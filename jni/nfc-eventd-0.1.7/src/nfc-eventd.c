/*
 * NFC Event Daemon
 * Generate events on tag status change
 * Copyright (C) 2009 Romuald Conty <romuald@libnfc.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif // HAVE_CONFIG_H

#include <nfc/nfc.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <unistd.h>

#include <errno.h>
#include <signal.h>

/* Dynamic load */
#include <dlfcn.h>
/* Configuration parser */
#include "nfcconf/nfcconf.h"
/* Debugging functions */
#include "debug/debug.h"
/* Module common defines */
#include "modules/nem_common.h"

#include "debug/nfc-utils.h"

#include "types.h"

#define DEF_POLLING 1    /* 1 second timeout */
#define DEF_EXPIRE 0    /* no expire */

#define DEF_CONFIG_FILE SYSCONFDIR"/nfc-eventd.conf"

int polling_time;
int expire_time;
int daemonize;
int debug;
char *cfgfile;

nfcconf_context *ctx;
const nfcconf_block *root;

typedef struct slot_st slot_t;

static module_init_fct module_init_fct_ptr = NULL;
static module_event_handler_fct module_event_handler_fct_ptr = NULL;
static nfc_connstring* connstring = NULL;

nfc_device* device = NULL;
nfc_context* context;

bool quit_flag = false;

