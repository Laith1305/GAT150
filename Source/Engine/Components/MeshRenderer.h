#pragma once
#include "Components/RendererComponent.h"
namespace viper {
	class MeshRenderer : public RendererComponent {
	public:
		std::string meshName;



	public:

		// Inherited via RendererComponent
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	};
}


