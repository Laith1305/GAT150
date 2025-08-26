#include "Actor.h"
#include "../Renderer/Mesh.h"
#include "Renderer/Renderer.h"
#include "Component.h"
#include <Components/RendererComponent.h>

namespace viper {
	FACTORY_REGISTER(Actor)

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
	void Actor::Read(const json::value_t& value){
		Object::Read(value);

		JSON_READ(value, tag);
		JSON_READ(value, lifespan);

		if (JSON_HAS(value,transform)) transform.Read(JSON_GET(value, transform));

		if (JSON_HAS(value, components)) {
			for (auto& componentValue : JSON_GET(value, components).GetArray()) {

				std::string type;
				JSON_READ(componentValue, type);


				auto component = Factory::Instance().Create<Component>(type);
				component->Read(componentValue);

				AddComponent(std::move(component));
			}
		}

	}
}
