/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_REFCOUNTING_H_
#define LIBMACHO_REFCOUNTING_H_

#include "base.h"
#include <cstdint>

BEGIN_MACHO_NS

class refcounted
{
private:
  mutable std::uint32_t _refcount;

protected:
  virtual void dealloc() const { delete this; }

public:
  refcounted() : _refcount(1) {}
  virtual ~refcounted() {}

  void retain() const { ++_refcount; }
  void release() const { if (!--_refcount) dealloc(); }
};

END_MACHO_NS

#endif
