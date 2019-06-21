#pragma once

namespace logic {

	class GameLoop {
	private:
		void(*mCallbackRender)();
		void(*mCallbackUpdate)();
		long long mMicroSPer;
		bool mShouldRun = true;
		int frames = 0, updates = 0;
		long long lag = 0;

		int mFps, mUps;

	public:
		GameLoop(void(*callbackRender)(), void(*callbackUpdate)(), long long microSecondsPerUpdate);

		void start();
		void stop();
		void forceUpdate();

		inline int getFPS() { return mFps; }
		inline int getUPS() { return mUps; }
	};

}