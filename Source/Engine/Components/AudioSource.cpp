#include "AudioSource.h"
#include "AudioClip.h"
#include "Engine.h"

namespace viper {

	void viper::AudioSource::Update(float dt)
	{

	}

	void AudioSource::Play(){
		auto audioClip = Resources().Get<AudioClip>(audioClipName, GetEngine().GetAudio());

		if (audioClip) {
			GetEngine().GetAudio().PlaySound(*audioClip);
		}
	}

}