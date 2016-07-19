#include "TextureManager.h"

#include "SDL_image.h"
#include "L.h"

using namespace std;

void loadTextureSize(std::string filename, int32_t * w, int32_t * h);
void loadGLTexture(std::string filename, GLuint texture, int32_t * w, int32_t * h);

TextureManager::TextureManager(void)
{
	modified = true;
}

TextureManager::~TextureManager(void)
{
}

void TextureManager::MapFileTexture(GLuint & texture, std::string path, int32_t & width, int32_t & height)
{
	auto it = files.find(path);
	if (it == files.end())
	{
		TextureInfo * tx = new TextureInfo();
		tx->textureID = 0;
		tx->links.insert(&texture);
		texture = 0;
		loadTextureSize(path, &(tx->width), &(tx->height));
		width = tx->width;
		height = tx->height;
		files.insert(pair<std::string, TextureInfo*>(path, tx));
		modified = true;
	}
	else
	{
		TextureInfo * tx = it->second;
		auto propit = tx->links.find(&texture);
		if (propit != tx->links.end())
		{
			texture = tx->textureID;
			width = tx->width;
			height = tx->height;
		}
		else
		{
			tx->links.insert(&texture);
			texture = tx->textureID;
			width = tx->width;
			height = tx->height;
		}
	}
}

void TextureManager::MapFileTexture(GLuint & texture, std::string path)
{
	auto it = files.find(path);
	if (it == files.end())
	{
		TextureInfo * tx = new TextureInfo();
		tx->textureID = 0;
		tx->links.insert(&texture);
		texture = 0;
		loadTextureSize(path, &(tx->width), &(tx->height));
		files.insert(pair<std::string, TextureInfo*>(path, tx));
		modified = true;
	}
	else
	{
		TextureInfo * tx = it->second;
		auto propit = tx->links.find(&texture);
		if (propit != tx->links.end())
		{
			texture = tx->textureID;
		}
		else
		{
			tx->links.insert(&texture);
			texture = tx->textureID;
		}
	}
}

void TextureManager::RemoveTexture(std::string path, GLuint & texture)
{
	auto it = files.find(path);
	if (it != files.end())
	{
		auto it2 = it->second->links.find(&texture);
		if (it2 != it->second->links.end())
		{
			it->second->links.erase(it2);
			if (it->second->links.size() == 0)
			{
				cout << "Texture deleted from memory." << endl;
				delete it->second;
				files.erase(it);
			}
		}
	}
	if (glIsTexture(texture))
		glDeleteTextures(1, &texture);
}

/* Quick utility function for texture creation */
static int powerOfTwo(int input) {
	int value = 1;

	while (value < input) {
		value <<= 1;
	}
	return value;
}

