#include <macho/rpath_command.h>
#include <cstring>

using namespace macho;

load_command *
rpath_command::from_file(lowlevel::load_command *pcmd,
                         int fp, off_t base, off_t end,
                         bool swap, bool &retain)
{
  (void)fp;
  (void)base;
  (void)end;
  (void)retain;

  lowlevel::load_command cmd = swap ? bswap(*pcmd) : *pcmd;

  if (cmd.cmdsize < sizeof (lowlevel::rpath_command))
    return NULL;

  lowlevel::rpath_command *prpath = (lowlevel::rpath_command *)pcmd;
  lowlevel::rpath_command rpc = swap ? bswap(*prpath) : *prpath;

  if (rpc.path > rpc.cmdsize)
    return NULL;

  rpath_command *r = new rpath_command();
  
  const char *rpath = ((const char *)prpath) + rpc.path;
  int len = ::strnlen (rpath, rpc.cmdsize - sizeof (rpc));

  r->_rpath = std::string(rpath, len);

  return r;
}

