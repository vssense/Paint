#ifndef _TEXTURE_MANAGER_HPP_INCLUDED
#define _TEXTURE_MANAGER_HPP_INCLUDED

#include <unordered_map>
#include <string>
#include <cassert>

constexpr const char* kCloseButtonPath     = "img/close.bmp";
constexpr const char* kClose2ButtonPath    = "img/close2.bmp";
constexpr const char* kHorizontalThumbPath = "img/hthumb.bmp";
constexpr const char* kVerticalThumbPath   = "img/vthumb.bmp";
constexpr const char* kNotFoundPath        = "img/not_found.bmp";
constexpr const char* kSliderThumbPath     = "img/thumb.bmp";
constexpr const char* kSliderTrackPath     = "img/track.bmp";

class Texture;

class TextureManager
{
private:
    TextureManager();
    ~TextureManager();

public:
    static TextureManager* GetInstance();
    static void Destruct();

    Texture* GetTexture(const std::string& path);
    Texture* GetDefaulTexture() const;

private:
    std::unordered_map<std::string, Texture*> loaded_textures_;
    Texture* default_texture_;

    static TextureManager* instance_;
};

#endif /* _TEXTURE_MANAGER_HPP_INCLUDED */