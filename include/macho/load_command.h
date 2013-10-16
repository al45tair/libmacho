/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_LOAD_COMMAND_H_
#define LIBMACHO_LOAD_COMMAND_H_

#include "base.h"
#include "types.h"
#include <cstdlib>
#include <map>

BEGIN_MACHO_NS

class load_command
{
private:
  uint32_t _cmd;
  
public:
  // Set retain to true if you want to keep the load_command structure
  typedef load_command *(*constructor_t)(lowlevel::load_command *pcmd,
                                         int fp, off_t base, off_t end,
                                         bool swap, bool &retain);

private:
  static std::map<uint32_t, constructor_t> _constructors;

public:
  static void register_builtin_commands();
  static void register_command(uint32_t cmd, constructor_t construct);
  static load_command *from_file(lowlevel::load_command *pcmd,
                                 int fp, off_t base, off_t end,
                                 bool swap, bool &retain);

public:
  load_command(uint32_t cmd) : _cmd(cmd) {}
  virtual ~load_command() { }

  virtual load_command *copy () const = 0;

  uint32_t command() const { return _cmd; }
};

/* If we meet a command we don't know, we'll copy it as a blob of data; note
   that, in the general case, this might be insufficient to reproduce the
   original file---since it's possible that the command refers to a block of
   data somewhere else in the file. */
class unknown_load_command : public load_command
{
private:
  lowlevel::load_command *_cmd;

public:
  unknown_load_command(uint32_t cmd, lowlevel::load_command *pcmd)
    : load_command(cmd), _cmd(pcmd) {}
  unknown_load_command(const unknown_load_command &other);
  ~unknown_load_command();
  
  load_command *copy() const;

  const void *data() const { return _cmd + 1; }
  size_t size() const { return _cmd->cmdsize - sizeof (lowlevel::load_command); }
};

END_MACHO_NS

#endif
