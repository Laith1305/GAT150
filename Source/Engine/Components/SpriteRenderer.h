#pragma once
#include "RendererComponent.h"


namespace viper {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;



	public:

		// Inherited via RendererComponent
		void Update(float dt) override;

		void Draw(Renderer& renderer) override;


		// Inherited via Serializable
		void Read(const json::value_t& value) override;

	};
}


