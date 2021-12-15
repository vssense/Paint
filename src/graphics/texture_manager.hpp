#ifndef _TEXTURE_MANAGER_HPP_INCLUDED
#define _TEXTURE_MANAGER_HPP_INCLUDED

#include <unordered_map>
#include <string>
#include <cassert>

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

private:
    std::unordered_map<std::string, Texture*> loaded_textures_;

    static TextureManager* instance_;
};

#endif /* _TEXTURE_MANAGER_HPP_INCLUDED */