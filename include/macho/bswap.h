/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_BSWAP_H_
#define LIBMACHO_BSWAP_H_

#include "base.h"
#include <cstdint.h>

BEGIN_MACHO_NS

using std::uint16_t;
using std::uint32_t;
using std::uint64_t;

inline constexpr uint16_t bswap(uint16_t u) 
{
  return ((u >> 8) & 0xff) | (u << 8);
}

inline constexpr uint32_t bswap(uint32_t u)
{
  u = ((u >> 8) & 0x00ff00ff) | ((u & 0x00ff00ff) << 8);
  return ((u >> 16) & 0x0000ffff) | (u << 16);
}

inline constexpr uint64_t bswap(uint64_t u)
{
  u = ((u >> 8) & 0x00ff00ff00ff00ff) | ((u & 0x00ff00ff00ff00ff) << 8);
  u = ((u >> 16) & 0x0000ffff0000ffff) | ((u & 0x0000ffff0000ffff) << 16);
  return ((u >> 32) & 0x00000000ffffffff) | (u << 32);
}

END_MACHO_NS

#endif
