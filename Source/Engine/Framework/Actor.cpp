#include "Actor.h"
#include "../Renderer/Model.h"
#include "Renderer/Renderer.h"

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
		renderer.DrawTexture(m_texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);

		//m_texture->Draw(renderer, transform);
	}

	float Actor::GetRadius()
	{
		return (m_texture) ? m_texture->GetSize().Length() * 0.5f * transform.scale * 0.9f : 0;
	}
}
