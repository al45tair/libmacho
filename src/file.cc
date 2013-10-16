#include <macho/file.h>
#include <macho/object.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdint>
#include <cstdlib>
#include <cassert>

using namespace macho;

namespace {
  object *read_object (int fp, off_t offset, off_t size=-1);
};

file::~file() 
{
  for (auto i = _objects.begin(); i < _objects.end(); ++i)
    delete *i;

  close();
}

void
file::close()
{
  if (_fp >= 0) {
    ::close (_fp);
    _fp = -1;
  }
}

file *
file::read (const char *fname)
{
  int fp = ::open (fname, O_RDONLY);
  return file::read (fp);
}

file *
file::read (int fp)
{
  file *f = new file();
  union {
    lowlevel::mach_header_64 ohdr;
    lowlevel::fat_header     fhdr;
  } u;

  f->_fp = fp;

  if (::pread (fp, &u.fhdr, sizeof (u.fhdr), 0) < (ssize_t)sizeof (u.fhdr))
    return NULL;

  if (u.fhdr.magic == FAT_MAGIC || u.fhdr.magic == FAT_CIGAM) {
    uint32_t narch;
    off_t pos = sizeof (lowlevel::fat_header);

    if (u.fhdr.magic == FAT_MAGIC)
      narch = u.fhdr.nfat_arch;
    else
      narch = bswap(u.fhdr.nfat_arch);

    for (uint32_t n = 0; n < narch; ++n) {
      lowlevel::fat_arch arch;

      if (::pread (fp, &arch, sizeof (arch), pos) < (ssize_t)sizeof (arch)) {
        delete f;
        return NULL;
      }

      if (u.fhdr.magic == FAT_CIGAM)
        arch = bswap (arch);

      object *o = ::read_object (fp, arch.offset, arch.size);

      if (o->architecture() != architecture(arch.cputype, arch.cpusubtype)) {
        delete o;
        continue;
      }

      f->add_object (o);

      pos += sizeof (arch);
    }
  } else if (u.fhdr.magic == MH_MAGIC || u.fhdr.magic == MH_CIGAM
             || u.fhdr.magic == MH_MAGIC_64 || u.fhdr.magic == MH_CIGAM_64) {
    struct stat st;
    if (::fstat (fp, &st) < 0) {
      delete f;
      return NULL;
    }

    object *o = ::read_object (fp, 0, st.st_size);
    f->add_object (o);
  } else {
    delete f;
    return NULL;
  }

  return f;
}

namespace {

object *
read_object (int fp, off_t offset, off_t length)
{
  off_t pos = offset;
  off_t end = offset + length;
  uint32_t magic;
  union {
    lowlevel::mach_header    mh;
    lowlevel::mach_header_64 mh64;
  } hdr;

  if (length < (off_t)sizeof (lowlevel::mach_header))
    return NULL;

  if (::pread (fp, &magic, sizeof (magic), offset) < (ssize_t)sizeof (magic))
    return NULL;

  if (magic == MH_MAGIC || magic == MH_CIGAM) {
    if (::pread (fp, &hdr.mh, sizeof (hdr.mh), offset) < (ssize_t)sizeof (hdr.mh))
      return NULL;

    if (magic == MH_CIGAM)
      hdr.mh = bswap (hdr.mh);

    pos += sizeof (hdr.mh);
  } else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64) {
    if (length < (off_t)sizeof (lowlevel::mach_header_64))
      return NULL;

    if (::pread (fp, &hdr.mh64, sizeof (hdr.mh64), offset) 
        < (ssize_t)sizeof (hdr.mh64))
      return NULL;

    if (magic == MH_CIGAM_64)
      hdr.mh64 = bswap (hdr.mh64);

    pos += sizeof (hdr.mh64);
  }

  // Note: 64-bit mach_header has the same initial layout as 32-bit

  off_t cmdend = pos + hdr.mh.sizeofcmds;

  if (cmdend > end)
    return NULL;

  object *o = new object (architecture (hdr.mh.cputype, hdr.mh.cpusubtype),
                          hdr.mh.filetype,
                          hdr.mh.flags);

  for (uint32_t n = 0; n < hdr.mh.ncmds; ++n) {
    lowlevel::load_command lcmd;

    if (pos + (off_t)sizeof (lcmd) > cmdend)
      goto errexit;

    if (::pread (fp, &lcmd, sizeof (lcmd), pos) < (ssize_t)sizeof (lcmd))
      goto errexit;

    if (magic == MH_CIGAM || magic == MH_CIGAM_64)
      lcmd = bswap (lcmd);

    if (pos + lcmd.cmdsize > cmdend || lcmd.cmdsize < sizeof (lcmd))
      goto errexit;

    lowlevel::load_command *data 
      = (lowlevel::load_command *)::malloc (lcmd.cmdsize);

    if (::pread (fp, data, lcmd.cmdsize, pos) < (ssize_t)lcmd.cmdsize) {
      ::free (data);
      goto errexit;
    }

    bool retain = false;
    load_command *lc = load_command::from_file (data, fp, offset, end,
                                                magic == MH_CIGAM
                                                || magic == MH_CIGAM_64,
                                                retain);

    assert (lc);

    o->add_load_command (lc);

    if (!retain)
      ::free (data);

    pos += lcmd.cmdsize;
  }

  return o;

 errexit:
  delete o;
  return NULL;
}

}

