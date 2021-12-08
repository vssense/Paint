#ifndef _TOOL_TEXTURE_HPP_INCLUDED
#define _TOOL_TEXTURE_HPP_INCLUDED

#include "../../plugins/plugin.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/renderer.hpp"

using namespace plugin;

#define GetHeight GetHieght

class APITextureFactory : public ITextureFactory
{
public:
    APITextureFactory() {}
    virtual ITexture* CreateTexture(const char* filename) override;
    virtual ITexture* CreateTexture(int32_t width, int32_t height) override;
};

class APITexture : public ITexture
{
public:
    APITexture(Texture* texture) : texture_(texture) {}
    
    virtual int32_t GetWidth() override;
    virtual int32_t GetHeight() override;

    virtual Buffer ReadBuffer() override;
    virtual void   ReleaseBuffer(Buffer buffer) override;
    virtual void   LoadBuffer(Buffer buffer) override;

    virtual void Clear(Color color) override;
    virtual void Present() override;

    virtual void DrawLine     (int32_t x0, int32_t y0, int32_t x1, int32_t y1, Color color) override;
    virtual void DrawThickLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t thickness, Color color) override;
    virtual void DrawCircle   (int32_t x, int32_t y, int32_t radius, Color color) override;
    virtual void DrawRect     (int32_t x, int32_t y, int32_t width, int32_t height, Color color) override;

    virtual void CopyTexture(ITexture* texture, int32_t x, int32_t y, int32_t width, int32_t height) override;

private:
    Texture* texture_;
};

#endif /* _TOOL_TEXTURE_HPP_INCLUDED */
