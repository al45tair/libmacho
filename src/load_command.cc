#include <macho/load_command.h>
#include <macho/segment_command.h>
#include <macho/dylib_command.h>
#include <macho/uuid_command.h>
#include <macho/rpath_command.h>
#include <macho/umbrella_commands.h>
#include <macho/version_min_command.h>
#include <macho/source_version_command.h>
#include <macho/dylinker_command.h>

#include <cstdlib>

using namespace macho;

std::map<uint32_t, load_command::constructor_t> load_command::_constructors;
static bool _registered_builtins = false;

void
load_command::register_command(uint32_t cmd, 
                               load_command::constructor_t construct)
{
  _constructors[cmd] = construct;
}

load_command *
load_command::from_file (lowlevel::load_command *pcmd,
                         int fp, off_t base, off_t end,
                         bool swap, bool &retain)
{
  if (!_registered_builtins)
    load_command::register_builtin_commands();

  lowlevel::load_command lcmd = swap ? bswap(*pcmd) : *pcmd;

  auto it = _constructors.find (lcmd.cmd);

  if (it == _constructors.end()) {
    retain = true;
    return new unknown_load_command (lcmd.cmd, pcmd);
  }

  return (it->second)(pcmd, fp, base, end, swap, retain);
}

void
load_command::register_builtin_commands()
{
  // All the commands we know about are registered in here
  register_command (LC_SEGMENT, segment_command::from_file);
  register_command (LC_SEGMENT_64, segment_command::from_file);

  register_command (LC_ID_DYLIB, dylib_command::from_file);
  register_command (LC_LOAD_DYLIB, dylib_command::from_file);
  register_command (LC_LAZY_LOAD_DYLIB, dylib_command::from_file);
  register_command (LC_LOAD_WEAK_DYLIB, dylib_command::from_file);
  register_command (LC_LOAD_UPWARD_DYLIB, dylib_command::from_file);
  register_command (LC_REEXPORT_DYLIB, dylib_command::from_file);

  register_command (LC_UUID, uuid_command::from_file);
  register_command (LC_RPATH, rpath_command::from_file);

  register_command (LC_SUB_FRAMEWORK, sub_framework_command::from_file);
  register_command (LC_SUB_CLIENT, sub_client_command::from_file);
  register_command (LC_SUB_UMBRELLA, sub_umbrella_command::from_file);
  register_command (LC_SUB_LIBRARY, sub_library_command::from_file);

  register_command (LC_VERSION_MIN_MACOSX, version_min_command::from_file);
  register_command (LC_VERSION_MIN_IPHONEOS, version_min_command::from_file);

  register_command (LC_SOURCE_VERSION, source_version_command::from_file);

  register_command (LC_ID_DYLINKER, dylinker_command::from_file);
  register_command (LC_LOAD_DYLINKER, dylinker_command::from_file);
  register_command (LC_DYLD_ENVIRONMENT, dylinker_command::from_file);
}

unknown_load_command::~unknown_load_command()
{
  ::free ((void *)_cmd);
}

unknown_load_command::unknown_load_command(const unknown_load_command &other)
  : load_command(other.command())
{
  _cmd = (lowlevel::load_command *)::malloc (other._cmd->cmdsize);

  ::memcpy (_cmd, other._cmd, other._cmd->cmdsize);
}

load_command *
unknown_load_command::copy() const
{
  return new unknown_load_command (*this);
}
