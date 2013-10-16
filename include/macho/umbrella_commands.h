/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_UMBRELLA_COMMANDS_H_
#define LIBMACHO_UMBRELLA_COMMANDS_H_

#include "load_command.h"
#include <string>

BEGIN_MACHO_NS

class sub_framework_command : public load_command
{
private:
  std::string _umbrella;

public:
  static load_command *from_file(lowlevel::load_command *pcmd,
                                 int fp, off_t base, off_t end,
                                 bool swap, bool &retain);

public:
  sub_framework_command() : load_command(LC_SUB_FRAMEWORK) {}
  sub_framework_command(const sub_framework_command &other)
    : load_command(other.command()), _umbrella(other._umbrella) {}
  ~sub_framework_command() {}

  load_command *copy() const {
    return new sub_framework_command(*this);
  }

  std::string umbrella() const { return _umbrella; }
  void set_umbrella (const std::string &s) { _umbrella = s; }
};

class sub_client_command : public load_command
{
private:
  std::string _client;

public:
  static load_command *from_file(lowlevel::load_command *pcmd,
                                 int fp, off_t base, off_t end,
                                 bool swap, bool &retain);

public:
  sub_client_command() : load_command(LC_SUB_CLIENT) {}
  sub_client_command(const sub_client_command &other)
    : load_command(other.command()), _client(other._client) {}
  ~sub_client_command() {}

  load_command *copy() const {
    return new sub_client_command(*this);
  }

  std::string client() const { return _client; }
  void set_client (const std::string &s) { _client = s; }
};

class sub_umbrella_command : public load_command
{
private:
  std::string _sub_umbrella;

public:
  static load_command *from_file(lowlevel::load_command *pcmd,
                                 int fp, off_t base, off_t end,
                                 bool swap, bool &retain);

public:
  sub_umbrella_command() : load_command(LC_SUB_UMBRELLA) {}
  sub_umbrella_command(const sub_umbrella_command &other)
    : load_command(other.command()), _sub_umbrella(other._sub_umbrella) {}
  ~sub_umbrella_command() {}

  load_command *copy() const {
    return new sub_umbrella_command(*this);
  }

  std::string sub_umbrella() const { return _sub_umbrella; }
  void set_sub_umbrella (const std::string &s) { _sub_umbrella = s; }
};

class sub_library_command : public load_command
{
private:
  std::string _sub_library;

public:
  static load_command *from_file(lowlevel::load_command *pcmd,
                                 int fp, off_t base, off_t end,
                                 bool swap, bool &retain);

public:
  sub_library_command() : load_command(LC_SUB_LIBRARY) {}
  sub_library_command(const sub_library_command &other)
    : load_command(other.command()), _sub_library(other._sub_library) {}
  ~sub_library_command() {}

  load_command *copy() const {
    return new sub_library_command(*this);
  }

  std::string sub_library() const { return _sub_library; }
  void set_sub_library (const std::string &s) { _sub_library = s; }
};

END_MACHO_NS

#endif
