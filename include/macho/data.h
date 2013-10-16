/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_DATA_H_
#define LIBMACHO_DATA_H_

#include "base.h"
#include "refcounting.h"
#include <unistd.h>

BEGIN_MACHO_NS

/* Represents some data, which might be backed by memory, or zero-filled,
   or could be backed by a section of a file. */
class mutable_data;

class data : public refcounted
{
protected:
  typedef enum { bytes, zeros, file } backing;

  struct mapping {
    void  *base;
    size_t len;

    bool operator<(const mapping &other) const {
      return base < other.base;
    }
  };

  void                       *_data;
  size_t                      _size;
  backing                     _backing;
  int                         _fp;
  off_t                       _offset;

  data (backing b, const void *bytes, off_t offset, size_t len, int fp);

public:
  virtual ~data();

  static data *with_size (size_t len);
  static data *from_bytes (const void *bytes, size_t len);
  static data *from_file (int fp, off_t start, size_t len);

  size_t size() const { return _size; }

  const void *lock(off_t offset, size_t len) const;
  void unlock(const void *ptr, size_t len) const;

  virtual data         *copy() const;
  virtual mutable_data *mutable_copy() const;
};

class mutable_data : public data
{
private:
  mutable_data (const void *bytes, size_t len);

public:
  virtual ~mutable_data();

  static mutable_data *with_size (size_t len);
  static mutable_data *from_bytes (const void *bytes, size_t len);
  static mutable_data *from_file (int fp, off_t start, size_t len);

  bool resize(size_t new_len);

  void *lock(off_t offset, size_t len);
  void unlock(void *ptr, size_t len);

  virtual data         *copy() const;
  virtual mutable_data *mutable_copy() const;
};

END_MACHO_NS

#endif
