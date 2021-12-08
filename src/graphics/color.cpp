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
