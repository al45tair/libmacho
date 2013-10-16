/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_SEGMENT_COMMAND_H_
#define LIBMACHO_SEGMENT_COMMAND_H_

#include "load_command.h"
#include "data.h"
#include <vector>
#include <string>

BEGIN_MACHO_NS

class relocation
{
private:
  bool     _scattered;
  bool     _external;
  bool     _pc_relative;
  int32_t  _offset;
  uint32_t _length;
  uint32_t _type;
  uint32_t _symbol_or_section;

public:
  relocation() {}
  relocation(int32_t addr, bool external, uint32_t symbol_or_section,
             uint32_t length, uint32_t type,
             bool pcrel=false, bool scattered=false)
    : _scattered(scattered), _external(external), _pc_relative(pcrel),
      _offset(addr), _length(length), _type(type),
      _symbol_or_section(symbol_or_section)
  {}

  bool is_scattered() const { return _scattered; }
  void set_scattered(bool s) { _scattered = s; }
  bool is_external() const { return _external; }
  bool is_pc_relative() const { return _pc_relative; }
  void set_pc_relative(bool p) { _pc_relative = p; }

  int32_t offset() const { return _offset; }
  void set_offset(int32_t ofs) { _offset = ofs; }
  uint32_t symbol() const { return _symbol_or_section; }
  uint32_t section() const { return _symbol_or_section; }
  void set_symbol(uint32_t sym) { _external = true; _symbol_or_section = sym; }
  void set_section(uint32_t sct) {
    _external = false;
    _symbol_or_section = sct;
  }
  uint32_t length() const { return _length; }
  void set_length(uint32_t l) { _length = l; }
  uint32_t type() const { return _type; }
  void set_type(uint32_t t) { _type = t; }
};

class section
{
public:
  typedef std::vector<relocation> rvector;

private:
  std::string _name;
  std::string _segment_name;
  uint64_t    _addr;
  uint64_t    _size;
  uint32_t    _alignment;
  std::vector<relocation> _relocations;

public:
  section(const std::string &name,
          const std::string &segment_name,
          uint64_t           addr,
          uint64_t           size,
          uint32_t           alignment)
    : _name(name), _segment_name(segment_name),
      _addr(addr), _size(size), _alignment(alignment)
  {}

  std::string name() const { return _name; }
  void set_name (const std::string &s) { _name = s; }
  std::string segment_name() const { return _segment_name; }
  void set_segment_name (const std::string &s) { _segment_name = s; }
  uint64_t addr() const { return _addr; }
  void set_addr(uint64_t addr) { _addr = addr; }
  uint64_t size() const { return _size; }
  void set_size(uint64_t size) { _size = size; }
  uint32_t alignment() const { return _alignment; }
  void set_alignment(uint32_t alignment) { _alignment = alignment; }

  const rvector &relocations() const { return _relocations; }

  void add_relocation(const relocation &r) { _relocations.push_back(r); }
  void remove_relocation(rvector::iterator p) {
    _relocations.erase(p);
  }
  void remove_relocations(rvector::iterator b, rvector::iterator e) {
    _relocations.erase(b, e);
  }
  void remove_all_relocations() {
    _relocations.clear();
  }
  void insert_relocation (rvector::iterator p, const relocation &r) {
    _relocations.insert(p, r);
  }
};

class segment_command : public load_command
{
private:
  typedef std::vector<section *>vec;

  std::string _name;
  uint64_t    _vm_addr;
  uint64_t    _vm_size;
  vm_prot     _max_prot;
  vm_prot     _init_prot;
  uint32_t    _flags;
  vec         _sections;
  data       *_data;

public:
  typedef section              value_type;
  typedef section             &reference;
  typedef const section       &const_reference;
  typedef section             *pointer;
  typedef const section       *const_pointer;
  typedef vec::difference_type difference_type;
  typedef vec::size_type       size_type;

  class iterator {
  private:
    vec::iterator _it;

    friend class segment_command;

  protected:
    iterator(vec::iterator it) : _it(it) {}

  public:
    iterator() {}
    iterator(const iterator &other) : _it(other._it) {}

    iterator &operator=(const iterator &o) { _it = o._it; return *this; }
    iterator &operator+=(difference_type d) { _it += d; return *this; }
    iterator &operator-=(difference_type d) { _it -= d; return *this; }

