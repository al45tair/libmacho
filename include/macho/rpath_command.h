/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_RPATH_COMMAND_H_
#define LIBMACHO_RPATH_COMMAND_H_

#include "load_command.h"
#include <string>

BEGIN_MACHO_NS

class rpath_command : public load_command
{
private:
  std::string _rpath;

public:
  static load_command *from_file(lowlevel::load_command *pcmd,
                                 int fp, off_t base, off_t end,
                                 bool swap, bool &retain);

public:
  rpath_command() : load_command(LC_RPATH) {}
  rpath_command(const rpath_command &other)
    : load_command(other.command()), _rpath(other._rpath) {}
  ~rpath_command() {}

  load_command *copy() const {
    return new rpath_command(*this);
  }

  std::string rpath() const { return _rpath; }
  void set_rpath (const std::string &s) { _rpath = s; }
};

END_MACHO_NS

#endif
