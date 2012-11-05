#ifndef m_s98_h
#define m_s98_h

#include <stdint.h>
#include "m_s98/device/s98types.h"
#include "m_s98/device/s98device.h"

#define SAMPLE_RATE 48000
#define SYNC_RATE 60 /* (Hz) */
#define UNIT_RENDER (SAMPLE_RATE/SYNC_RATE)
#define S98DEVICE_MAX 16

class s98File {
public:
	bool OpenFromBuffer(const uint8_t *Buffer, uint32_t dwSize /*, SOUNDINFO *pInfo*/);
	/* bool Open(const char *cszFileName, SOUNDINFO *pInfo);*/
	void Close(void);
	uint32_t SetPosition(uint32_t dwpos);
	uint32_t Write(Int16 *Buffer, uint32_t numSample);
	s98File();
	~s98File();
protected:
	int number_of_devices;
	S98DEVICEIF *devices[S98DEVICE_MAX];
	uint8_t devicemap[0x40];

	uint8_t *s98data;
	uint8_t *s98head;
	uint8_t *s98top;
	uint8_t *s98loop;
	int length;
	uint32_t playtime; /* syncs */
	uint32_t looptime; /* syncs */

	uint8_t *s98cur;
	uint32_t curtime;

	int loopnum;
#if FADEOUT_TIME
	int loopcur;
	uint32_t fader;
#endif

#define SPS_SHIFT 28
#define SPS_LIMIT (1 << SPS_SHIFT)
	enum { SAMPLE_PER_SYNC, SYNC_PER_SAMPLE } spsmode;
	uint32_t sps;		/* sync/sample or sample/syjnc */
	uint32_t timerinfo1;
	uint32_t timerinfo2;

	double sync_per_sec;

	uint32_t lefthi;
	uint32_t leftlo;

	Sample bufdev[UNIT_RENDER * 2];

	void CalcTime(void);
	void Step(void);
	void Reset(void);

	void WriteSub(Int16 *Buffer, uint32_t numSample);
	uint32_t SyncToMsec(uint32_t sync);
	uint32_t MsecToSync(uint32_t ms);
};

#endif // !m_s98_h