    bool operator==(const iterator &o) const { return _it == o._it; }
    bool operator!=(const iterator &o) const { return _it != o._it; }
    bool operator<(const iterator &o) const { return _it < o._it; }
    bool operator<=(const iterator &o) const { return _it <= o._it; }
    bool operator>(const iterator  &o) const { return _it > o._it; }
    bool operator>=(const iterator &o) const { return _it >= o._it; }

    reference operator*() { return **_it; }
    pointer operator->() { return *_it; }
    reference operator[](difference_type d) { return *_it[d]; }

    iterator &operator++() { ++_it; return *this; }
    iterator operator++(int) { return iterator(_it++); }
    iterator &operator--() { --_it; return *this; }
    iterator operator--(int) { return iterator(_it--); }

    friend iterator operator+(const iterator &a, difference_type d);
    friend iterator operator+(difference_type d, const iterator &a);
    friend iterator operator-(const iterator &a, difference_type d);
    friend difference_type operator-(const iterator &a, const iterator &b);
  };

  class const_iterator {
  private:
    vec::const_iterator _it;

    friend class segment_command;

  protected:
    const_iterator(vec::const_iterator it) : _it(it) {}

  public:
    const_iterator() {}
    const_iterator(const const_iterator &other) : _it(other._it) {}

    const_iterator &operator=(const const_iterator &o) { _it = o._it; return *this; }
    const_iterator &operator+=(difference_type d) { _it += d; return *this; }
    const_iterator &operator-=(difference_type d) { _it -= d; return *this; }

    bool operator==(const const_iterator &o) const { return _it == o._it; }
    bool operator!=(const const_iterator &o) const { return _it != o._it; }
    bool operator<(const const_iterator &o) const { return _it < o._it; }
    bool operator<=(const const_iterator &o) const { return _it <= o._it; }
    bool operator>(const const_iterator  &o) const { return _it > o._it; }
    bool operator>=(const const_iterator &o) const { return _it >= o._it; }

    const_reference operator*() { return **_it; }
    const_pointer operator->() { return *_it; }
    const_reference operator[](difference_type d) { return *_it[d]; }

    const_iterator &operator++() { ++_it; return *this; }
    const_iterator operator++(int) { return const_iterator(_it++); }
    const_iterator &operator--() { --_it; return *this; }
    const_iterator operator--(int) { return const_iterator(_it--); }

    friend const_iterator operator+(const const_iterator &a, difference_type d);
    friend const_iterator operator+(difference_type d, const const_iterator &a);
    friend const_iterator operator-(const const_iterator &a, difference_type d);
    friend difference_type operator-(const const_iterator &a,
                                     const const_iterator &b);
  };

  typedef std::reverse_iterator<iterator>       reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  
public:
  static load_command *from_file (lowlevel::load_command *pcmd,
                                  int fp, off_t base, off_t end,
                                  bool swap, bool &retain);

public:
  segment_command() : load_command(LC_SEGMENT), _data(NULL) {}
  segment_command(const segment_command &other)
    : load_command(other.command()),
      _name(other._name), _vm_addr(other._vm_addr), _vm_size(other._vm_size),
      _max_prot(other._max_prot), _init_prot(other._init_prot),
      _flags(other._flags), _sections(other._sections),
      _data(other._data)
  {
    if (_data)
      _data->retain();
  }
  ~segment_command();

  load_command *copy() const;

  std::string name() const { return _name; }
  void set_name(const std::string &s) { _name = s; }

  iterator begin() { return iterator(_sections.begin()); }
  iterator end()   { return iterator(_sections.end()); }
  const_iterator begin() const { return const_iterator(_sections.begin()); }
  const_iterator end() const   { return const_iterator(_sections.end()); }
  const_iterator cbegin() const { return const_iterator(_sections.cbegin()); }
  const_iterator cend() const   { return const_iterator(_sections.cend()); }

  uint64_t vm_addr() const { return _vm_addr; }
  void     set_vm_addr (uint64_t vmaddr) { _vm_addr = vmaddr; }
  uint64_t vm_size() const { return _vm_size; }
  void     set_vm_size (uint64_t vmsize) { _vm_size = vmsize; }
  vm_prot  maximum_protection() const { return _max_prot; }
  void     set_maximum_protection (vm_prot prot) { _max_prot = prot; }
  vm_prot  initial_protection() const { return _init_prot; }
  void     set_initial_protection (vm_prot prot) { _init_prot = prot; }
  uint32_t flags() const { return _flags; }
  void     set_flags (uint32_t flags) { _flags = flags; }
  data     *data() const { return _data; }
  void     set_data(class data *d) {
    d->retain();
    _data->release();
    _data = d;
  }
};

END_MACHO_NS

#endif
