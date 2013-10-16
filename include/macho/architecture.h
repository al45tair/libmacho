/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_ARCHITECTURE_H_
#define LIBMACHO_ARCHITECTURE_H_

#include "base.h"
#include "types.h"
#include <iostream>

BEGIN_MACHO_NS

class architecture {
public:
  macho::cpu_type    cpu_type;
  macho::cpu_subtype cpu_subtype;

  architecture(macho::cpu_type c, macho::cpu_subtype s) 
    : cpu_type(c), cpu_subtype(s) {}
};

// Output
std::ostream &operator<<(std::ostream &os, const architecture &a);

// Comparison operators
inline bool operator==(const architecture &a, const architecture &b) {
  return a.cpu_type == b.cpu_type && a.cpu_subtype == b.cpu_subtype;
}
inline bool operator!=(const architecture &a, const architecture &b) {
  return a.cpu_type != b.cpu_type || a.cpu_subtype != b.cpu_subtype;
}
inline bool operator<(const architecture &a, const architecture &b) {
  return a.cpu_type < b.cpu_type || (a.cpu_type == b.cpu_type
                                   && a.cpu_subtype < b.cpu_subtype);
}
inline bool operator<=(const architecture &a, const architecture &b) {
  return a.cpu_type < b.cpu_type || (a.cpu_type == b.cpu_type
                                   && a.cpu_subtype <= b.cpu_subtype);
}
inline bool operator>(const architecture &a, const architecture &b) {
  return a.cpu_type > b.cpu_type || (a.cpu_type == b.cpu_type
                                   && a.cpu_subtype > b.cpu_subtype);
}
inline bool operator>=(const architecture &a, const architecture &b) {
  return a.cpu_type > b.cpu_type || (a.cpu_type == b.cpu_type
                                   && a.cpu_subtype >= b.cpu_subtype);
}

END_MACHO_NS

#endif
