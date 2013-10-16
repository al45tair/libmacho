/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_SOURCE_VERSION_COMMAND_H_
#define LIBMACHO_SOURCE_VERSION_COMMAND_H_

#include "load_command.h"
#include <string>
#include <iostream>

BEGIN_MACHO_NS

class source_version
{
public:
  unsigned a, b, c, d, e;

  source_version() : a(0), b(0), c(0), d(0), e(0) {}
  source_version(const source_version &other) 
    : a(other.a), b(other.b), c(other.c), d(other.d), e(other.e) {}
  source_version(unsigned _a, unsigned _b, unsigned _c, unsigned _d, unsigned _e)
    : a(_a), b(_b), c(_c), d(_d), e(_e) {}

  source_version &operator=(const source_version &other) {
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
    e = other.e;
    return *this;
  }

  bool operator<(const source_version &o) {
    return (a < o.a 
            || (a == o.a &&
                (b < o.b
                 || (b == o.b &&
                     (c < o.c
		      || (c == o.c &&
			  (d < o.d
			   || (d == o.d &&
			       e < o.e))))))));
  }
  bool operator<=(const source_version &o) {
    return (a < o.a 
            || (a == o.a &&
                (b < o.b
                 || (b == o.b &&
                     (c < o.c
		      || (c == o.c &&
			  (d < o.d
			   || (d == o.d &&
			       e <= o.e))))))));
  }
  bool operator==(const source_version &o) {
    return a == o.a && b == o.b && c == o.c && d == o.d && e == o.e;
  }
  bool operator!=(const source_version &o) {
    return a != o.a && b != o.b && c != o.c && d != o.d && e != o.e;
  }
  bool operator>=(const source_version &o) {
    return (a > o.a 
            || (a == o.a &&
                (b > o.b
                 || (b == o.b &&
                     (c > o.c
		      || (c == o.c &&
			  (d > o.d
			   || (d == o.d &&
			       e >= o.e))))))));
  }
  bool operator>(const source_version &o) {
    return (a > o.a 
            || (a == o.a &&
                (b > o.b
                 || (b == o.b &&
                     (c > o.c
		      || (c == o.c &&
			  (d > o.d
			   || (d == o.d &&
			       e > o.e))))))));
  }
};

inline std::ostream &operator<<(std::ostream &os, const source_version &v)
{
  return os << v.a << '.' << v.b << '.' << v.c << '.' << v.d << '.' << v.e;
}

class source_version_command : public load_command
{
private:
  source_version _version;

public:
  static load_command *from_file(lowlevel::load_command *pcmd,
                                 int fp, off_t base, off_t end,
                                 bool swap, bool &retain);

public:
  source_version_command() : load_command(LC_SOURCE_VERSION) {}
  source_version_command(const source_version_command &other)
    : load_command(other.command()), _version(other._version) {}
  ~source_version_command() {}

  load_command *copy() const {
    return new source_version_command(*this);
  }

  source_version version() const { return _version; }
  void set_version(const source_version &v) { _version = v; }
};

END_MACHO_NS

#endif