static SDL_Surface *prepGLTexture(SDL_Surface *surface, GLfloat *texCoords) {
	/* Use the surface width and height expanded to powers of 2 */
	int w = powerOfTwo(surface->w);
	int h = powerOfTwo(surface->h);
	if (texCoords != NULL) {
		texCoords[0] = 0.0f;					/* Min X */
		texCoords[1] = 0.0f;					/* Min Y */
		texCoords[2] = (GLfloat)surface->w / w;	/* Max X */
		texCoords[3] = (GLfloat)surface->h / h;	/* Max Y */
	}

	SDL_Surface *image = SDL_CreateRGBSurface(
		SDL_SWSURFACE,
		w, h,
		32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
		0x000000FF, 
		0x0000FF00, 
		0x00FF0000, 
		0xFF000000
#else
		0xFF000000,
		0x00FF0000, 
		0x0000FF00, 
		0x000000FF
#endif
	);
	if ( image == NULL ) {
		return 0;
	}

	/* Save the alpha blending attributes */
	Uint32 savedFlags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
	Uint8  savedAlpha = surface->format->alpha;
	if ( (savedFlags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		SDL_SetAlpha(surface, 0, 0);
	}

	SDL_Rect srcArea, destArea;
	/* Copy the surface into the GL texture image */
	srcArea.x = 0; destArea.x = 0;
	/* Copy it in at the bottom, because we're going to flip
	   this image upside-down in a moment
	*/
	srcArea.y = 0; destArea.y = h - surface->h;
	srcArea.w = surface->w;
	srcArea.h = surface->h;
	SDL_BlitSurface(surface, &srcArea, image, &destArea);

	/* Restore the alpha blending attributes */
	if ((savedFlags & SDL_SRCALPHA) == SDL_SRCALPHA) {
		SDL_SetAlpha(surface, savedFlags, savedAlpha);
	}

	/* Turn the image upside-down, because OpenGL textures
	   start at the bottom-left, instead of the top-left
	*/
#ifdef _MSC_VER
	Uint8 *line = new Uint8[image->pitch];
#else
	Uint8 line[image->pitch];
#endif
	/* These two make the following more readable */
	Uint8 *pixels = static_cast<Uint8*>(image->pixels);
	Uint16 pitch = image->pitch;
	int ybegin = 0;
	int yend = image->h - 1;

	// TODO: consider if this lock is legal/appropriate
	if (SDL_MUSTLOCK(image)) { SDL_LockSurface(image); }
	while (ybegin < yend) {
		memcpy(line, pixels + pitch*ybegin, pitch);
		memcpy(pixels + pitch*ybegin, pixels + pitch*yend, pitch);
		memcpy(pixels + pitch*yend, line, pitch);
		ybegin++;
		yend--;
	}
	if (SDL_MUSTLOCK(image)) { SDL_UnlockSurface(image); }

#ifdef _MSC_VER
	delete[] line;
#endif

	return image;
}

static SDL_Surface *load_img(std::string filename)
{
  //Image loaded
  SDL_Surface* loadedimage = NULL;
  //Image to be used
  SDL_Surface* usedimage = NULL;

  //Loads Image
  loadedimage = IMG_Load(filename.c_str());
 
  //Creates image to be used
  if(loadedimage != NULL)
  {
	  //return loadedimage;
    //Puts the file in a SDL acceptable format
    usedimage = prepGLTexture(loadedimage, NULL);

    //Frees the old surface
    SDL_FreeSurface(loadedimage);
  }
 
  //Returns the final image
  return usedimage;
}

void TextureManager::WindowResize()
{
	modified = true;
}

static void loadTextureSize(std::string filename, int32_t * w, int32_t * h)
{
	SDL_Surface * s = load_img(filename);
	if (s != NULL)
	{
		*w = s->w;
		*h = s->h;
	}
}

static void loadGLTexture(std::string filename, GLuint texture, int32_t * w, int32_t * h)
{
	l(string("Loading image: ") + filename, L_INFO);
	SDL_Surface * s = load_img(filename);
	
	if (s != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, texture);

		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (w != NULL)
			*w = s->w;
		if (h != NULL)
			*h = s->h;

		
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, s->w, s->h, GL_RGBA, GL_UNSIGNED_BYTE, s->pixels );
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, s->w, s->h, GL_RGBA, GL_UNSIGNED_BYTE, s->pixels );
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, s->w, s->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, s->pixels);

		/*glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA, s->w, s->h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, s->pixels);*/

		SDL_FreeSurface(s);
	}
	else
	{
		l("Failed to load image.", L_ERROR);
	}
}

void TextureManager::SceneStart()
{
	// check textures
	if (modified)
	{
		// initialize textures
		for (auto it = files.begin(); it != files.end(); ++it)
		{
			TextureInfo * tx = it->second;
			if (tx->textureID == 0)
			{
				glGenTextures(1, &(tx->textureID));
				for (auto it2 = tx->links.begin(); it2 != tx->links.end(); ++it2)
				{
					*(*it2) = tx->textureID;
				}
			}
			if (!glIsTexture(tx->textureID))
			{
				loadGLTexture(it->first, tx->textureID, &(tx->width), &(tx->height));
			}
		}
		modified = false;
	}
}