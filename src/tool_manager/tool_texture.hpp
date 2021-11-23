#ifndef _TOOL_TEXTURE_HPP_INCLUDED
#define _TOOL_TEXTURE_HPP_INCLUDED

#include "../plugins/paint_plugin.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/renderer.hpp"

class ToolTexture : public ITexture
{
public:
    ToolTexture(Texture* texture) : texture_(texture) {}
    
    virtual void SetPixel(uint32_t x, uint32_t y, uint32_t color) override;
    virtual void DrawRect(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color) override;
    virtual void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color) override;
    virtual void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color,
                          uint32_t thickness) override;

    virtual uint32_t GetXSize() const override;
    virtual uint32_t GetYSize() const override;

private:
    Texture* texture_;
};

#endif /* _TOOL_TEXTURE_HPP_INCLUDED */
