#ifndef _TEXTURE_H_INCLUDED
#define _TEXTURE_H_INCLUDED

#include <SDL.h>
#include "../graphics/color.hpp"
#include "../math/vector2.hpp"

class Text;

class Texture
{
public:
    Texture(uint32_t width, uint32_t height);
    Texture(uint32_t width, uint32_t height, Color bg);
    Texture(uint32_t width, uint32_t height, Color bg, Color border);
    Texture(const char* path);
    Texture(Text* text);
    ~Texture();

    SDL_Texture* GetTexture() const { return texture_; }
    Vec2<uint32_t> GetSize() const;

    Color* ReadBuffer();
    void   LoadBuffer(Color* buffer);
    void   ReleaseBuffer(Color* buffer);

    void SetManagerOwner();
    bool IsManagerOwner();

private:
    SDL_Texture* texture_;

    bool manager_owns_;
};

#endif /* _TEXTURE_H_INCLUDED */
