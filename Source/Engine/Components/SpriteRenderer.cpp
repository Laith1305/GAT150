#include "EnginePCH.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"

namespace viper {

	void SpriteRenderer::Update(float dt){
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer){
		renderer.DrawTexture(Resources().Get<Texture>(textureName, renderer).get(), 
			owner->transform.position.x,
			owner->transform.position.y, 
			owner->transform.rotation, 
			owner->transform.scale);
	}

}