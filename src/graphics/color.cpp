#include "color.hpp"

SDL_Color ConvertColor(uint32_t color)
{
    return SDL_Color{GetR(color), GetG(color), GetB(color), GetA(color)};
}

uint8_t GetB(uint32_t color)
{
    return color & 0xFF;
}

uint8_t GetG(uint32_t color)
{
    return (color >> kByteSize) & 0xFF;
}

uint8_t GetR(uint32_t color)
{
    return (color >> (2 * kByteSize)) & 0xFF;
}

uint8_t GetA(uint32_t color)
{
    return (color >> (3 * kByteSize)) & 0xFF;
}
