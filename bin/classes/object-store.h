/*
 * object-store.h
 *
 *  Created on: 17 Dec 2013
 *      Author: redbandit
 */

#ifndef OBJECT_STORE_H_
#define OBJECT_STORE_H_
#include <jni.h>
#include <pthread.h>

 __thread struct jobject_store{
     JavaVM * jvm ;
	 jobject  objectRef;

} ;

 //typedef struct object_store OBJECT_STORE;
 extern struct  jobject_store *object_store;
#endif /* OBJECT_STORE_H_ */
