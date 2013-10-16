#include <macho/source_version_command.h>
#include <cstring>

using namespace macho;

load_command *
source_version_command::from_file(lowlevel::load_command *pcmd,
                                  int fp, off_t base, off_t end,
                                  bool swap, bool &retain)
{
  (void)fp;
  (void)base;
  (void)end;
  (void)retain;

  lowlevel::load_command cmd = swap ? bswap(*pcmd) : *pcmd;

  if (cmd.cmdsize < sizeof (lowlevel::source_version_command))
    return NULL;

  lowlevel::source_version_command
    *psvc = (lowlevel::source_version_command *)pcmd;
  lowlevel::source_version_command
    svc = swap ? bswap(*psvc) : *psvc;

  source_version_command *r = new source_version_command();
  
  r->_version = macho::source_version (svc.version >> 40,
                                       (svc.version >> 30) & 0x3ff,
                                       (svc.version >> 20) & 0x3ff,
                                       (svc.version >> 10) & 0x3ff,
                                       svc.version & 0x3ff);

  return r;
}

