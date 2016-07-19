#include "Theme.h"

#include <sstream>

using namespace std;

Theme::Theme()
{
	manager.put(new TextureManager());
}

p<Texture> Theme::GetTexture(string name)
{
	for ( int i = 0; i < name.length(); i++)
	{
		if (name[i] =='/')
		{
			name.replace(i, 1, "\\");
		}
	}
	name = FullPathTo(name);
	auto it = textures.find(name);
	if (it == textures.end())
	{
		p<Texture> deco(new Texture(this->manager, name), 1, boost::bind(&Theme::OnUnusedDeco, this, _1));
		textures.insert(pair<string, p<Texture>>(name, deco));
		return deco;
	}
	else
	{
		return it->second;
	}
}

void Theme::OnUnusedDeco(Texture * texture)
{
	auto it = textures.find(texture->Path());
	if (it != textures.end())
		textures.erase(it);
}