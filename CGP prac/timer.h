#pragma once
#include <windows.h>
class timer
{
	public:
		void Init(int);
		int FramesToUpdate();
		static timer& getInstance() {
			static timer instance;
			return instance;
		}

	private:
		
		LARGE_INTEGER timerFreq;
		LARGE_INTEGER timeNow;
		LARGE_INTEGER timePrevious;
		int requestFPS;
		float intervalsPerFrame;
		float intervalsSinceLastUpdate;
};

