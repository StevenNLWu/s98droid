
#define	LOCAL_LOG

#include "m_s98/m_s98.h"
#include "pmdwin/pmdwin.h"
#include "net_autch_android_s98droid_MS98NativeInterface.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef	LOCAL_LOG
#include <android/log.h>
#endif


#define USE_S98		0
#define USE_PMDWIN		1

static int select_synth = USE_S98;	// USE_S98 || USE_PMDWIN

static s98File* theFile = NULL; // THE s98 file
// PMDWin instance is at pmdwin.cpp


/*
 * Class:     net_autch_android_s98droid_MS98NativeInterface
 * Method:    ms98Init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_autch_android_s98droid_MS98NativeInterface_ms98Init
  (JNIEnv *, jclass)
{
	pmdwininit((char*)"/sdcard/s98");
	setpcmrate(SAMPLE_RATE);
	//setfmcalc55k(true);
	setppsuse(true);
	setrhythmwithssgeffect(true);
	setppsinterpolation(true);
	//setp86interpolation(true);
	//setppzinterpolation(true);
}

/*
 * Class:     net_autch_android_s98droid_MS98NativeInterface
 * Method:    ms98Deinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_autch_android_s98droid_MS98NativeInterface_ms98Deinit
  (JNIEnv *, jclass)
{
	switch(select_synth) {
	case USE_S98:
		if(theFile != NULL) {
			delete theFile;
			theFile = NULL;
		}
		break;
	case USE_PMDWIN:
		music_stop();
	}
}

int load_s98(const char* cszFileName)
{
	uint32_t bytes_read;
	uint8_t *Buffer = 0;
	int fd = -1, ret = 0;
	struct stat stat_buf;
	do
	{
		fd = ::open(cszFileName, O_RDONLY);
		if (fd < 0) break;
		fstat(fd, &stat_buf);
		if (stat_buf.st_size < 4) break;
		Buffer = new uint8_t[stat_buf.st_size];
		if (!Buffer) break;
		if ((bytes_read = ::read(fd, Buffer, stat_buf.st_size)) < 0) break;
		if (stat_buf.st_size != bytes_read) break;

		if(theFile != NULL) {
			delete theFile;
			theFile = NULL;
		}

		theFile = new s98File;
		if(theFile == NULL) break;
		if(!theFile->OpenFromBuffer(Buffer, bytes_read)) break;
		ret = 1;
	} while (0);
	if (Buffer) delete [] Buffer;
	if (fd != -1) ::close(fd);
	return ret;
}

int load_pmdwin(const char* cszFileName)
{
	music_stop();

	int ret = music_load((char*)cszFileName);

	__android_log_print(ANDROID_LOG_DEBUG, "PMDWin", "music_load: %d", ret);

	switch(ret) {
	case PMDWIN_OK:
	case ERR_OPEN_PPC_FILE:
	case WARNING_PPC_ALREADY_LOAD:
	case ERR_OPEN_P86_FILE:
	case ERR_OPEN_PPS_FILE:
	case WARNING_PPS_ALREADY_LOAD:
	case ERR_OPEN_PPZ1_FILE:
	case ERR_OPEN_PPZ2_FILE:
	case WARNING_PPZ1_ALREADY_LOAD:
	case WARNING_PPZ2_ALREADY_LOAD:
		music_start();
		return 1;
	case ERR_WRONG_PPC_FILE:
	case ERR_WRONG_PPZ1_FILE:
	case ERR_WRONG_PPZ2_FILE:
	case ERR_WRONG_P86_FILE:
	case ERR_OPEN_MUSIC_FILE:
	case ERR_WRONG_MUSIC_FILE:
	case ERR_OUT_OF_MEMORY:
	case ERR_OTHER:
		return 0;
	}
}

/*
 * Class:     net_autch_android_s98droid_MS98NativeInterface
 * Method:    ms98OpenFile
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_net_autch_android_s98droid_MS98NativeInterface_ms98OpenFile
  (JNIEnv* env, jclass klass, jstring filename)
{
	int ret = 0;

	if(filename == NULL) return 0;

	const char* cszFileName = env->GetStringUTFChars(filename, NULL);
	char* pPeriod;


	pPeriod = strrchr(cszFileName, '.');
	if(pPeriod == NULL) {
		env->ReleaseStringUTFChars(filename, cszFileName);
		return 0;
	}

	if(strcmp(pPeriod, ".s98") == 0 || strcmp(pPeriod, ".S98") == 0) {
		// this may be a s98
		ret = load_s98(cszFileName);
		select_synth = USE_S98;
	} else {
		ret = load_pmdwin(cszFileName);
		select_synth = USE_PMDWIN;
	}
	env->ReleaseStringUTFChars(filename, cszFileName);
	return ret;
}

/*
 * Class:     net_autch_android_s98droid_MS98NativeInterface
 * Method:    ms98Render
 * Signature: ([BI)I
 */
JNIEXPORT jint JNICALL Java_net_autch_android_s98droid_MS98NativeInterface_ms98Render
  (JNIEnv *env, jclass klass, jbyteArray jbuffer, jint size)
{
	jbyte* buffer = env->GetByteArrayElements(jbuffer, NULL);
	jint ret;

	if(select_synth == USE_S98) {
		if(theFile == NULL) return 0;
		memset(buffer, 0, size);
		ret = theFile->Write((Int16*)buffer, (uint32_t)(size / 4)) * 4;
	} else {
		memset(buffer, 0, size);
		getpcmdata((short*)buffer, size / 4);
		ret = size;
	}

	env->ReleaseByteArrayElements(jbuffer, buffer, 0);

	return ret;
}

/*
 * Class:     net_autch_android_s98droid_MS98NativeInterface
 * Method:    ms98Close
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_net_autch_android_s98droid_MS98NativeInterface_ms98Close
  (JNIEnv *, jclass)
{
	switch(select_synth) {
	case USE_S98:
		if(theFile != NULL) {
			delete theFile;
			theFile = NULL;
		}
		break;
	case USE_PMDWIN:
		music_stop();
	}
}

