/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_UUID_COMMAND_H_
#define LIBMACHO_UUID_COMMAND_H_

#include "load_command.h"
#include <string>
#include <cstring>

BEGIN_MACHO_NS

class uuid_command : public load_command
{
private:
  uint8_t _uuid[16];

public:
  static load_command *from_file(lowlevel::load_command *pcmd,
                                 int fp, off_t base, off_t end,
                                 bool swap, bool &retain);

public:
  uuid_command() : load_command(LC_UUID) {}
  uuid_command(const uuid_command &other)
    : load_command(other.command())
  {
    ::memcpy (_uuid, other._uuid, 16);
  }
  ~uuid_command() {}

  load_command *copy() const {
    return new uuid_command(*this);
  }

  const uint8_t *uuid() const { return _uuid; }
  void set_uuid (const uint8_t *puuid) { ::memcpy (_uuid, puuid, 16); }
};

END_MACHO_NS

#endif
