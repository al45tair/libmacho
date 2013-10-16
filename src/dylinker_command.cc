#include <macho/dylinker_command.h>
#include <cstring>

using namespace macho;

load_command *
dylinker_command::from_file(lowlevel::load_command *pcmd,
                         int fp, off_t base, off_t end,
                         bool swap, bool &retain)
{
  (void)fp;
  (void)base;
  (void)end;
  (void)retain;

  lowlevel::load_command cmd = swap ? bswap(*pcmd) : *pcmd;

  if (cmd.cmdsize < sizeof (lowlevel::dylinker_command))
    return NULL;

  lowlevel::dylinker_command *pdyl = (lowlevel::dylinker_command *)pcmd;
  lowlevel::dylinker_command rpc = swap ? bswap(*pdyl) : *pdyl;

  if (rpc.path > rpc.cmdsize)
    return NULL;

  dylinker_command *r = new dylinker_command(rpc.cmd);
  
  const char *name = ((const char *)pdyl) + rpc.path;
  int len = ::strnlen (name, rpc.cmdsize - sizeof (rpc));

  r->_name = std::string(name, len);

  return r;
}

