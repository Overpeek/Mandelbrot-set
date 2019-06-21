#include "gameloop.h"

#include "tools/clock.h"

namespace logic {

	GameLoop::GameLoop(void(*callbackRender)(), void(*callbackUpdate)(), long long microSecondsPerUpdate) {
		mMicroSPer = microSecondsPerUpdate;
		mCallbackRender = callbackRender;
		mCallbackUpdate = callbackUpdate;
	}

	void GameLoop::start() {
		long long start = tools::Clock::getMicroseconds();
		long long previous = start;
		while (mShouldRun)
		{
			long long current = tools::Clock::getMicroseconds();
			long long elapsed = current - previous;
			previous = current;
			lag += elapsed;
		
			while (lag >= mMicroSPer)
			{
				updates++;
				mCallbackUpdate();
				lag -= mMicroSPer;
			}
		
			frames++;
			if (mCallbackRender) mCallbackRender();
		
			if (current - start > 1000000) {
				mFps = frames; mUps = updates;
				frames = 0; updates = 0;
				start += 1000000;
			}
		}
	}

	void GameLoop::stop() {
		mShouldRun = false;
	}

	void GameLoop::forceUpdate() {
		updates++;
		mCallbackUpdate();
		lag -= mMicroSPer;
	}

}