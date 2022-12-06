#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const GameObject& gO)
{
	Position = new S2D::Vector2(gO.Position->X, gO.Position->Y);
	SourceRect = new S2D::Rect(gO.SourceRect->X, gO.SourceRect->Y, gO.SourceRect->Width, gO.SourceRect->Height);
	_renderDepth = gO._renderDepth;
	_textureKey = gO._textureKey;
}

void GameObject::Update(int elapsedTime) {}
void GameObject::Load()
{
	Texture->Load(TextureManager::TextureMap[TextureManager::ToLower(_textureKey)].c_str(), false);
}

int GameObject::GetRenderDepth()
{
	return _renderDepth;
}

std::string GameObject::GetTextureKey()
{
	return _textureKey;
}
