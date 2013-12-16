/*
 * jlog.h
 *
 *  Created on: 16 Dec 2013
 *      Author: redbandit
 */

#ifndef JLOG_H_
#define JLOG_H_

#include <android/log.h>

#define LOG_LEVEL 9
#define LOG_TAG "JLOGGER"

#define LOGU(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_UNKOWN, LOG_TAG, __VA_ARGS__);}
#define LOGD(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_DEFAULT, LOG_TAG, __VA_ARGS__);}
#define LOGV(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__);}
#define LOGDE(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__);}
#define LOGI(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__);}
#define LOGW(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__);}
#define LOGE(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__);}
#define LOGF(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__);}
#define LOGS(level, ...) if (level <= LOG_LEVEL){__android_log_print(ANDROID_LOG_SILENT, LOG_TAG, __VA_ARGS__);}



#endif /* JLOG_H_ */
