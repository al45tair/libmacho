#include <macho/version_min_command.h>
#include <cstring>

using namespace macho;

load_command *
version_min_command::from_file(lowlevel::load_command *pcmd,
                         int fp, off_t base, off_t end,
                         bool swap, bool &retain)
{
  (void)fp;
  (void)base;
  (void)end;
  (void)retain;

  lowlevel::load_command cmd = swap ? bswap(*pcmd) : *pcmd;

  if (cmd.cmdsize < sizeof (lowlevel::version_min_command))
    return NULL;

  lowlevel::version_min_command *pvmc = (lowlevel::version_min_command *)pcmd;
  lowlevel::version_min_command vmc = swap ? bswap(*pvmc) : *pvmc;

  version_min_command *r = new version_min_command(vmc.cmd);
  
  r->_version = macho::version (vmc.version >> 16,
                                (vmc.version >> 8) & 0xff,
                                vmc.version & 0xff);
  r->_sdk = macho::version (vmc.sdk >> 16,
                            (vmc.sdk >> 8) & 0xff,
                            vmc.sdk & 0xff);

  return r;
}

