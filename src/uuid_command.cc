#include <macho/uuid_command.h>
#include <cstring>

using namespace macho;

load_command *
uuid_command::from_file(lowlevel::load_command *pcmd,
                        int fp, off_t base, off_t end,
                        bool swap, bool &retain)
{
  (void)fp;
  (void)base;
  (void)end;
  (void)retain;

  lowlevel::load_command cmd = swap ? bswap(*pcmd) : *pcmd;

  if (cmd.cmdsize < sizeof (lowlevel::uuid_command))
    return NULL;

  lowlevel::uuid_command *puuid = (lowlevel::uuid_command *)pcmd;
  uuid_command *u = new uuid_command();
  
  ::memcpy (u->_uuid, puuid->uuid, 16);

  return u;
}

