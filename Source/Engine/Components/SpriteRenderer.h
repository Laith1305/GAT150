#pragma once
#include "RendererComponent.h"


namespace viper {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;

		res_t<Texture> texture;

	public:

		CLASS_PROTOTYPE(SpriteRenderer)



		void Start() override;
		// Inherited via RendererComponent
		void Update(float dt) override;

		void Draw(Renderer& renderer) override;


		// Inherited via Serializable
		void Read(const json::value_t& value) override;

	};
}


