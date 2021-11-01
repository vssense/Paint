#ifndef _COLOR_HPP_INCLUDED
#define _COLOR_HPP_INCLUDED

#include <SDL.h>

const uint32_t kBlack       = 0xFF'00'00'00;
const uint32_t kWhite       = 0xFF'FF'FF'FF;
const uint32_t kLightPurple = 0xFF'E1'E1'FA;
const uint32_t kDarkGray    = 0xFF'40'40'40;
const uint32_t kLightYellow = 0xFF'FF'EE'91;
const uint32_t kYellow      = 0xFF'FF'E6'00;
const uint32_t kBlue        = 0xFF'00'80'FF;
const uint32_t kDarkBlue    = 0xFF'00'00'33;
const uint32_t kGray        = 0xFF'60'60'60;
const uint32_t kRed         = 0xFF'FD'59'59;

const size_t kByteSize = 8;

SDL_Color ConvertColor(uint32_t color);

uint8_t  GetB(uint32_t color);
uint8_t  GetG(uint32_t color);
uint8_t  GetR(uint32_t color);
uint8_t  GetA(uint32_t color);

#endif /* _COLOR_HPP_INCLUDED */