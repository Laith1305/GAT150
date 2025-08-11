#include "Texture.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "Math/Vector2.h"
//#include "Renderer/Renderer.h"
#include "Renderer/Renderer.h"
#include "Math/Vector2.h"
#include "Logger.h"
namespace viper {

    Texture::~Texture()
    {
        // if texture exists, destroy texture
        if (m_texture != nullptr) SDL_DestroyTexture(m_texture);
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
        //SDL_Renderer* sdlRenderer = renderer.;
        // load image onto surface
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            Logger::Error("Could not load image: ", filename);
            return false;
        }

        // create texture from surface, texture is a friend class of renderer
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
        // once texture is created, surface can be freed up
        SDL_DestroySurface(surface);
        if (!m_texture)
        {
            Logger::Error("Could not create texture: ", filename);
            return false;
        }

        return true;
    }

    viper::vec2 Texture::GetSize()
    {
        //https://wiki.libsdl.org/SDL3/SDL_GetTextureSize

       

        return vec2(20, 30);
    }
}