#include "color.hpp"

SDL_Color ConvertColor(Color color)
{
    return SDL_Color{GetR(color), GetG(color), GetB(color), GetA(color)};
}

uint8_t GetB(Color color)
{
    return color & 0xFF;
}

uint8_t GetG(Color color)
{
    return (color >> kByteSize) & 0xFF;
}

uint8_t GetR(Color color)
{
    return (color >> (2 * kByteSize)) & 0xFF;
}

uint8_t GetA(Color color)
{
    return (color >> (3 * kByteSize)) & 0xFF;
}

Color SetB(Color color, uint8_t black)
{
    return (color & 0x00) | black;
}

Color SetG(Color color, uint8_t green)
{
    color = (color >> kByteSize) & 0x00; 
    return (color >> kByteSize) | green;
}

Color SetR(Color color, uint8_t red)
{
    color = (color >> 2 * kByteSize) & 0x00; 
    return (color >> 2 * kByteSize) | red;
}

Color SetA(Color color, uint8_t alpha)
{
    color = (color >> 3 * kByteSize) & 0x00; 
    return (color >> 3 * kByteSize) | alpha;
}
