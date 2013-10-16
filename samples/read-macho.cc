#include <macho/macho.h>
#include <iostream>

int
main (int argc, char **argv)
{
  if (argc != 2) {
    std::cerr << "usage: read-macho <mach-o file>" << std::endl;
    return 1;
  }

  macho::file *f = macho::file::read (argv[1]);

  if (!f) {
    std::cerr << "unable to read file \"" << argv[1] << "\"" << std::endl;
    return 1;
  }

  for (auto i = f->begin(); i != f->end(); ++i) {
    macho::object &o = *i;

    std::cout << o.architecture() << std::endl;

    auto cmds = o.load_commands();
    for (auto i = cmds.begin(); i != cmds.end(); ++i) {
      if (i->command() == macho::LC_SEGMENT
          || i->command() == macho::LC_SEGMENT_64) {
        macho::segment_command *cmd = (macho::segment_command *)&*i;

        std::cout << "  " << cmd->name() << std::endl;

        for (auto s = cmd->begin(); s != cmd->end(); ++s) {
          const macho::section &sect = *s;

          std::cout << "    " << sect.name() << std::endl;
        }
      } else if (i->command() == macho::LC_LOAD_DYLIB) {
        macho::dylib_command *cmd = (macho::dylib_command *)&*i;
        std::cout << "  load dylib \"" << cmd->name() << "\"" << std::endl;
      } else if (i->command() == macho::LC_LOAD_WEAK_DYLIB) {
        macho::dylib_command *cmd = (macho::dylib_command *)&*i;
        std::cout << "  load weak dylib \"" << cmd->name() << "\"" << std::endl;
      } else if (i->command() == macho::LC_REEXPORT_DYLIB) {
        macho::dylib_command *cmd = (macho::dylib_command *)&*i;
        std::cout << "  reexport dylib \"" << cmd->name() << "\"" << std::endl;
      } else if (i->command() == macho::LC_ID_DYLIB) {
        macho::dylib_command *cmd = (macho::dylib_command *)&*i;
        std::cout << "  dylib ID \"" << cmd->name() << "\"" << std::endl;
      } else {
        std::cout << "  (CMD " << std::hex << i->command() << ")" << std::endl;
      }
    }
  }

  delete f;

  return 0;
}
