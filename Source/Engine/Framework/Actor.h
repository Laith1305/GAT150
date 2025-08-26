#pragma once
#include "Component.h"
#include "Object.h"
#include "Math/Transform.h"
#include "Core/Serializable.h"
#include "Texture.h"
#include <string>
#include <memory>
#include <vector>

namespace viper {
	class Actor : public Object {
	public:
		std::string tag;

		float lifespan{ 0 };
		
		Transform transform;

		bool destroyed{ false };

		class Scene* scene{ nullptr };

	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{}

		void Read(const json::value_t& value) override;

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) {}



		// components
		void AddComponent(std::unique_ptr<class Component> component);


		template <typename T>
		T* GetComponent();

		template <typename T>
		std::vector<T*> GetComponents();

		

	protected:

		std::vector<std::unique_ptr<class Component>> m_components;
		res_t<Texture> m_texture;

		// Inherited via Serializable
		//std::shared_ptr<Model> m_model;
	};



	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& Component : m_components) {
			auto result = dynamic_cast<T*>(Component.get());
			if (result) return result;
		}
		return nullptr;
	}
	template<typename T>
	inline std::vector<T*> Actor::GetComponents()
	{

		std::vector<T*> results;
		for (auto& Component : m_components) {
			auto result = dynamic_cast<T*>(Component.get());
			if (result) {
				results.push_back(result);
			}
		}
		return results;
	}
}