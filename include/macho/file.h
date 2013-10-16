/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_FILE_H_
#define LIBMACHO_FILE_H_

#include "base.h"
#include "types.h"
#include "object.h"
#include <vector>

BEGIN_MACHO_NS

class file {
private:
  typedef std::vector<object *> vec;
  vec _objects;
  int _fp;

public:
  typedef object               value_type;
  typedef object              &reference;
  typedef const object        &const_reference;
  typedef object              *pointer;
  typedef const object        *const_pointer;
  typedef vec::difference_type difference_type;
  typedef vec::size_type       size_type;

  class iterator {
  private:
    vec::iterator _it;

    friend class file;

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

    friend class file;

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
  file() : _fp(-1) {}
  file(const file &other) : _objects(other._objects), _fp(-1) {}
  ~file();
    
  void close();

  iterator begin() { return iterator(_objects.begin()); }
  iterator end()   { return iterator(_objects.end()); }
  const_iterator begin() const { return const_iterator(_objects.begin()); }
  const_iterator end() const   { return const_iterator(_objects.end()); }
  const_iterator cbegin() const { return const_iterator(_objects.cbegin()); }
  const_iterator cend() const   { return const_iterator(_objects.cend()); }

  void add_object (object *ob) { _objects.push_back(ob); }
  void remove_object (iterator p) { delete *p._it; _objects.erase(p._it); }
  void remove_objects (iterator b, iterator e) {
    for (auto i = b._it; i < e._it; ++i)
      delete *i;
    _objects.erase(b._it, e._it);
  }
  void remove_all_objects() {
    for (auto i = _objects.begin(); i < _objects.end(); ++i)
      delete *i;
    _objects.clear();
  }
  void insert_object (iterator p, object *ob) {
    _objects.insert(p._it, ob);
  }
  void replace_object (iterator p, object *ob) {
    delete *p._it;
    *p._it = ob;
  }
  void swap_objects (iterator a, iterator b) {
    object *t = *a._it;
    *a._it = *b._it;
    *b._it = t;
  }

  static file *read (int fp);
  static file *read (const char *fname);
  
  //  bool write (int fp);
  //  bool write (const char *fname, int mode=0777);
};

inline file::iterator operator+(const file::iterator &a,
                                file::difference_type d) {
  return file::iterator(a._it + d);
}
inline file::iterator operator+(file::difference_type d,
                                const file::iterator &a) {
  return file::iterator(a._it + d);
}
inline file::iterator operator-(const file::iterator &a,
                                file::difference_type d) {
  return file::iterator(a._it - d);
}
inline file::difference_type operator-(const file::iterator &a,
                                       const file::iterator &b) {
  return a._it - b._it;
}

inline file::const_iterator operator+(const file::const_iterator &a,
                                      file::difference_type d) {
  return file::const_iterator(a._it + d);
}
inline file::const_iterator operator+(file::difference_type d,
                                      const file::const_iterator &a) {
  return file::const_iterator(a._it + d);
}
inline file::const_iterator operator-(const file::const_iterator &a,
                                      file::difference_type d) {
  return file::const_iterator(a._it - d);
}
inline file::difference_type operator-(const file::const_iterator &a,
                                       const file::const_iterator &b) {
  return a._it - b._it;
}

END_MACHO_NS

#endif
