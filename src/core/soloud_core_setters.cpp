/*
SoLoud audio engine
Copyright (c) 2013-2014 Jari Komppa

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

#include "soloud_internal.h"

// Setters - set various bits of SoLoud state

namespace SoLoud
{
	void Soloud::setPostClipScaler(float aScaler)
	{
		mPostClipScaler = aScaler;
	}

	void Soloud::setGlobalVolume(float aVolume)
	{
		mGlobalVolumeFader.mActive = 0;
		mGlobalVolume = aVolume;
	}		

	void Soloud::setRelativePlaySpeed(handle aVoiceHandle, float aSpeed)
	{
		FOR_ALL_VOICES_PRE
		mVoice[ch]->mRelativePlaySpeedFader.mActive = 0;
		setVoiceRelativePlaySpeed(ch, aSpeed);
		FOR_ALL_VOICES_POST
	}

	void Soloud::setSamplerate(handle aVoiceHandle, float aSamplerate)
	{
		FOR_ALL_VOICES_PRE
		mVoice[ch]->mBaseSamplerate = aSamplerate;
		mVoice[ch]->mSamplerate = mVoice[ch]->mBaseSamplerate * mVoice[ch]->mRelativePlaySpeed;
		FOR_ALL_VOICES_POST
	}

	void Soloud::setPause(handle aVoiceHandle, bool aPause)
	{
		FOR_ALL_VOICES_PRE
		setVoicePause(ch, aPause);
		FOR_ALL_VOICES_POST
	}

	void Soloud::setPauseAll(bool aPause)
	{
		if (mLockMutexFunc) mLockMutexFunc(mMutex);
		int ch;
		for (ch = 0; ch < VOICE_COUNT; ch++)
		{
			setVoicePause(ch, aPause);
		}
		if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
	}

	void Soloud::setProtectVoice(handle aVoiceHandle, bool aProtect)
	{
		FOR_ALL_VOICES_PRE
		if (aProtect)
		{
			mVoice[ch]->mFlags |= AudioSourceInstance::PROTECTED;
		}
		else
		{
			mVoice[ch]->mFlags &= ~AudioSourceInstance::PROTECTED;
		}
		FOR_ALL_VOICES_POST
	}

	void Soloud::setPan(handle aVoiceHandle, float aPan)
	{		
		FOR_ALL_VOICES_PRE
		setVoicePan(ch, aPan);
		FOR_ALL_VOICES_POST
	}

	void Soloud::setPanAbsolute(handle aVoiceHandle, float aLVolume, float aRVolume)
	{
		FOR_ALL_VOICES_PRE
		mVoice[ch]->mPanFader.mActive = 0;
		mVoice[ch]->mLVolume = aLVolume;
		mVoice[ch]->mRVolume = aRVolume;
		FOR_ALL_VOICES_POST
	}

	void Soloud::setVolume(handle aVoiceHandle, float aVolume)
	{
		FOR_ALL_VOICES_PRE
		mVoice[ch]->mVolumeFader.mActive = 0;
		setVoiceVolume(ch, aVolume);
		FOR_ALL_VOICES_POST
	}

	void Soloud::setDelaySamples(handle aVoiceHandle, unsigned int aSamples)
	{
		FOR_ALL_VOICES_PRE
		mVoice[ch]->mDelaySamples = aSamples;
		FOR_ALL_VOICES_POST
	}

	void Soloud::setVisualizationEnable(bool aEnable)
	{
		if (aEnable)
		{
			mFlags |= ENABLE_VISUALIZATION;
		}
		else
		{
			mFlags &= ~ENABLE_VISUALIZATION;
		}
	}

}
