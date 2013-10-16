/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_DYLINKER_COMMAND_H_
#define LIBMACHO_DYLINKER_COMMAND_H_

#include "load_command.h"
#include <string>

BEGIN_MACHO_NS

class dylinker_command : public load_command
{
private:
  std::string _name;

public:
  static load_command *from_file(lowlevel::load_command *pcmd,
                                 int fp, off_t base, off_t end,
                                 bool swap, bool &retain);

public:
  dylinker_command(uint32_t cmd) : load_command(cmd) {}
  dylinker_command(const dylinker_command &other)
    : load_command(other.command()), _name(other._name) {}
  ~dylinker_command() {}

  load_command *copy() const {
    return new dylinker_command(*this);
  }

  std::string name() const { return _name; }
  void set_name (const std::string &s) { _name = s; }
};

END_MACHO_NS

#endif
