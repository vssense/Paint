#include "texture_manager.hpp"
#include "texture.hpp"

TextureManager* TextureManager::instance_ = nullptr;

TextureManager::TextureManager() {}

TextureManager* TextureManager::GetInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new TextureManager;
    }

    return instance_;
}

TextureManager::~TextureManager()
{
    for (auto it = loaded_textures_.begin(); it != loaded_textures_.end(); ++it)
    {
        delete it->second;
    }
}

void TextureManager::Destruct()
{
    if (instance_ != nullptr)
    {
        delete instance_;
        instance_ = nullptr;
    }
}

Texture* TextureManager::GetTexture(const std::string& path)
{
    auto it = loaded_textures_.find(path);

    if (it != loaded_textures_.end())
    {
        return it->second;
    }

    Texture* new_texture = new Texture(path.c_str());
    if (new_texture == nullptr)
    {
        fprintf(stderr, "Can't load texture from %s\n", path.c_str());
        return nullptr;
    }

    new_texture->SetManagerOwner();
    loaded_textures_.insert(std::pair<std::string, Texture*>(path, new_texture));

    return new_texture;
}
