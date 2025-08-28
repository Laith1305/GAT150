#pragma once
#include "Component.h"
#include "Physics/PhysicsBody.h"


namespace viper {
	class RigidBody : public Component {
	public:
		PhysicsBody::PhysicsBodyDef bodyDef;
		vec2 size{ 0, 0 };


		vec2 velocity{ 0, 0 };
		float damping{ 0 };


	public:
		CLASS_PROTOTYPE(RigidBody)
		RigidBody() = default;

		RigidBody(const RigidBody& other);


		void Start() override;




		void Update(float dt) override;
		void Draw(class Renderer& renderer);

		void Read(const json::value_t& value) override;

		void ApplyForce(const vec2& force);
		void ApplyTorque(float radians);

		void SetVelocity(const vec2& velocity);

	private:
		std::unique_ptr<PhysicsBody> physicsBody;


	};
}