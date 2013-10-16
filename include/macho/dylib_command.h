/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_DYLIB_COMMAND_H_
#define LIBMACHO_DYLIB_COMMAND_H_

#include "load_command.h"
#include <string>

BEGIN_MACHO_NS

class dylib_command : public load_command
{
private:
  std::string _name;
  uint32_t    _timestamp;
  uint32_t    _version;
  uint32_t    _compat_version;

public:
  static load_command *from_file(lowlevel::load_command *pcmd,
                                 int fp, off_t base, off_t end,
                                 bool swap, bool &retain);

public:
  dylib_command(uint32_t cmd) : load_command(cmd) {}
  dylib_command(const dylib_command &other)
    : load_command(other.command()),
      _name(other._name), _timestamp(other._timestamp),
      _version(other._version), _compat_version(other._compat_version)
  {}
  ~dylib_command() {}

  load_command *copy() const {
    return new dylib_command(*this);
  }

  std::string name() const { return _name; }
  void set_name(const std::string &s) { _name = s; }

  uint32_t timestamp() const { return _timestamp; }
  void set_timestamp(uint32_t t) { _timestamp = t; }
  uint32_t version() const { return _version; }
  void set_version(uint32_t v) { _version = v; }
  uint32_t compatibility_version() const { return _compat_version; }
  void set_compatibility_version(uint32_t v) { _compat_version = v; }
};

END_MACHO_NS

#endif
