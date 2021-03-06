/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class mona_Mona */

#ifndef _Included_mona_Mona
#define _Included_mona_Mona
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     mona_Mona
 * Method:    createMona
 * Signature: (IIII)I
 */
JNIEXPORT jint JNICALL Java_mona_Mona_createMona
  (JNIEnv *, jobject, jint, jint, jint, jint);

/*
 * Class:     mona_Mona
 * Method:    createMonaWithParameters
 * Signature: ([Ljava/lang/String;[Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_mona_Mona_createMonaWithParameters
  (JNIEnv *, jobject, jobjectArray, jobjectArray);

/*
 * Class:     mona_Mona
 * Method:    setSensorResolution
 * Signature: (IF)I
 */
JNIEXPORT jint JNICALL Java_mona_Mona_setSensorResolution
  (JNIEnv *, jobject, jint, jfloat);

/*
 * Class:     mona_Mona
 * Method:    addSensorMode
 * Signature: (I[Z)I
 */
JNIEXPORT jint JNICALL Java_mona_Mona_addSensorMode__I_3Z
  (JNIEnv *, jobject, jint, jbooleanArray);

/*
 * Class:     mona_Mona
 * Method:    addSensorMode
 * Signature: (I[ZF)I
 */
JNIEXPORT jint JNICALL Java_mona_Mona_addSensorMode__I_3ZF
  (JNIEnv *, jobject, jint, jbooleanArray, jfloat);

/*
 * Class:     mona_Mona
 * Method:    setEffectEventIntervals
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_mona_Mona_setEffectEventIntervals
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     mona_Mona
 * Method:    setEffectEventInterval
 * Signature: (IIIIF)V
 */
JNIEXPORT void JNICALL Java_mona_Mona_setEffectEventInterval
  (JNIEnv *, jobject, jint, jint, jint, jint, jfloat);

/*
 * Class:     mona_Mona
 * Method:    dispose
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_mona_Mona_dispose
  (JNIEnv *, jobject, jint);

/*
 * Class:     mona_Mona
 * Method:    cycle
 * Signature: (I[F)I
 */
JNIEXPORT jint JNICALL Java_mona_Mona_cycle
  (JNIEnv *, jobject, jint, jfloatArray);

/*
 * Class:     mona_Mona
 * Method:    addResponse
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_mona_Mona_addResponse
  (JNIEnv *, jobject, jint);

/*
 * Class:     mona_Mona
 * Method:    getResponsePotential
 * Signature: (II)D
 */
JNIEXPORT jdouble JNICALL Java_mona_Mona_getResponsePotential
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     mona_Mona
 * Method:    overrideResponse
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_mona_Mona_overrideResponse
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     mona_Mona
 * Method:    clearResponseOverride
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_mona_Mona_clearResponseOverride
  (JNIEnv *, jobject, jint);

/*
 * Class:     mona_Mona
 * Method:    getNeed
 * Signature: (II)D
 */
JNIEXPORT jdouble JNICALL Java_mona_Mona_getNeed
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     mona_Mona
 * Method:    setNeed
 * Signature: (IID)V
 */
JNIEXPORT void JNICALL Java_mona_Mona_setNeed
  (JNIEnv *, jobject, jint, jint, jdouble);

/*
 * Class:     mona_Mona
 * Method:    setPeriodicNeed
 * Signature: (IIID)V
 */
JNIEXPORT void JNICALL Java_mona_Mona_setPeriodicNeed
  (JNIEnv *, jobject, jint, jint, jint, jdouble);

/*
 * Class:     mona_Mona
 * Method:    addGoal
 * Signature: (II[FIID)I
 */
JNIEXPORT jint JNICALL Java_mona_Mona_addGoal__II_3FIID
  (JNIEnv *, jobject, jint, jint, jfloatArray, jint, jint, jdouble);

/*
 * Class:     mona_Mona
 * Method:    addGoal
 * Signature: (II[FID)I
 */
JNIEXPORT jint JNICALL Java_mona_Mona_addGoal__II_3FID
  (JNIEnv *, jobject, jint, jint, jfloatArray, jint, jdouble);

/*
 * Class:     mona_Mona
 * Method:    findGoal
 * Signature: (II[FII)I
 */
JNIEXPORT jint JNICALL Java_mona_Mona_findGoal__II_3FII
  (JNIEnv *, jobject, jint, jint, jfloatArray, jint, jint);

/*
 * Class:     mona_Mona
 * Method:    findGoal
 * Signature: (II[FI)I
 */
JNIEXPORT jint JNICALL Java_mona_Mona_findGoal__II_3FI
  (JNIEnv *, jobject, jint, jint, jfloatArray, jint);

/*
 * Class:     mona_Mona
 * Method:    getNumGoals
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_mona_Mona_getNumGoals
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     mona_Mona
 * Method:    isGoalEnabled
 * Signature: (III)Z
 */
JNIEXPORT jboolean JNICALL Java_mona_Mona_isGoalEnabled
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     mona_Mona
 * Method:    enableGoal
 * Signature: (III)Z
 */
JNIEXPORT jboolean JNICALL Java_mona_Mona_enableGoal
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     mona_Mona
 * Method:    disableGoal
 * Signature: (III)Z
 */
JNIEXPORT jboolean JNICALL Java_mona_Mona_disableGoal
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     mona_Mona
 * Method:    removeGoal
 * Signature: (III)Z
 */
JNIEXPORT jboolean JNICALL Java_mona_Mona_removeGoal
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     mona_Mona
 * Method:    load
 * Signature: (ILjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_mona_Mona_load__ILjava_lang_String_2
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     mona_Mona
 * Method:    load
 * Signature: (ILmona/NativeFileDescriptor;)Z
 */
JNIEXPORT jboolean JNICALL Java_mona_Mona_load__ILmona_NativeFileDescriptor_2
  (JNIEnv *, jobject, jint, jobject);

/*
 * Class:     mona_Mona
 * Method:    save
 * Signature: (ILjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_mona_Mona_save__ILjava_lang_String_2
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     mona_Mona
 * Method:    save
 * Signature: (ILmona/NativeFileDescriptor;)Z
 */
JNIEXPORT jboolean JNICALL Java_mona_Mona_save__ILmona_NativeFileDescriptor_2
  (JNIEnv *, jobject, jint, jobject);

/*
 * Class:     mona_Mona
 * Method:    clearWorkingMemory
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_mona_Mona_clearWorkingMemory
  (JNIEnv *, jobject, jint);

/*
 * Class:     mona_Mona
 * Method:    clearLongTermMemory
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_mona_Mona_clearLongTermMemory
  (JNIEnv *, jobject, jint);

/*
 * Class:     mona_Mona
 * Method:    clear
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_mona_Mona_clear
  (JNIEnv *, jobject, jint);

/*
 * Class:     mona_Mona
 * Method:    print_jni
 * Signature: (ILjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_mona_Mona_print_1jni
  (JNIEnv *, jobject, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif
