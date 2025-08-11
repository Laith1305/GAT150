#include "Font.h"
#include "Logger.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

namespace viper {
	Font::~Font() {
		if (m_ttfFont != nullptr) {
			TTF_CloseFont(m_ttfFont);
		}
	}

	bool Font::Load(const std::string& name, float fontSize) {
		m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (m_ttfFont == nullptr) {
			Logger::Error("Could not load font: ", name);
			return false;
		}

		return true;
	}
}