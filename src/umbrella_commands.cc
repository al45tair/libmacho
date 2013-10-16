#include <macho/umbrella_commands.h>
#include <cstring>

using namespace macho;

load_command *
sub_framework_command::from_file(lowlevel::load_command *pcmd,
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

  lowlevel::sub_framework_command *psfc 
    = (lowlevel::sub_framework_command *)pcmd;
  lowlevel::sub_framework_command sfc = swap ? bswap(*psfc) : *psfc;

  if (sfc.umbrella > sfc.cmdsize)
    return NULL;

  sub_framework_command *c = new sub_framework_command();
  
  const char *umbrella = ((const char *)psfc) + sfc.umbrella;
  int len = ::strnlen (umbrella, sfc.cmdsize - sizeof (sfc));

  c->_umbrella = std::string(umbrella, len);

  return c;
}

load_command *
sub_client_command::from_file(lowlevel::load_command *pcmd,
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

  lowlevel::sub_client_command *pscc 
    = (lowlevel::sub_client_command *)pcmd;
  lowlevel::sub_client_command scc = swap ? bswap(*pscc) : *pscc;

  if (scc.client > scc.cmdsize)
    return NULL;

  sub_client_command *c = new sub_client_command();
  
  const char *client = ((const char *)pscc) + scc.client;
  int len = ::strnlen (client, scc.cmdsize - sizeof (scc));

  c->_client = std::string(client, len);

  return c;
}

load_command *
sub_umbrella_command::from_file(lowlevel::load_command *pcmd,
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

  lowlevel::sub_umbrella_command *psuc 
    = (lowlevel::sub_umbrella_command *)pcmd;
  lowlevel::sub_umbrella_command suc = swap ? bswap(*psuc) : *psuc;

  if (suc.sub_umbrella > suc.cmdsize)
    return NULL;

  sub_umbrella_command *c = new sub_umbrella_command();
  
  const char *sub_umbrella = ((const char *)psuc) + suc.sub_umbrella;
  int len = ::strnlen (sub_umbrella, suc.cmdsize - sizeof (suc));

  c->_sub_umbrella = std::string(sub_umbrella, len);

  return c;
}

load_command *
sub_library_command::from_file(lowlevel::load_command *pcmd,
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

  lowlevel::sub_library_command *pslc 
    = (lowlevel::sub_library_command *)pcmd;
  lowlevel::sub_library_command slc = swap ? bswap(*pslc) : *pslc;

  if (slc.sub_library > slc.cmdsize)
    return NULL;

  sub_library_command *c = new sub_library_command();
  
  const char *sub_library = ((const char *)pslc) + slc.sub_library;
  int len = ::strnlen (sub_library, slc.cmdsize - sizeof (slc));

  c->_sub_library = std::string(sub_library, len);

  return c;
}

