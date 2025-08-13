#pragma once
#include "Component.h"

namespace viper {
	class RigidBody : public Component {
	public:
		vec2 velocity{ 0, 0 };
		float damping{ 0 };


	public:


		void Update(float dt) override;
	};
}