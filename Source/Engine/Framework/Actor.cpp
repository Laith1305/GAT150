#include "Actor.h"
#include "../Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Component.h"
#include <Components/RendererComponent.h>

namespace viper {
	void Actor::Update(float dt)
	{
		if (destroyed) return;

		if (lifespan > 0) {
			lifespan -= dt;
			if (lifespan <= 0) {
				destroyed = true;
				return;

			}

		}

		for (auto& component : m_components) {
			if (component->active) component->Update(dt);
		}


		
	}

	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;
		for (auto& component : m_components)
		{
			if (component->active) {
				auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
				if (rendererComponent) {
					rendererComponent->Draw(renderer);
				}
				
			}
		}

		//renderer.DrawTexture(m_texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);

		//m_texture->Draw(renderer, transform);
	}

	
	void Actor::AddComponent(std::unique_ptr<class Component> component){
		component->owner = this;
		m_components.push_back(std::move(component));

	}
}
