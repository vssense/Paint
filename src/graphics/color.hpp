#ifndef _COLOR_HPP_INCLUDED
#define _COLOR_HPP_INCLUDED

#include <SDL.h>

typedef uint32_t Color;

const Color kBlack       = 0xFF'00'00'00;
const Color kWhite       = 0xFF'FF'FF'FF;
const Color kLightPurple = 0xFF'E1'E1'FA;
const Color kDarkGray    = 0xFF'40'40'40;
const Color kLightYellow = 0xFF'FF'EE'91;
const Color kYellow      = 0xFF'FF'E6'00;
const Color kBlue        = 0xFF'00'80'FF;
const Color kDarkBlue    = 0xFF'00'00'33;
const Color kGray        = 0xFF'60'60'60;
const Color kRed         = 0xFF'FD'59'59;
const Color kTransparent = 0x00'00'00'00;

const size_t kByteSize = 8;

SDL_Color ConvertColor(Color color);

uint8_t  GetB(Color color);
uint8_t  GetG(Color color);
uint8_t  GetR(Color color);
uint8_t  GetA(Color color);

#endif /* _COLOR_HPP_INCLUDED */
