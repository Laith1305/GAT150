#include "Actor.h"
#include "../Renderer/Model.h"

namespace viper {
	void Actor::Update(float dt)
	{
		if (destroyed) return;

		if (lifespan != 0) {
			lifespan -= dt;
			destroyed = lifespan <= 0;
		}

		transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}

	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;

		m_model->Draw(renderer, transform);
	}

	float Actor::GetRadius()
	{
		return (m_model) ? m_model->GetRadius() * transform.scale * 0.9f : 0;
	}
}