static void stop_polling(int sig) 
{ 
  (void) sig;
  DBG( "Stop polling... (sig:%d)", sig);
  if (device != NULL) {
    nfc_abort_command(device);
    DBG( "%s", "Polling aborted.");
    quit_flag = true;
  } else {
    nfc_exit(context);
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Load and init specified (in config file) NEM module
 */
static int load_module( void ) {
    nfcconf_block **module_list, *my_module;

    module_list = nfcconf_find_blocks ( ctx, root, "module", NULL );
    if ( !module_list ) {
        ERR ( "%s", "Module item not found." );
        return -1;
    }
    my_module = module_list[0];
    free ( module_list );
    if ( !my_module ) {
        ERR ( "%s", "Module item not found." );
        return -1;
    }
    DBG("Loading module: '%s'...", my_module->name->data);
    char module_path[256]={ '\0', };
    strcat(module_path, NEMDIR"/" );
    strcat(module_path, my_module->name->data);
    strcat(module_path, ".so");
    DBG("Module found at: '%s'...", module_path);

    void *module_handler;
    module_handler = dlopen(module_path,RTLD_LAZY);
    if ( module_handler == NULL ) {
        ERR("Unable to open module: %s", dlerror());
        exit(EXIT_FAILURE);
    }

    char module_fct_name[256];
    char *error;

    module_fct_name[0]='\0';
    strcat(module_fct_name,my_module->name->data);
    strcat(module_fct_name,"_init");

    module_init_fct_ptr = dlsym(module_handler,module_fct_name);

    if ((error = dlerror()) != NULL) {
        ERR ("%s", error);
        exit(EXIT_FAILURE);
    }

    module_fct_name[0]='\0';
    strcat(module_fct_name,my_module->name->data);
    strcat(module_fct_name,"_event_handler");

    module_event_handler_fct_ptr = dlsym(module_handler,module_fct_name);
    if ((error = dlerror()) != NULL) {
        ERR ( "%s", error);
        exit(EXIT_FAILURE);
    }

    (*module_init_fct_ptr)( ctx, my_module );
    return 0;
}

/**
 * @brief Execute NEM function that handle events
 */
static int execute_event ( const nfc_device *dev, const nfc_target* tag, const nem_event_t event ) {
    return (*module_event_handler_fct_ptr)( dev, tag, event );
}

/**
 * @brief Parse configuration file
 */
static int parse_config_file(void) {
    ctx = nfcconf_new ( cfgfile );
    if ( !ctx ) {
        ERR ( "%s", "Error creating conf context" );
        return -1;
    }
    if ( nfcconf_parse ( ctx ) <= 0 ) {
        ERR ( "Error parsing file '%s'", cfgfile );
        return -1;
    }
    /* now parse options */
    root = nfcconf_find_block ( ctx, NULL, "nfc-eventd" );
    if ( !root ) {
        ERR ( "nfc-eventd block not found in config: '%s'", cfgfile );
        return -1;
    }
    debug = nfcconf_get_bool ( root, "debug", debug );
    daemonize = nfcconf_get_bool ( root, "daemon", daemonize );
    polling_time = nfcconf_get_int ( root, "polling_time", polling_time );
    expire_time = nfcconf_get_int ( root, "expire_time", expire_time );

    if ( debug ) set_debug_level ( 1 );

    DBG( "%s", "Looking for specified NFC device." );
    nfcconf_block **device_list, *my_device;
    const char* nfc_device_str = nfcconf_get_str ( root, "nfc_device", "" );
    if (strcmp( nfc_device_str, "") != 0) {
        device_list = nfcconf_find_blocks ( ctx, root, "device", NULL );
        if ( !device_list ) {
            ERR ( "%s", "Device item not found." );
            return -1;
        }
        int i = 0;
        my_device = device_list[i];
        while ( my_device != NULL ) {
            i++;
            if ( strcmp(my_device->name->data, nfc_device_str) == 0 ) {
                INFO("Specified device %s have been found.", nfc_device_str);
                /*connstring = malloc(sizeof(nfc_connstring));
                connstring->pcDriver = (char*)nfcconf_get_str( my_device, "driver", "" );
		char* device_name = (char*)nfcconf_get_str( my_device, "name", "" );
		strncpy(connstring->acDevice, device_name, sizeof(connstring->acDevice));
                char* device_port   = (char*)nfcconf_get_str( my_device, "port", "" );
		strncpy(connstring->acPort, device_port, sizeof(connstring->acPort));
                connstring->uiSpeed  = nfcconf_get_int( my_device, "speed", 9600 );
                connstring->uiBusIndex  = nfcconf_get_int( my_device, "index", 0 );*/
                break;
            }
            my_device = device_list[i];
        }
        DBG( "Found %d device configuration block(s).", i );
        if ( connstring == NULL ) {
            ERR("NFC device have been specified in configuration file but there is no device description. Unable to select specified device: %s.", nfc_device_str);
        }
        free ( device_list );
    }

    return 0;
}

/**
 * @brief Parse command line args
 */
static int parse_args ( int argc, char *argv[] ) {
    int i;
    int res;
    polling_time = DEF_POLLING;
    expire_time = DEF_EXPIRE;
    debug   = 0;
    daemonize  = 0;
    cfgfile = DEF_CONFIG_FILE;
    /* first of all check whether debugging should be enabled */
    for ( i = 0; i < argc; i++ ) {
        if ( ! strcmp ( "debug", argv[i] ) ) set_debug_level ( 1 );
    }
    /* try to find a configuration file entry */
    for ( i = 0; i < argc; i++ ) {
        if ( strstr ( argv[i], "config_file=" ) ) {
            cfgfile = 1 + strchr ( argv[i], '=' );
            break;
        }
    }
    /* parse configuration file */
    if ( parse_config_file() < 0 ) {
        ERR ( "Error parsing configuration file %s", cfgfile );
        exit ( EXIT_FAILURE );
    }

    /* and now re-parse command line to take precedence over cfgfile */
    for ( i = 1; i < argc; i++ ) {
        if ( strcmp ( "daemon", argv[i] ) == 0 ) {
            daemonize = 1;
            continue;
        }
        if ( strcmp ( "nodaemon", argv[i] ) == 0 ) {
            daemonize = 0;
            continue;
        }
        if ( strstr ( argv[i], "polling_time=" ) ) {
            res = sscanf ( argv[i], "polling_time=%d", &polling_time );
            continue;
        }
        if ( strstr ( argv[i], "expire_time=" ) ) {
            res = sscanf ( argv[i], "expire_time=%d", &expire_time );
            continue;
        }
        if ( strstr ( argv[i], "debug" ) ) {
            continue;  /* already parsed: skip */
        }
        if ( strstr ( argv[i], "nodebug" ) ) {
            set_debug_level ( 0 );
            continue;  /* already parsed: skip */
        }
        if ( strstr ( argv[i], "config_file=" ) ) {
            continue; /* already parsed: skip */
        }
        ERR ( "unknown option %s", argv[i] );

        /* arriving here means syntax error */
        printf( "NFC Event Daemon\n" );
        printf( "Usage %s [[no]debug] [[no]daemon] [polling_time=<time>] [expire_time=<limit>] [config_file=<file>]", argv[0] );
        printf( "\nDefaults: debug=0 daemon=0 polltime=%d (ms) expiretime=0 (none) config_file=%s", DEF_POLLING, DEF_CONFIG_FILE );
        exit ( EXIT_FAILURE );
    } /* for */
    /* end of config: return */
    return 0;
}

typedef enum {
  NFC_POLL_HARDWARE,
  NFC_POLL_SOFTWARE,
} nfc_poll_mode;

static nfc_target*
ned_poll_for_tag(nfc_device* dev, nfc_target* tag)
{
  uint8_t uiPollNr;
  const uint8_t uiPeriod = 2; /* 2 x 150 ms = 300 ms */
  const nfc_modulation nm[1] = { { .nmt = NMT_ISO14443A, .nbr = NBR_106 } };

  if( tag != NULL ) {
    /* We are looking for a previous tag */
    /* In this case, to prevent for intensive polling we add a sleeping time */
    sleep ( polling_time );
    uiPollNr = 3; /* Polling duration : btPollNr * szTargetTypes * btPeriod * 150 = btPollNr * 300 = 900 */
  } else {
    /* We are looking for any tag */
    uiPollNr = 0xff; /* We endless poll for a new tag */
  }

  nfc_target target;
  int res = nfc_initiator_poll_target (dev, nm, 1, uiPollNr, uiPeriod, &target);
  if (res > 0) {
    if ( (tag != NULL) && (0 == memcmp(tag->nti.nai.abtUid, target.nti.nai.abtUid, target.nti.nai.szUidLen)) ) {
      return tag;
    } else {
      nfc_target* rv = malloc(sizeof(nfc_target));
      memcpy(rv, &target, sizeof(nfc_target));
      nfc_initiator_deselect_target ( dev );
      return rv;
    }
  } else {
    return NULL;
  }
}

int
main ( int argc, char *argv[] ) {
    nfc_target* old_tag = NULL;
    nfc_target* new_tag;

    int expire_count = 0;

    INFO ("%s", PACKAGE_STRING);

    /* parse args and configuration file */
    parse_args ( argc, argv );

    /* put my self into background if flag is set */
    if ( daemonize ) {
        DBG ( "%s", "Going to be daemon..." );
        if ( daemon ( 0, debug ) < 0 ) {
            ERR ( "Error in daemon() call: %s", strerror ( errno ) );
            return 1;
        }
    }

    load_module();

    /*
     * Wait endlessly for all events in the list of readers
     * We only stop in case of an error
     *
     * COMMENT:
     * There are no way in libnfc API to detect if a card is present or not
     * so the way we proceed is to look for an tag
     * Any ideas will be welcomed
     */
    signal(SIGINT, stop_polling);
    signal(SIGTERM, stop_polling);

    nfc_init(&context);
    if (context == NULL) {
      ERR("Unable to init libnfc (malloc)");
      exit(EXIT_FAILURE);
    }
    // Try to open the NFC device
    if ( device == NULL ) device = nfc_open( context, NULL );
    if ( device == NULL ) {
        ERR( "%s", "NFC device not found" );
        exit(EXIT_FAILURE);
    }
    nfc_initiator_init ( device );

    // Drop the field for a while
    nfc_device_set_property_bool ( device, NP_ACTIVATE_FIELD, false );
    nfc_device_set_property_bool ( device, NP_INFINITE_SELECT, false );

    // Configure the CRC and Parity settings
    nfc_device_set_property_bool ( device, NP_HANDLE_CRC, true );
    nfc_device_set_property_bool ( device, NP_HANDLE_PARITY, true );

    // Enable field so more power consuming cards can power themselves up
    nfc_device_set_property_bool ( device, NP_ACTIVATE_FIELD, true );

    INFO( "Connected to NFC device: %s", nfc_device_get_name(device) );

    do {
detect:
        new_tag = ned_poll_for_tag(device, old_tag);

        if ( old_tag == new_tag ) { /* state unchanged */
            /* on card not present, increase and check expire time */
            if (( !quit_flag ) && ( expire_time == 0 )) goto detect;
            if (( !quit_flag ) && ( new_tag != NULL )) goto detect;
            expire_count += polling_time;
            if ( expire_count >= expire_time ) {
                DBG ( "%s", "Timeout on tag removed " );
                execute_event ( device, new_tag,EVENT_EXPIRE_TIME );
                expire_count = 0; /*restart timer */
            }
        } else { /* state changed; parse event */
            expire_count = 0;
            if ( new_tag == NULL ) {
                DBG ( "%s", "Event detected: tag removed" );
                execute_event ( device, old_tag, EVENT_TAG_REMOVED );
                free(old_tag);
            } else {
                DBG ( "%s", "Event detected: tag inserted " );
                execute_event ( device, new_tag, EVENT_TAG_INSERTED );
            }
            old_tag = new_tag;
        }
    } while ( !quit_flag );

    if ( device != NULL ) {
        nfc_close(device);
        DBG ( "NFC device (0x%08x) is disconnected", device );
        device = NULL;
    }

    /* If we get here means that an error or exit status occurred */
    DBG ( "%s", "Exited from main loop" );
    nfc_exit(context);
    exit ( EXIT_FAILURE );
} /* main */

