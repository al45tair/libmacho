/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_OBJECT_H_
#define LIBMACHO_OBJECT_H_

#include "base.h"
#include "types.h"
#include "architecture.h"
#include "load_command.h"

#include <vector>

BEGIN_MACHO_NS

class object
{
private:
  architecture                _architecture;
  uint32_t                    _file_type;
  uint32_t                    _flags;
  std::vector<load_command *> _load_commands;

public:
  class lcvector {
  private:
    typedef std::vector<load_command *> vec;

    vec &_cmds;

    friend class object;

  protected:
    lcvector(std::vector<load_command *> &cmds) : _cmds(cmds) { }
    
  public:
    typedef load_command         value_type;
    typedef load_command        &reference;
    typedef const load_command  &const_reference;
    typedef load_command        *pointer;
    typedef const load_command  *const_pointer;
    typedef vec::difference_type difference_type;
    typedef vec::size_type       size_type;

    class iterator {
    private:
      vec::iterator _it;

      friend class lcvector;
      friend class object;

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

      friend class lcvector;
      friend class object;

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
    size_type size() { return _cmds.size(); }

    reference operator[](size_type n) { return *_cmds[n]; }
    const_reference operator[](size_type n) const { return *_cmds[n]; }
    reference at(size_type n) { return *_cmds.at(n); }
    const_reference at(size_type n) const { return *_cmds.at(n); }
    reference front() { return *_cmds.front(); }
    const_reference front() const { return *_cmds.front(); }
    reference back() { return *_cmds.back(); }
    const_reference back() const { return *_cmds.back(); }
    
    iterator begin() { return iterator(_cmds.begin()); }
    iterator end()   { return iterator(_cmds.end()); }
    const_iterator begin() const { return const_iterator(_cmds.begin()); }
    const_iterator end() const   { return const_iterator(_cmds.end()); }
    const_iterator cbegin() const { return const_iterator(_cmds.cbegin()); }
    const_iterator cend() const   { return const_iterator(_cmds.cend()); }
  };

public:
  object(architecture arch, uint32_t file_type, uint32_t flags=0)
    : _architecture(arch), _file_type(file_type), _flags(flags) {}
  object(const object &other)
    : _architecture(other._architecture), _file_type(other._file_type),
      _flags(other._flags) {
    for (auto i = other._load_commands.begin();
         i != other._load_commands.end();
         ++i)
      _load_commands.push_back((*i)->copy());
  }
  ~object();

  architecture         architecture() const { return _architecture; }
  uint32_t             file_type() const { return _file_type; }
  uint32_t             flags() const { return _flags; }
  void                 set_flags(uint32_t f) { _flags = f; }

  // lcvector is a vector-like object, without mutation
  lcvector load_commands() { return lcvector(_load_commands); }

  void add_load_command (load_command *lc) {
    _load_commands.push_back(lc);
  }
  void remove_load_command (lcvector::iterator p) {
    delete *p._it;
    _load_commands.erase(p._it);
  }
  void remove_load_commands (lcvector::iterator b, lcvector::iterator e) {
    for (auto i = b._it; i < e._it; ++i)
      delete *i;
    _load_commands.erase(b._it, e._it);
  }
  void remove_all_load_commands() {
    for (auto i = _load_commands.begin(); i < _load_commands.end(); ++i)
      delete *i;
    _load_commands.clear();
  }
  void insert_load_command (lcvector::iterator p, load_command *lc) {
    _load_commands.insert(p._it, lc);
  }
  void swap_load_commands (lcvector::iterator a, lcvector::iterator b) {
    load_command *t = *a._it;
    *a._it = *b._it;
    *b._it = t;
  }
};

inline object::lcvector::iterator
operator+(const object::lcvector::iterator &a,
          object::lcvector::difference_type d) {
  return object::lcvector::iterator(a._it + d);
}
inline object::lcvector::iterator
operator+(object::lcvector::difference_type d,
          const object::lcvector::iterator &a) {
  return object::lcvector::iterator(a._it + d);
}
inline object::lcvector::iterator
operator-(const object::lcvector::iterator &a,
          object::lcvector::difference_type d) {
  return object::lcvector::iterator(a._it - d);
}
inline object::lcvector::difference_type
operator-(const object::lcvector::iterator &a,
          const object::lcvector::iterator &b) {
  return a._it - b._it;
}

inline object::lcvector::const_iterator 
operator+(const object::lcvector::const_iterator &a,
          object::lcvector::difference_type d) {
  return object::lcvector::const_iterator(a._it + d);
}
inline object::lcvector::const_iterator
operator+(object::lcvector::difference_type d,
          const object::lcvector::const_iterator &a) {
  return object::lcvector::const_iterator(a._it + d);
}
inline object::lcvector::const_iterator
operator-(const object::lcvector::const_iterator &a,
          object::lcvector::difference_type d) {
  return object::lcvector::const_iterator(a._it - d);
}
inline object::lcvector::difference_type
operator-(const object::lcvector::const_iterator &a,
          const object::lcvector::const_iterator &b) {
  return a._it - b._it;
}

END_MACHO_NS

#endif
