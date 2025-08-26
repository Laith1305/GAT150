#pragma once
#include "Component.h"

namespace viper {
	class AudioSource : public Component {
	public:
		std::string audioClipName;
	public:
		CLASS_PROTOTYPE(AudioSource)


		// Inherited via Component
		void Update(float dt) override;
		void Play();


	};
}