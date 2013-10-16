/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_VERSION_COMMAND_H_
#define LIBMACHO_VERSION_COMMAND_H_

#include "load_command.h"
#include <string>
#include <iostream>

BEGIN_MACHO_NS

class version
{
public:
  unsigned x;
  unsigned y;
  unsigned z;

  version() : x(0), y(0), z(0) {}
  version(const version &other) : x(other.x), y(other.y), z(other.z) {}
  version(unsigned _x, unsigned _y, unsigned _z) : x(_x), y(_y), z(_z) {}

  version &operator=(const version &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  bool operator<(const version &o) {
    return x < o.x || (x == o.x && (y < o.y || (y == o.y && z < o.z)));
  }
  bool operator<=(const version &o) {
    return x < o.x || (x == o.x && (y < o.y || (y == o.y && z <= o.z)));
  }
  bool operator==(const version &o) {
    return x == o.x && y == o.y && z == o.z;
  }
  bool operator!=(const version &o) {
    return x != o.x && y != o.y && z != o.z;
  }
  bool operator>=(const version &o) {
    return x > o.x || (x == o.x && (y > o.y || (y == o.y && z >= o.z)));
  }
  bool operator>(const version &o) {
    return x > o.x || (x == o.x && (y > o.y || (y == o.y && z > o.z)));
  }
};

inline std::ostream &operator<<(std::ostream &os, const version &v)
{
  return os << v.x << '.' << v.y << '.' << v.z;
}

class version_min_command : public load_command
{
private:
  version _version;
  version _sdk;

public:
  static load_command *from_file(lowlevel::load_command *pcmd,
                                 int fp, off_t base, off_t end,
                                 bool swap, bool &retain);

public:
  version_min_command(uint32_t cmd) : load_command(cmd) {}
  version_min_command(const version_min_command &other)
    : load_command(other.command()), _version(other._version), _sdk(other._sdk) {}
  ~version_min_command() {}

  load_command *copy() const {
    return new version_min_command(*this);
  }

  class version version() const { return _version; }
  void set_version(const class version &v) { _version = v; }
  class version sdk() const { return _sdk; }
  void set_sdk(const class version &v) { _sdk = v; }
};

END_MACHO_NS

#endif
