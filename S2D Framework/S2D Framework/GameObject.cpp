#include "GameObject.h"
#include "TextureManager.h"

void GameObject::Update(int elapsedTime) {}
void GameObject::Load()
{
	Texture->Load(TextureManager::TextureMap[_textureKey].c_str(), false);
}
