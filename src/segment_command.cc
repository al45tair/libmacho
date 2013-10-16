#include <macho/segment_command.h>
#include <iostream>

using namespace macho;

segment_command::~segment_command()
{
  if (_data) {
    _data->release();
    _data = NULL;
  }

  for (auto i = _sections.begin(); i != _sections.end(); ++i)
    delete *i;
}

static void
read_relocs (section *ns, int fp, uint32_t reloff, uint32_t nreloc)
{
  size_t reloc_len = sizeof (lowlevel::relocation_info) * nreloc;
  lowlevel::relocation_info *prelocs 
    = (lowlevel::relocation_info *)::malloc (reloc_len);

  try {
    ssize_t ret = ::pread (fp, prelocs, reloc_len, reloff);

    if (ret > 0 && (size_t)ret == reloc_len) {
      for (unsigned n = 0; n < nreloc; ++n) {
        union {
          lowlevel::relocation_info           ri;
          lowlevel::scattered_relocation_info sri;
        } u;
        relocation r;

        u.ri = bswap(prelocs[n]);

        if (u.ri.r_address & R_SCATTERED) {
          r = relocation (u.sri.r_address,
                          false,
                          0,
                          u.sri.r_length,
                          u.sri.r_type,
                          u.sri.r_pcrel,
                          true);
        } else {
          r = relocation (u.ri.r_address,
                          u.ri.r_extern,
                          u.ri.r_symbolnum,
                          u.ri.r_length,
                          u.ri.r_type,
                          u.ri.r_pcrel);
        }

        ns->add_relocation (r);
      }
    }
  } catch (...) {
    ::free (prelocs);
    throw;
  }

  ::free (prelocs);
}

load_command *
segment_command::from_file (lowlevel::load_command *pcmd,
                            int fp, off_t base, off_t end,
                            bool swap, bool &retain)
{
  lowlevel::load_command cmd = swap ? bswap(*pcmd) : *pcmd;
  segment_command *s = new segment_command();
  uint32_t left = cmd.cmdsize;
  off_t flen = end - base;

  retain = false;

  if (cmd.cmd == LC_SEGMENT) {
    if (cmd.cmdsize < sizeof (lowlevel::segment_command)) {
      delete s;
      return NULL;
    }

    lowlevel::segment_command *pseg = (lowlevel::segment_command *)pcmd;
    lowlevel::segment_command seg = swap ? bswap(*pseg) : *pseg;

    if (seg.fileoff > flen
        || seg.fileoff + seg.filesize > flen) {
      delete s;
      return NULL;
    }

    int len = ::strnlen (seg.segname, 16);
    
    s->_name = std::string(seg.segname, len);

    s->_vm_addr = seg.vmaddr;
    s->_vm_size = seg.vmsize;
    s->_max_prot = seg.maxprot;
    s->_init_prot = seg.initprot;
    s->_flags = seg.flags;
    
    left -= sizeof (lowlevel::segment_command);
    lowlevel::section *psect = (lowlevel::section *)(pseg + 1);

    while (left >= sizeof (lowlevel::section)) {
      lowlevel::section sect;

      if (swap)
        sect = bswap(*psect++);
      else
        sect = *psect++;

      int nlen = ::strnlen (sect.sectname, 16);
      int nglen = ::strnlen (sect.segname, 16);

      section *ns = new section (std::string(sect.sectname, nlen),
                                 std::string(sect.segname, nglen),
                                 sect.addr,
                                 sect.size,
                                 sect.align);
      
      s->_sections.push_back(ns);

      size_t reloc_len = sizeof (lowlevel::relocation_info) * sect.nreloc;
      if (base + sect.reloff < end 
          && (off_t)(base + sect.reloff + reloc_len) <= end)
        read_relocs (ns, fp, base + sect.reloff, sect.nreloc);

      left -= sizeof (sect);
    }

    s->_data = data::from_file (fp, base + seg.fileoff, seg.filesize);
  } else if (cmd.cmd == LC_SEGMENT_64) {
    if (cmd.cmdsize < sizeof (lowlevel::segment_command_64)) {
      delete s;
      return NULL;
    }

    lowlevel::segment_command_64 *pseg = (lowlevel::segment_command_64 *)pcmd;
    lowlevel::segment_command_64 seg = swap ? bswap(*pseg) : *pseg;

    if ((off_t)seg.fileoff > flen
        || (off_t)(seg.fileoff + seg.filesize) > flen) {
      delete s;
      return NULL;
    }

    int len = ::strnlen (seg.segname, 16);
    
    s->_name = std::string(seg.segname, len);

    s->_vm_addr = seg.vmaddr;
    s->_vm_size = seg.vmsize;
    s->_max_prot = seg.maxprot;
    s->_init_prot = seg.initprot;
    s->_flags = seg.flags;

    left -= sizeof (lowlevel::segment_command_64);
    lowlevel::section_64 *psect = (lowlevel::section_64 *)(pseg + 1);

    while (left >= sizeof (lowlevel::section_64)) {
      lowlevel::section_64 sect;
      
      if (swap)
        sect = bswap(*psect++);
      else
        sect = *psect++;

      int nlen = ::strnlen (sect.sectname, 16);
      int nglen = ::strnlen (sect.segname, 16);

      section *ns = new section (std::string(sect.sectname, nlen),
                                 std::string(sect.segname, nglen),
                                 sect.addr,
                                 sect.size,
                                 sect.align);
      
      s->_sections.push_back(ns);

      size_t reloc_len = sizeof (lowlevel::relocation_info) * sect.nreloc;
      if (base + sect.reloff < end 
          && (off_t)(base + sect.reloff + reloc_len) <= end)
        read_relocs (ns, fp, base + sect.reloff, sect.nreloc);      

      left -= sizeof (sect);
    }

    s->_data = data::from_file (fp, base + seg.fileoff, seg.filesize);
  }

  return s;
}

load_command *
segment_command::copy() const
{
  return new segment_command(*this);
}
