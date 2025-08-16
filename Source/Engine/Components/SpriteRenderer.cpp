#include "EnginePCH.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"

namespace viper {

	void SpriteRenderer::Update(float dt){
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer){


		auto texture = Resources().Get<Texture>(textureName, renderer).get();
		if (texture) {

			renderer.DrawTexture(*texture, 
				owner->transform.position.x,
				owner->transform.position.y, 
				owner->transform.rotation, 
				owner->transform.scale);  
		}
	}

}