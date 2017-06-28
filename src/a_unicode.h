#pragma once

#include "types.h"
#include <string>
#include <vector>
#include <utf8.h>
#include <SDL2/SDL.h>

bool IsSDLKeysymValidSymbol(SDL_Keysym *keysym);
void DoBackspaceForString(std::string *value);
std::string GetStringFromUnicode(Uint16 code);
int utf8len(std::string & value);
