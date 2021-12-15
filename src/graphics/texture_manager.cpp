#include "texture_manager.hpp"
#include "texture.hpp"

const int kDefaultSize = 30;

TextureManager* TextureManager::instance_ = nullptr;

TextureManager::TextureManager()
    : default_texture_(nullptr)
{
    default_texture_ = GetTexture(kNotFoundPath);

    if (default_texture_ == nullptr)
    {
        assert(0);
        default_texture_ = new Texture(kDefaultSize, kDefaultSize, kRed, kYellow);
    }

    GetTexture(kCloseButtonPath);
    GetTexture(kClose2ButtonPath);
    GetTexture(kHorizontalThumbPath);
    GetTexture(kVerticalThumbPath);
    GetTexture(kNotFoundPath);
    GetTexture(kSliderThumbPath);
    GetTexture(kSliderTrackPath);
}

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
    if (new_texture->GetTexture() == nullptr)
    {
        delete new_texture;
        return default_texture_;
    }

    new_texture->SetManagerOwner();
    loaded_textures_.insert(std::pair<std::string, Texture*>(path, new_texture));

    return new_texture;
}

Texture* TextureManager::GetDefaulTexture() const
{
    return default_texture_;
}
