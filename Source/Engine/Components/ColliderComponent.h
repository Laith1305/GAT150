#pragma once
#include "Component.h"

namespace viper {
	class ColliderComponent : public Component {
	public:
		virtual bool CheckCollission(ColliderComponent& other) = 0;

	};
}