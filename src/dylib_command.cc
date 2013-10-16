#include <macho/dylib_command.h>
#include <cstring>

using namespace macho;

load_command *
dylib_command::from_file(lowlevel::load_command *pcmd,
                         int fp, off_t base, off_t end,
                         bool swap, bool &retain)
{
  (void)fp;
  (void)base;
  (void)end;
  (void)retain;

  lowlevel::load_command cmd = swap ? bswap(*pcmd) : *pcmd;

  if (cmd.cmdsize < sizeof (lowlevel::dylib_command))
    return NULL;

  lowlevel::dylib_command *pdlc = (lowlevel::dylib_command *)pcmd;
  lowlevel::dylib_command dlc = swap ? bswap(*pdlc) : *pdlc;

  if (dlc.dylib.name > dlc.cmdsize)
    return NULL;

  dylib_command *d = new dylib_command (dlc.cmd);

  const char *pname = ((const char *)pdlc) + dlc.dylib.name;
  int len = ::strnlen (pname, dlc.cmdsize - sizeof(dlc));

  d->_name = std::string(pname, len);
  d->_timestamp = dlc.dylib.timestamp;
  d->_version = dlc.dylib.current_version;
  d->_compat_version = dlc.dylib.compatibility_version;

  return d;
}

