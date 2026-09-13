#include "timer.h"
#include <profileapi.h>

void timer::Init(int fps)
{
	QueryPerformanceFrequency(&timerFreq);	
	QueryPerformanceCounter(&timeNow);
	QueryPerformanceCounter(&timePrevious);

	requestFPS = fps;

	intervalsPerFrame = ((float)timerFreq.QuadPart / requestFPS);
}

int timer::FramesToUpdate()
{
	int frametoupdate = 0;
	QueryPerformanceCounter(&timeNow);

	intervalsSinceLastUpdate = (float)timeNow.QuadPart - (float)timePrevious.QuadPart;

	frametoupdate = (int)(intervalsSinceLastUpdate / intervalsPerFrame);

	if (frametoupdate != 0) {
		QueryPerformanceCounter(&timePrevious);
	}
	
	return frametoupdate;
}
