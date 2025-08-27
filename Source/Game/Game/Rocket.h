#pragma once
#include "Component.h"

class Rocket : public viper::Component, public viper::ICollidable {
public:
	float speed = 200;

public:
	Rocket() = default;
	CLASS_PROTOTYPE(Rocket)



	void Update(float dt) override;

	void OnCollision(viper::Actor* other) override;

	void Read(const viper::json::value_t& value) override;
};
