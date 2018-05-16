/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class net_autch_android_s98droid_PMDWinNativeInterface */

#ifndef _Included_net_autch_android_s98droid_PMDWinNativeInterface
#define _Included_net_autch_android_s98droid_PMDWinNativeInterface
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     net_autch_android_s98droid_PMDWinNativeInterface
 * Method:    pmdwinInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_autch_android_s98droid_PMDWinNativeInterface_pmdwinInit
  (JNIEnv *, jclass);

/*
 * Class:     net_autch_android_s98droid_PMDWinNativeInterface
 * Method:    pmdwinDeinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_autch_android_s98droid_PMDWinNativeInterface_pmdwinDeinit
  (JNIEnv *, jclass);

/*
 * Class:     net_autch_android_s98droid_PMDWinNativeInterface
 * Method:    pmdwinOpenFile
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_net_autch_android_s98droid_PMDWinNativeInterface_pmdwinOpenFile
  (JNIEnv *, jclass, jstring);

/*
 * Class:     net_autch_android_s98droid_PMDWinNativeInterface
 * Method:    pmdwinRender
 * Signature: ([BI)I
 */
JNIEXPORT jint JNICALL Java_net_autch_android_s98droid_PMDWinNativeInterface_pmdwinRender
  (JNIEnv *, jclass, jbyteArray, jint);

/*
 * Class:     net_autch_android_s98droid_PMDWinNativeInterface
 * Method:    pmdwinClose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_autch_android_s98droid_PMDWinNativeInterface_pmdwinClose
  (JNIEnv *, jclass);

/*
 * Class:     net_autch_android_s98droid_PMDWinNativeInterface
 * Method:    pmdwinFGetMemo
 * Signature: ([BLjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_net_autch_android_s98droid_PMDWinNativeInterface_pmdwinFGetMemo
  (JNIEnv *, jclass, jbyteArray, jstring, jint);

/*
 * Class:     net_autch_android_s98droid_PMDWinNativeInterface
 * Method:    pmdwinFGetMemo2
 * Signature: ([BLjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_net_autch_android_s98droid_PMDWinNativeInterface_pmdwinFGetMemo2
  (JNIEnv *, jclass, jbyteArray, jstring, jint);

/*
 * Class:     net_autch_android_s98droid_PMDWinNativeInterface
 * Method:    pmdwinFGetMemo3
 * Signature: ([BLjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_net_autch_android_s98droid_PMDWinNativeInterface_pmdwinFGetMemo3
  (JNIEnv *, jclass, jbyteArray, jstring, jint);

#ifdef __cplusplus
}
#endif
#endif