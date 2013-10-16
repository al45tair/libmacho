#include <macho/data.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <set>

using namespace macho;

data::data (data::backing b, const void *bytes, off_t offset, size_t len, int fp)
  : _size(len), _backing(b), _fp(fp), _offset(offset)
{
  switch (_backing) {
  case data::bytes:
    _data = (void *)bytes;
    break;
  case data::zeros:
    _fp = ::open ("/dev/zero", O_RDONLY);
  case data::file:
    _data = new std::set<data::mapping>;
  }
}

data::~data ()
{
  switch (_backing) {
  case data::bytes:
    ::free (_data);
    break;
  case data::zeros:
    ::close (_fp);
  case data::file:
    std::set<data::mapping> *mappings = (std::set<data::mapping> *)_data;

    for (auto i = mappings->begin(); i != mappings->end(); ++i)
      ::munmap (i->base, i->len);

    delete mappings;
  }
}

data *
data::with_size (size_t len)
{
  return new data(data::zeros, NULL, 0, len, -1);
}

data *
data::from_bytes (const void *bytes, size_t len)
{
  return new data(data::bytes, bytes, 0, len, -1);
}

data *
data::from_file (int fp, off_t start, size_t len)
{
  return new data(data::file, NULL, start, len, fp);
}

const void *
data::lock(off_t offset, size_t len) const
{
  if (_backing == data::bytes) {
    if ((size_t)offset > _size || _size - offset < len)
      return NULL;
    return ((uint8_t *)_data) + offset;
  }

  off_t foffset = offset + _offset;
  int pagesize = getpagesize();
  int extra = foffset & (pagesize - 1);
  
  if (extra) {
    foffset -= extra;
    len += extra;
  }

  len = (len + (pagesize - 1)) & ~(size_t)(pagesize - 1);
  
  void *base = ::mmap (NULL, len, PROT_READ, MAP_FILE, _fp, foffset);
  
  if (!base)
    return NULL;
  
  struct mapping m = { base, len };
  
  std::set<data::mapping> *mappings = (std::set<data::mapping> *)_data;
  mappings->insert (m);
  
  return ((uint8_t *)base) + extra;
}

void
data::unlock (const void *ptr, size_t len) const
{
  if (_backing == data::bytes)
    return;

  std::uintptr_t up = (std::uintptr_t)ptr;
  int pagesize = getpagesize();
  int extra = up & (pagesize - 1);

  if (extra) {
    up -= extra;
    len += extra;
  }

  len = (len + (pagesize - 1)) & ~(size_t)(pagesize - 1);

  struct mapping m = { (void *)up, len };

  std::set<data::mapping> *mappings = (std::set<data::mapping> *)_data;
  mappings->erase (m);

  munmap (m.base, m.len);
}

data *
data::copy() const
{
  retain();
  return (data *)this;
}

mutable_data *
data::mutable_copy() const
{
  const void *bytes = lock (0, _size);
  mutable_data *md = NULL;

  try {
    md = mutable_data::from_bytes(bytes, _size);
  } catch (...) {
    unlock (bytes, _size);
    throw;
  }

  unlock (bytes, _size);

  return md;
}

mutable_data::mutable_data (const void *bytes, size_t len)
  : data(data::bytes, bytes, 0, len, -1)
{
}

mutable_data::~mutable_data()
{
}

mutable_data *
mutable_data::with_size (size_t len)
{
  return new mutable_data (NULL, len);
}

mutable_data *
mutable_data::from_bytes (const void *bytes, size_t len)
{
  return new mutable_data (bytes, len);
}

mutable_data *
mutable_data::from_file (int fp, off_t start, size_t len)
{
  mutable_data *d = new mutable_data (NULL, len);
  int ret = ::pread (fp, d->_data, len, start);
  
  if (ret < 0) {
    d->release();
    return NULL;
  }

  return d;
}

bool
mutable_data::resize (size_t new_len)
{
  void *new_data = ::realloc (_data, new_len);

  if (!new_data)
    return false;

  _data = new_data;

  return true;
}

void *
mutable_data::lock (off_t offset, size_t len)
{
  if (offset < 0 || (size_t)offset > _size
      || len > _size || offset + len > _size)
    return NULL;

  return (uint8_t *)_data + offset;
}

void
mutable_data::unlock (void *ptr, size_t len)
{
  (void)ptr;
  (void)len;
}

data *
mutable_data::copy() const
{
  return data::from_bytes (_data, _size);
}

mutable_data *
mutable_data::mutable_copy() const
{
  return mutable_data::from_bytes (_data, _size);
}
