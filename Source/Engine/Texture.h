#pragma once
#include <string>
#include "Resources/Resource.h"
#include "Math/Vector2.h"
//#include "../../../GameExecutableProject/Source/Engine/Math/Vector2.h"


namespace viper {

	class Texture : public Resource{

	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);

		vec2 GetSize();

		friend class Renderer;


	private:
		struct SDL_Texture* m_texture{ nullptr };

	};
}