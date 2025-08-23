#pragma once
#include "Component.h"

class Rocket : public viper::Component {
public:
	float speed = 200;

public:
	Rocket() = default;
	/*Rocket(const viper::Transform& transform) :
		Actor{ transform }
	{
	}*/

	void Update(float dt) override;

	void OnCollision(Actor* other);
};
