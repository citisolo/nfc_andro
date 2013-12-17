/*
 * object-store.h
 *
 *  Created on: 17 Dec 2013
 *      Author: redbandit
 */

#ifndef OBJECT_STORE_H_
#define OBJECT_STORE_H_
#include <jni.h>

 struct object_store{
     JNIEnv * pEnv;
	 jobject  objectRef;

} ;

 typedef struct object_store OBJECT_STORE;
#endif /* OBJECT_STORE_H_ */
