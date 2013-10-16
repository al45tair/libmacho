/* Emacs, this is -*-C++-*- */
#ifndef LIBMACHO_TYPES_H_
#define LIBMACHO_TYPES_H_

#include "base.h"
#include <cstdint>
#include <cstring>

BEGIN_MACHO_NS

using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::uint16_t;
using std::uint32_t;
using std::uint32_t;
using std::uint64_t;

#pragma pack(push, 1)

// -- Byte swapping ------------------------------------------------------------

// bswap() should be overloaded for any structures that are declared

inline uint16_t bswap(uint16_t u) 
{
  return ((u >> 8) & 0xff) | (u << 8);
}
inline int16_t bswap(int16_t i)
{
  return int16_t(bswap(uint16_t(i)));
}

inline uint32_t bswap(uint32_t u)
{
  u = ((u >> 8) & 0x00ff00ff) | ((u & 0x00ff00ff) << 8);
  return ((u >> 16) & 0x0000ffff) | (u << 16);
}
inline int32_t bswap(int32_t i)
{
  return int32_t(bswap(uint32_t(i)));
}

inline uint64_t bswap(uint64_t u)
{
  u = ((u >> 8) & 0x00ff00ff00ff00ff) | ((u & 0x00ff00ff00ff00ff) << 8);
  u = ((u >> 16) & 0x0000ffff0000ffff) | ((u & 0x0000ffff0000ffff) << 16);
  return ((u >> 32) & 0x00000000ffffffff) | (u << 32);
}
inline int64_t bswap(int64_t i)
{
  return int64_t(bswap(uint64_t(i)));
}

// -----------------------------------------------------------------------------

/* The types below match those declared in /usr/include/mach on Mac OS X;
   they are, however, in a namespace, and all of the symbols are enums
   rather than #defines, so they have namespace scope.

   Note: we do not include constants labelled "compat"!

   This file was based on the iOS 7 ARM files, being as they are the most
   complete. */

// -- CPU types/subtypes -------------------------------------------------------

typedef int32_t  cpu_type;
typedef int32_t  cpu_subtype;

const cpu_type CPU_ARCH_MASK  = 0xff000000;
const cpu_type CPU_ARCH_ABI64 = 0x01000000;

// CPU types
const cpu_type CPU_TYPE_ANY = -1;
const cpu_type CPU_TYPE_VAX = 1;
const cpu_type CPU_TYPE_MC680x0 = 6;
const cpu_type CPU_TYPE_X86 = 7;
const cpu_type CPU_TYPE_I386 = CPU_TYPE_X86;
const cpu_type CPU_TYPE_X86_64 = CPU_TYPE_X86 | CPU_ARCH_ABI64;
const cpu_type CPU_TYPE_MIPS = 8;
const cpu_type CPU_TYPE_MC98000 = 10;
const cpu_type CPU_TYPE_HPPA = 11;
const cpu_type CPU_TYPE_ARM = 12;
const cpu_type CPU_TYPE_ARM64 = CPU_TYPE_ARM | CPU_ARCH_ABI64;
const cpu_type CPU_TYPE_MC88000 = 13;
const cpu_type CPU_TYPE_SPARC = 14;
const cpu_type CPU_TYPE_I860 = 15;
const cpu_type CPU_TYPE_ALPHA = 16;
const cpu_type CPU_TYPE_POWERPC = 18;
const cpu_type CPU_TYPE_POWERPC64 = CPU_TYPE_POWERPC | CPU_ARCH_ABI64;

// CPU subtypes
const cpu_subtype CPU_SUBTYPE_MASK  = 0xff000000;
const cpu_subtype CPU_SUBTYPE_LIB64 = 0x80000000;

const cpu_subtype CPU_SUBTYPE_MULTIPLE      = -1;
const cpu_subtype CPU_SUBTYPE_LITTLE_ENDIAN = 0;
const cpu_subtype CPU_SUBTYPE_BIG_ENDIAN    = 1;

// VAX
const cpu_subtype CPU_SUBTYPE_VAX_ALL = 0;
const cpu_subtype CPU_SUBTYPE_VAX780  = 1;
const cpu_subtype CPU_SUBTYPE_VAX785  = 2;
const cpu_subtype CPU_SUBTYPE_VAX750  = 3;
const cpu_subtype CPU_SUBTYPE_VAX730  = 4;
const cpu_subtype CPU_SUBTYPE_UVAXI   = 5;
const cpu_subtype CPU_SUBTYPE_UVAXII  = 6;
const cpu_subtype CPU_SUBTYPE_VAX8200 = 7;
const cpu_subtype CPU_SUBTYPE_VAX8500 = 8;
const cpu_subtype CPU_SUBTYPE_VAX8600 = 9;
const cpu_subtype CPU_SUBTYPE_VAX8650 = 10;
const cpu_subtype CPU_SUBTYPE_VAX8800 = 11;
const cpu_subtype CPU_SUBTYPE_UVAXIII = 12;

// 680x0
const cpu_subtype CPU_SUBTYPE_MC680x0_ALL = 1;
const cpu_subtype CPU_SUBTYPE_MC68040     = 2;
const cpu_subtype CPU_SUBTYPE_MC68030     = 3;

// Intel
const cpu_subtype CPU_SUBTYPE_I386_ALL       = 0x03;
const cpu_subtype CPU_SUBTYPE_386            = 0x03;
const cpu_subtype CPU_SUBTYPE_486            = 0x04;
const cpu_subtype CPU_SUBTYPE_486SX          = 0x84;
const cpu_subtype CPU_SUBTYPE_586            = 0x05;
const cpu_subtype CPU_SUBTYPE_PENT           = 0x05;
const cpu_subtype CPU_SUBTYPE_PENTPRO        = 0x16;
const cpu_subtype CPU_SUBTYPE_PENTII_M3      = 0x36;
const cpu_subtype CPU_SUBTYPE_PENTII_M5      = 0x56;
const cpu_subtype CPU_SUBTYPE_CELERON        = 0x67;
const cpu_subtype CPU_SUBTYPE_CELERON_MOBILE = 0x77;
const cpu_subtype CPU_SUBTYPE_PENTIUM_3      = 0x08;
const cpu_subtype CPU_SUBTYPE_PENTIUM_3_M    = 0x18;
const cpu_subtype CPU_SUBTYPE_PENTIUM_3_XEON = 0x28;
const cpu_subtype CPU_SUBTYPE_PENTIUM_M      = 0x09;
const cpu_subtype CPU_SUBTYPE_PENTIUM_4      = 0x0a;
const cpu_subtype CPU_SUBTYPE_PENTIUM_4_M    = 0x1a;
const cpu_subtype CPU_SUBTYPE_ITANIUM        = 0x0b;
const cpu_subtype CPU_SUBTYPE_ITANIUM_2      = 0x1b;
const cpu_subtype CPU_SUBTYPE_XEON           = 0x0c;
const cpu_subtype CPU_SUBTYPE_XEON_MP        = 0x1c;

// x86
const cpu_subtype CPU_SUBTYPE_X86_ALL    = 3;
const cpu_subtype CPU_SUBTYPE_X86_64_ALL = 3;
const cpu_subtype CPU_SUBTYPE_X86_ARCH1  = 4;

// Mips
const cpu_subtype CPU_SUBTYPE_MIPS_ALL    = 0;
const cpu_subtype CPU_SUBTYPE_MIPS_R2300  = 1;
const cpu_subtype CPU_SUBTYPE_MIPS_R2600  = 2;
const cpu_subtype CPU_SUBTYPE_MIPS_R2800  = 3;
const cpu_subtype CPU_SUBTYPE_MIPS_R2000a = 4;
const cpu_subtype CPU_SUBTYPE_MIPS_R2000  = 5;
const cpu_subtype CPU_SUBTYPE_MIPS_R3000a = 6;
const cpu_subtype CPU_SUBTYPE_MIPS_R3000  = 7;

// MC98K
const cpu_subtype CPU_SUBTYPE_MC98000_ALL = 0;
const cpu_subtype CPU_SUBTYPE_MC98601 = 1;

// HPPA
const cpu_subtype CPU_SUBTYPE_HPPA_ALL = 0;
const cpu_subtype CPU_SUBTYPE_HPPA_7100LC = 1;

// MC88K
const cpu_subtype CPU_SUBTYPE_MC88000_ALL = 0;
const cpu_subtype CPU_SUBTYPE_MC88100 = 1;
const cpu_subtype CPU_SUBTYPE_MC88110 = 2;

// SPARC
const cpu_subtype CPU_SUBTYPE_SPARC_ALL = 0;

// i860
const cpu_subtype CPU_SUBTYPE_I860_ALL = 0;
const cpu_subtype CPU_SUBTYPE_I860_860 = 1;

// PowerPC
const cpu_subtype CPU_SUBTYPE_POWERPC_ALL   = 0;
const cpu_subtype CPU_SUBTYPE_POWERPC_601   = 1;
const cpu_subtype CPU_SUBTYPE_POWERPC_602   = 2;
const cpu_subtype CPU_SUBTYPE_POWERPC_603   = 3;
const cpu_subtype CPU_SUBTYPE_POWERPC_603e  = 4;
const cpu_subtype CPU_SUBTYPE_POWERPC_603ev = 5;
const cpu_subtype CPU_SUBTYPE_POWERPC_604   = 6;
const cpu_subtype CPU_SUBTYPE_POWERPC_604e  = 7;
const cpu_subtype CPU_SUBTYPE_POWERPC_620   = 8;
const cpu_subtype CPU_SUBTYPE_POWERPC_750   = 9;
const cpu_subtype CPU_SUBTYPE_POWERPC_7400  = 10;
const cpu_subtype CPU_SUBTYPE_POWERPC_7450  = 11;
const cpu_subtype CPU_SUBTYPE_POWERPC_970   = 100;

// ARM
const cpu_subtype CPU_SUBTYPE_ARM_ALL    = 0;
const cpu_subtype CPU_SUBTYPE_ARM_V4T    = 5;
const cpu_subtype CPU_SUBTYPE_ARM_V6     = 6;
const cpu_subtype CPU_SUBTYPE_ARM_V5TEJ  = 7;
const cpu_subtype CPU_SUBTYPE_ARM_XSCALE = 8;
const cpu_subtype CPU_SUBTYPE_ARM_V7     = 9;
const cpu_subtype CPU_SUBTYPE_ARM_V7F    = 10;
const cpu_subtype CPU_SUBTYPE_ARM_V7S    = 11;
const cpu_subtype CPU_SUBTYPE_ARM_V7K    = 12;
const cpu_subtype CPU_SUBTYPE_ARM_V6M    = 14;
const cpu_subtype CPU_SUBTYPE_ARM_V7M    = 15;
const cpu_subtype CPU_SUBTYPE_ARM_V7EM   = 16;
const cpu_subtype CPU_SUBTYPE_ARM_V8     = 13;

// ARM64
const cpu_subtype CPU_SUBTYPE_ARM64_ALL = 0;
const cpu_subtype CPU_SUBTYPE_ARM64_V8  = 1;

// -- VM protection ------------------------------------------------------------

typedef uint32_t vm_prot;

const vm_prot VM_PROT_READ    = 0x01;
const vm_prot VM_PROT_WRITE   = 0x02;
const vm_prot VM_PROT_EXECUTE = 0x04;

const vm_prot VM_PROT_NONE    = 0x00;
const vm_prot VM_PROT_DEFAULT = VM_PROT_READ | VM_PROT_WRITE;
const vm_prot VM_PROT_ALL     = VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXECUTE;

const vm_prot VM_PROT_COPY    = 0x10;

// -- Mach-O header ------------------------------------------------------------

namespace lowlevel {

struct fat_header {
  uint32_t magic;
  uint32_t nfat_arch;
};

struct fat_arch {
  cpu_type    cputype;
  cpu_subtype cpusubtype;
  uint32_t    offset;
  uint32_t    size;
  uint32_t    align;
};

struct mach_header {
  uint32_t    magic;
  cpu_type    cputype;
  cpu_subtype cpusubtype;
  uint32_t    filetype;
  uint32_t    ncmds;
  uint32_t    sizeofcmds;
  uint32_t    flags;
};

struct mach_header_64 {
  uint32_t    magic;
  cpu_type    cputype;
  cpu_subtype cpusubtype;
  uint32_t    filetype;
  uint32_t    ncmds;
  uint32_t    sizeofcmds;
  uint32_t    flags;
  uint32_t    reserved;
};

}

inline lowlevel::fat_header bswap(const lowlevel::fat_header &h) {
  lowlevel::fat_header r = { bswap(h.magic), bswap(h.nfat_arch) };
  return r;
}

inline lowlevel::fat_arch bswap(const lowlevel::fat_arch &a) {
  lowlevel::fat_arch r = { bswap(a.cputype), bswap(a.cpusubtype),
                           bswap(a.offset),
                           bswap(a.size), bswap(a.align) };
  return r;
}

inline lowlevel::mach_header bswap(const lowlevel::mach_header &m) {
  lowlevel::mach_header r = { bswap(m.magic),
                              bswap(m.cputype),
                              bswap(m.cpusubtype),
                              bswap(m.filetype),
                              bswap(m.ncmds),
                              bswap(m.sizeofcmds),
                              bswap(m.flags) };
  return r;
}

inline lowlevel::mach_header_64 bswap(const lowlevel::mach_header_64 &m) {
  lowlevel::mach_header_64 r = { bswap(m.magic),
                                 bswap(m.cputype),
                                 bswap(m.cpusubtype),
                                 bswap(m.filetype),
                                 bswap(m.ncmds),
                                 bswap(m.sizeofcmds),
                                 bswap(m.flags),
                                 bswap(m.reserved) };
  return r;
}

// magic
const uint32_t MH_MAGIC    = 0xfeedface;
const uint32_t MH_CIGAM    = 0xcefaedfe;
const uint32_t MH_MAGIC_64 = 0xfeedfacf;
const uint32_t MH_CIGAM_64 = 0xcffaedfe;
const uint32_t FAT_MAGIC   = 0xcafebabe;
const uint32_t FAT_CIGAM   = 0xbebafeca;

// filetype
const uint32_t MH_OBJECT      = 0x1;
const uint32_t MH_EXECUTE     = 0x2;
const uint32_t MH_FVMLIB      = 0x3;
const uint32_t MH_CORE        = 0x4;
const uint32_t MH_PRELOAD     = 0x5;
const uint32_t MH_DYLIB       = 0x6;
const uint32_t MH_DYLINKER    = 0x7;
const uint32_t MH_BUNDLE      = 0x8;
const uint32_t MH_DYLIB_STUB  = 0x9;
const uint32_t MH_DSYM        = 0xa;
const uint32_t MH_KEXT_BUNDLE = 0xb;

// flags
const uint32_t MH_NOUNDEFS                = 0x00000001;
const uint32_t MH_INCRLINK                = 0x00000002;
const uint32_t MH_DYLDLINK                = 0x00000004;
const uint32_t MH_BINDATLOAD              = 0x00000008;
const uint32_t MH_PREBOUND                = 0x00000010;
const uint32_t MH_SPLIT_SEGS              = 0x00000020;
const uint32_t MH_LAZY_INIT               = 0x00000040;
const uint32_t MH_TWOLEVEL                = 0x00000080;
const uint32_t MH_FORCE_FLAT              = 0x00000100;
const uint32_t MH_NOMULTIDEFS             = 0x00000200;
const uint32_t MH_NOFIXPREBINDING         = 0x00000400;
const uint32_t MH_PREBINDABLE             = 0x00000800;
const uint32_t MH_ALLMODSBOUND            = 0x00001000;
const uint32_t MH_SUBSECTIONS_VIA_SYMBOLS = 0x00002000;
const uint32_t MH_CANONICAL               = 0x00004000;
const uint32_t MH_WEAK_DEFINES            = 0x00008000;
const uint32_t MH_BINDS_TO_WEAK           = 0x00010000;
const uint32_t MH_ALLOW_STACK_EXECUTION   = 0x00020000;
const uint32_t MH_ROOT_SAFE               = 0x00040000;   
const uint32_t MH_SETUID_SAFE             = 0x00080000;
const uint32_t MH_NO_REEXPORTED_DYLIBS    = 0x00100000;
const uint32_t MH_PIE                     = 0x00200000;
const uint32_t MH_DEAD_STRIPPABLE_DYLIB   = 0x00400000;
const uint32_t MH_HAS_TLV_DESCRIPTORS     = 0x00800000;
const uint32_t MH_NO_HEAP_EXECUTION       = 0x01000000;

// -- Load commands ------------------------------------------------------------

namespace lowlevel {

struct load_command {
  uint32_t cmd;
  uint32_t cmdsize;
};

}

inline lowlevel::load_command bswap (const lowlevel::load_command &lc)
{
  lowlevel::load_command r = { bswap (lc.cmd), bswap (lc.cmdsize) };
  return r;
}

const uint32_t LC_REQ_DYLD = 0x80000000;

//                                                                 supported

const uint32_t LC_SEGMENT              = 1;                     // X
const uint32_t LC_SYMTAB               = 2;
const uint32_t LC_SYMSEG               = 3;
const uint32_t LC_THREAD               = 4;
const uint32_t LC_UNIXTHREAD           = 5;
const uint32_t LC_LOADFVMLIB           = 6;
const uint32_t LC_IDFVMLIB             = 7;
const uint32_t LC_IDENT                = 8;
const uint32_t LC_FVMFILE              = 9;
const uint32_t LC_PREPAGE              = 10;
const uint32_t LC_DYSYMTAB             = 11;
const uint32_t LC_LOAD_DYLIB           = 12;                    // X
const uint32_t LC_ID_DYLIB             = 13;                    // X
const uint32_t LC_LOAD_DYLINKER        = 14;                    // X
const uint32_t LC_ID_DYLINKER          = 15;
const uint32_t LC_PREBOUND_DYLIB       = 16;
const uint32_t LC_ROUTINES             = 17;
const uint32_t LC_SUB_FRAMEWORK        = 18;                    // X
const uint32_t LC_SUB_UMBRELLA         = 19;                    // X
const uint32_t LC_SUB_CLIENT           = 20;                    // X
const uint32_t LC_SUB_LIBRARY          = 21;                    // X
const uint32_t LC_TWOLEVEL_HINTS       = 22;
const uint32_t LC_PREBIND_CKSUM        = 23;
const uint32_t LC_LOAD_WEAK_DYLIB      = 24 | LC_REQ_DYLD;      // X
const uint32_t LC_SEGMENT_64           = 25;                    // X
const uint32_t LC_ROUTINES_64          = 26;
const uint32_t LC_UUID                 = 27;                    // X
const uint32_t LC_RPATH                = 28 | LC_REQ_DYLD;      // X
const uint32_t LC_CODE_SIGNATURE       = 29;
const uint32_t LC_SEGMENT_SPLIT_INFO   = 30;
const uint32_t LC_REEXPORT_DYLIB       = 31 | LC_REQ_DYLD;      // X
const uint32_t LC_LAZY_LOAD_DYLIB      = 32;                    // X
const uint32_t LC_ENCRYPTION_INFO      = 33;
const uint32_t LC_DYLD_INFO            = 34;
const uint32_t LC_DYLD_INFO_ONLY       = 34 | LC_REQ_DYLD;
const uint32_t LC_LOAD_UPWARD_DYLIB    = 35 | LC_REQ_DYLD;      // X
const uint32_t LC_VERSION_MIN_MACOSX   = 36;                    // X
const uint32_t LC_VERSION_MIN_IPHONEOS = 37;                    // X
const uint32_t LC_FUNCTION_STARTS      = 38;
const uint32_t LC_DYLD_ENVIRONMENT     = 39;                    // X
const uint32_t LC_MAIN                 = 40 | LC_REQ_DYLD;
const uint32_t LC_DATA_IN_CODE         = 41;
const uint32_t LC_SOURCE_VERSION       = 42;                    // X
const uint32_t LC_DYLIB_CODE_SIGN_DRS  = 43;
const uint32_t LC_ENCRYPTION_INFO_64   = 44;
const uint32_t LC_LINKER_OPTION        = 45;

// A string
typedef uint32_t lc_str;

// .. LC_SEGMENT[64] ...........................................................

namespace lowlevel {

struct segment_command {
  uint32_t cmd;
  uint32_t cmdsize;
  char     segname[16];
  uint32_t vmaddr;
  uint32_t vmsize;
  uint32_t fileoff;
  uint32_t filesize;
  vm_prot  maxprot;
  vm_prot  initprot;
  uint32_t nsects;
  uint32_t flags;
};

struct segment_command_64 {
  uint32_t cmd;
  uint32_t cmdsize;
  char     segname[16];
  uint64_t vmaddr;
  uint64_t vmsize;
  uint64_t fileoff;
  uint64_t filesize;
  vm_prot  maxprot;
  vm_prot  initprot;
  uint32_t nsects;
  uint32_t flags;
};

}

inline lowlevel::segment_command bswap(const lowlevel::segment_command &s) {
  lowlevel::segment_command r;

  r.cmd = bswap (s.cmd);
  r.cmdsize = bswap (s.cmdsize);
  std::memcpy (r.segname, s.segname, sizeof (s.segname));
  r.vmaddr = bswap (s.vmaddr);
  r.vmsize = bswap (s.vmsize);
  r.fileoff = bswap (s.fileoff);
  r.filesize = bswap (s.filesize);
  r.maxprot = bswap (s.maxprot);
  r.initprot = bswap (s.initprot);
  r.nsects = bswap (s.nsects);
  r.flags = bswap (s.flags);

  return r;
}

inline lowlevel::segment_command_64 bswap(const lowlevel::segment_command_64 &s) {
  lowlevel::segment_command_64 r;

  r.cmd = bswap (s.cmd);
  r.cmdsize = bswap (s.cmdsize);
  std::memcpy (r.segname, s.segname, sizeof (s.segname));
  r.vmaddr = bswap (s.vmaddr);
  r.vmsize = bswap (s.vmsize);
  r.fileoff = bswap (s.fileoff);
  r.filesize = bswap (s.filesize);
  r.maxprot = bswap (s.maxprot);
  r.initprot = bswap (s.initprot);
  r.nsects = bswap (s.nsects);
  r.flags = bswap (s.flags);

  return r;
}

// flags
const uint32_t SG_HIGHVM = 0x1;
const uint32_t SG_FVMLIB = 0x2;
const uint32_t SG_NORELOC = 0x4;
const uint32_t SG_PROTECTED_VERSION_1 = 0x8;

namespace lowlevel {

// relocations
struct relocation_info {
  int32_t  r_address;
  uint32_t r_symbolnum:24;
  uint32_t r_pcrel:1;
  uint32_t r_length:2;
  uint32_t r_extern:1;
  uint32_t r_type:4;
};

struct scattered_relocation_info {
#if __BIG_ENDIAN__
  uint32_t r_scattered:1;
  uint32_t r_pcrel:1;
  uint32_t r_length:2;
  uint32_t r_type:4;
  uint32_t r_address:24;
#elif __LITTLE_ENDIAN__
  uint32_t r_address:24;
  uint32_t r_type:4;
  uint32_t r_length:2;
  uint32_t r_pcrel:1;
  uint32_t r_scattered:1;
#endif
  int32_t  r_value;
};

}

inline lowlevel::relocation_info bswap(const lowlevel::relocation_info &i)
{
  lowlevel::relocation_info r;
  uint32_t *pr = (uint32_t *)&r;
  const uint32_t *pi = (const uint32_t *)&i;

  *pr++ = bswap(*pi++);
  *pr = bswap(*pi);

  return r;
}

inline lowlevel::scattered_relocation_info 
bswap(const lowlevel::scattered_relocation_info &i)
{
  lowlevel::scattered_relocation_info r;
  uint32_t *pr = (uint32_t *)&r;
  const uint32_t *pi = (const uint32_t *)&i;

  *pr++ = bswap(*pi++);
  *pr = bswap(*pi);

  return r;
}

// Types are processor-specific
const uint32_t R_ABS = 0;

/* If this bit is set in the address field, it might be a
   scattered_relocation_info... */
const int32_t R_SCATTERED = (int32_t)0x80000000;


const uint32_t GENERIC_RELOC_VANILLA = 0;
const uint32_t GENERIC_RELOC_PAIR = 1;
const uint32_t GENERIC_RELOC_SECTDIFF = 2;
const uint32_t GENERIC_RELOC_PB_LA_PTR = 3;
const uint32_t GENERIC_RELOC_LOCAL_SECTDIFF = 4;
const uint32_t GENERIC_RELOC_TLV = 5;

namespace lowlevel {

// sections
struct section {
  char     sectname[16];
  char     segname[16];
  uint32_t addr;
  uint32_t size;
  uint32_t offset;
  uint32_t align;
  uint32_t reloff;
  uint32_t nreloc;
  uint32_t flags;
  uint32_t reserved1;
  uint32_t reserved2;
};

struct section_64 {
  char sectname[16];
  char segname[16];
  uint64_t addr;
  uint64_t size;
  uint32_t offset;
  uint32_t align;
  uint32_t reloff;
  uint32_t nreloc;
  uint32_t flags;
  uint32_t reserved1;
  uint32_t reserved2;
  uint32_t reserved3;
};

}

inline lowlevel::section bswap(const lowlevel::section &s) {
  lowlevel::section r;

  std::memcpy (r.sectname, s.sectname, sizeof (s.sectname));
  std::memcpy (r.segname, s.segname, sizeof (s.segname));
  r.addr = bswap(s.addr);
  r.size = bswap(s.size);
  r.offset = bswap(s.offset);
  r.align = bswap(s.align);
  r.reloff = bswap(s.reloff);
  r.nreloc = bswap(s.nreloc);
  r.flags = bswap(s.flags);
  r.reserved1 = bswap(s.reserved1);
  r.reserved2 = bswap(s.reserved2);

  return r;
}

inline lowlevel::section_64 bswap(const lowlevel::section_64 &s) {
  lowlevel::section_64 r;

  std::memcpy (r.sectname, s.sectname, sizeof (s.sectname));
  std::memcpy (r.segname, s.segname, sizeof (s.segname));
  r.addr = bswap(s.addr);
  r.size = bswap(s.size);
  r.offset = bswap(s.offset);
  r.align = bswap(s.align);
  r.reloff = bswap(s.reloff);
  r.nreloc = bswap(s.nreloc);
  r.flags = bswap(s.flags);
  r.reserved1 = bswap(s.reserved1);
  r.reserved2 = bswap(s.reserved2);
  r.reserved3 = bswap(s.reserved3);

  return r;
}

// section flags
const uint32_t SECTION_TYPE           = 0x000000ff;
const uint32_t SECTION_ATTRIBUTES     = 0xffffff00;
const uint32_t SECTION_ATTRIBUTES_USR = 0xff000000;
const uint32_t SECTION_ATTRIBUTES_SYS = 0x00ffff00;

const uint32_t S_REGULAR                             = 0x00;
const uint32_t S_ZEROFILL                            = 0x01;
const uint32_t S_CSTRING_LITERATLS                   = 0x02;
const uint32_t S_4BYTE_LITERALS                      = 0x03;
const uint32_t S_8BYTE_LITERALS                      = 0x04;
const uint32_t S_LITERAL_POINTERS                    = 0x05;
const uint32_t S_NON_LAZY_SYMBOL_POINTERS            = 0x06;
const uint32_t S_LAZY_SYMBOL_POINTERS                = 0x07;
const uint32_t S_SYMBOL_STUBS                        = 0x08;
const uint32_t S_MOD_INIT_FUNC_POINTERS              = 0x09;
const uint32_t S_MOD_TERM_FUNC_POINTERS              = 0x0a;
const uint32_t S_COALESCED                           = 0x0b;
const uint32_t S_GB_ZEROFILL                         = 0x0c;
const uint32_t S_INTERPOSING                         = 0x0d;
const uint32_t S_16BYTE_LITERALS                     = 0x0e;
const uint32_t S_DTRACE_DOF                          = 0x0f;
const uint32_t S_LAZY_DYLIB_SYMBOL_POINTERS          = 0x10;
const uint32_t S_THREAD_LOCAL_REGULAR                = 0x11;
const uint32_t S_THREAD_LOCAL_ZEROFILL               = 0x12;
const uint32_t S_THREAD_LOCAL_VARIABLES              = 0x13;
const uint32_t S_THREAD_LOCAL_VARIABLE_POINTERS      = 0x14;
const uint32_t S_THREAD_LOCAL_INIT_FUNCTION_POINTERS = 0x15;

const uint32_t S_ATTR_PURE_INSTRUCTIONS   = 0x80000000;
const uint32_t S_ATTR_NO_TOC              = 0x40000000;
const uint32_t S_ATTR_STRIP_STATIC_SYMS   = 0x20000000;
const uint32_t S_ATTR_NO_DEAD_STRIP       = 0x10000000;
const uint32_t S_ATTR_LIVE_SUPPORT        = 0x08000000;
const uint32_t S_ATTR_SELF_MODIFYING_CODE = 0x04000000;
const uint32_t S_ATTR_DEBUG               = 0x02000000;

const uint32_t S_ATTR_SOME_INSTRUCTIONS   = 0x00000400;
const uint32_t S_ATTR_EXT_RELOC           = 0x00000200;
const uint32_t S_ATTR_LOC_RELOC           = 0x00000100;

extern const char *SEG_PAGEZERO;
extern const char *SEG_TEXT;
extern const char *SECT_TEXT;
extern const char *SECT_FVMLIB_INIT0;
extern const char *SECT_FVMLIB_INIT1;

extern const char *SEG_DATA;
extern const char *SECT_DATA;
extern const char *SECT_BSS;
extern const char *SECT_COMMON;

extern const char *SEG_OBJC;
extern const char *SECT_OBJC_SYMBOLS;
extern const char *SECT_OBJC_MODULES;
extern const char *SECT_OBJC_STRINGS;
extern const char *SECT_OBJC_REFS;

extern const char *SEG_ICON;
extern const char *SECT_ICON_HEADER;
extern const char *SECT_ICON_TIFF;

extern const char *SEG_LINKEDIT;

extern const char *SEG_UNIXSTACK;

extern const char *SEG_IMPORT;

namespace lowlevel {

// S_THREAD_LOCAL_VARIABLES sections contain an array of these:
struct tlv_descriptor
{
  uint32_t thunk; // void *(*thunk)(tlv_descriptor *)
  uint32_t key;
  uint32_t offset;
};

struct tlv_descriptor_64
{
  uint64_t thunk; // void *(*thunk)(tlv_descriptor *)
  uint32_t key;
  uint32_t offset;
};

}

// .. LC_(ID|LOAD)FVMLIB .......................................................

namespace lowlevel {

struct fvmlib {
  lc_str   name;
  uint32_t minor_version;
  uint32_t header_addr;
};

struct fvmlib_command {
  uint32_t cmd;
  uint32_t cmdsize;
  fvmlib   fvmlib;
};

}

// .. LC_(ID|LOAD[_WEAK]|REEXPORT)_DYLIB .......................................

namespace lowlevel {

struct dylib {
  lc_str   name;
  uint32_t timestamp;
  uint32_t current_version;
  uint32_t compatibility_version;
};

struct dylib_command {
  uint32_t cmd;
  uint32_t cmdsize;
  dylib    dylib;
};

}

inline lowlevel::dylib bswap(const lowlevel::dylib &d) {
  lowlevel::dylib r = { bswap(d.name), 
                        bswap(d.timestamp),
                        bswap(d.current_version),
                        bswap(d.compatibility_version) };
  return r;
}

inline lowlevel::dylib_command bswap(const lowlevel::dylib_command &d) {
  lowlevel::dylib_command r = { bswap(d.cmd),
                                bswap(d.cmdsize),
                                bswap(d.dylib) };
  return r;
}

// .. LC_SUB_FRAMEWORK .........................................................

namespace lowlevel {

struct sub_framework_command {
  uint32_t cmd;
  uint32_t cmdsize;
  lc_str   umbrella;
};

}

inline lowlevel::sub_framework_command 
bswap(const lowlevel::sub_framework_command &c)
{
  lowlevel::sub_framework_command r = { bswap(c.cmd),
                                        bswap(c.cmdsize),
                                        bswap(c.umbrella) };
  return r;
}

// .. LC_SUB_CLIENT ............................................................

namespace lowlevel {

struct sub_client_command {
  uint32_t cmd;
  uint32_t cmdsize;
  lc_str   client;
};

}

inline lowlevel::sub_client_command 
bswap(const lowlevel::sub_client_command &c)
{
  lowlevel::sub_client_command r = { bswap(c.cmd),
                                     bswap(c.cmdsize),
                                     bswap(c.client) };
  return r;
}

// .. LC_SUB_UMBRELLA ..........................................................

namespace lowlevel {

struct sub_umbrella_command {
  uint32_t cmd;
  uint32_t cmdsize;
  lc_str   sub_umbrella;
};

}

inline lowlevel::sub_umbrella_command 
bswap(const lowlevel::sub_umbrella_command &c)
{
  lowlevel::sub_umbrella_command r = { bswap(c.cmd),
                                       bswap(c.cmdsize),
                                       bswap(c.sub_umbrella) };
  return r;
}

// .. LC_SUB_LIBRARY ...........................................................

namespace lowlevel {

struct sub_library_command {
  uint32_t cmd;
  uint32_t cmdsize;
  lc_str   sub_library;
};

}

inline lowlevel::sub_library_command 
bswap(const lowlevel::sub_library_command &c)
{
  lowlevel::sub_library_command r = { bswap(c.cmd),
                                      bswap(c.cmdsize),
                                      bswap(c.sub_library) };
  return r;
}

// .. LC_PREBOUND_DYLIB ........................................................

namespace lowlevel {

struct prebound_dylib_command {
  uint32_t cmd;
  uint32_t cmdsize;
  lc_str   name;
  uint32_t nmodules;
  lc_str   linked_modules;
};

}

// .. LC_((ID|LOAD)_DYLINKER|DYLD_ENVIRONMENT) .................................

namespace lowlevel {

struct dylinker_command {
  uint32_t cmd;
  uint32_t cmdsize;
  lc_str   name;
};

}

inline lowlevel::dylinker_command
bswap(const lowlevel::dylinker_command &c)
{
  lowlevel::dylinker_command r = { bswap(c.cmd),
				   bswap(c.cmdsize),
				   bswap(c.name) };
  return r;
}

// .. LC_(UNIX)THREAD ..........................................................

namespace lowlevel {

struct thread_command {
  uint32_t cmd;
  uint32_t cmdsize;
  // Followed by the following fields REPEATED:
  // {
  //   uint32_t         flavor;
  //   uint32_t         count;
  //   xxx_thread_state state; /* VARIABLE LENGTH */
  // }
};

}

// .. LC_ROUTINES[_64] .........................................................

namespace lowlevel {

struct routines_command {
  uint32_t cmd;
  uint32_t cmdsize;
  uint32_t init_address;
  uint32_t init_module;
  uint32_t reserved1;
  uint32_t reserved2;
  uint32_t reserved3;
  uint32_t reserved4;
  uint32_t reserved5;
  uint32_t reserved6;
};

struct routines_command_64 {
  uint32_t cmd;
  uint32_t cmdsize;
  uint64_t init_address;
  uint64_t init_module;
  uint64_t reserved1;
  uint64_t reserved2;
  uint64_t reserved3;
  uint64_t reserved4;
  uint64_t reserved5;
  uint64_t reserved6;
};

}

// .. LC_SYMTAB ................................................................

namespace lowlevel {

struct symtab_command {
  uint32_t cmd;
  uint32_t cmdsize;
  uint32_t symoff;
  uint32_t nsyms;
  uint32_t stroff;
  uint32_t strsize;
};

}

// .. LC_DYSYMTAB ..............................................................

namespace lowlevel {

struct dysymtab_command {
  uint32_t cmd;
  uint32_t cmdsize;

  uint32_t ilocalsym;
  uint32_t nlocalsym;
  uint32_t iextdefsym;
  uint32_t nextdefsym;
  uint32_t iundefsym;
  uint32_t nundefsym;
  uint32_t tocoff;
  uint32_t ntoc;
  uint32_t modtaboff;
  uint32_t nmodtab;
  uint32_t extrefsymoff;
  uint32_t nextrefsyms;
  uint32_t indirectsymoff;
  uint32_t nindirectsyms;
  uint32_t extreloff;
  uint32_t nextrel;
  uint32_t locreloff;
  uint32_t nlocrel;
};

}

const uint32_t INDIRECT_SYMBOL_LOCAL = 0x80000000;
const uint32_t INDIRECT_SYMBOL_ABS   = 0x40000000;

namespace lowlevel {

struct dylib_table_of_contents {
  uint32_t symbol_index;
  uint32_t module_index;
};

struct dylib_module {
  uint32_t module_name;
  uint32_t iextdefsym;
  uint32_t nextdefsym;
  uint32_t irefsym;
  uint32_t nrefsyn;
  uint32_t ilocalsym;
  uint32_t nlocalsym;
  uint32_t iextrel;
  uint32_t nextrel;
  uint32_t iinit_iterm;
  uint32_t ninit_nterm;
  uint32_t objc_module_info_addr;
  uint32_t objc_module_info_size;
};

struct dylib_module_64 {
  uint32_t module_name;
  uint32_t iextdefsym;
  uint32_t nextdefsym;
  uint32_t irefsym;
  uint32_t nrefsyn;
  uint32_t ilocalsym;
  uint32_t nlocalsym;
  uint32_t iextrel;
  uint32_t nextrel;
  uint32_t iinit_iterm;
  uint32_t ninit_nterm;
  uint32_t objc_module_info_addr;
  uint64_t objc_module_info_size;  
};

struct dylib_reference {
  uint32_t isym:24;
  uint32_t flags:8;
};

}

// .. LC_TWOLEVEL_HINTS ........................................................

namespace lowlevel {

struct twolevel_hints_command {
  uint32_t cmd;
  uint32_t cmdsize;
  uint32_t offset;
  uint32_t nhints;
};

struct twolevel_hint {
  uint32_t isub_image:8;
  uint32_t itoc:24;
};

}

// .. LC_PREBIND_CKSUM .........................................................

namespace lowlevel {

struct prebind_cksum_command {
  uint32_t cmd;
  uint32_t cmdsize;
  uint32_t cksum;
};

}

// .. LC_UUID ..................................................................

namespace lowlevel {

struct uuid_command {
  uint32_t cmd;
  uint32_t cmdsize;
  uint8_t  uuid[16];
};

}

// .. LC_RPATH .................................................................

namespace lowlevel {

struct rpath_command {
  uint32_t cmd;
  uint32_t cmdsize;
  lc_str   path;
};

}

inline lowlevel::rpath_command bswap(const lowlevel::rpath_command &c)
{
  lowlevel::rpath_command r = { bswap(c.cmd),
                                bswap(c.cmdsize),
                                bswap(c.path) };
  return r;
}

// .. LC_CODE_SIGNATURE, LC_SEGMENT_SPLIT_INFO, LC_FUNCTION_STARTS, ............
//    LC_DATA_IN_CODE, LC_DYLIB_CODE_SIGN_DRS

namespace lowlevel {

struct linkedit_data_command {
  uint32_t cmd;
  uint32_t cmdsize;
  uint32_t dataoff;
  uint32_t datasize;
};

// LC_DATA_IN_CODE points at this:
struct data_in_code_entry {
  uint32_t offset;
  uint16_t length;
  uint16_t kind;
};

}

const uint16_t DICE_KIND_DATA             = 0x0001;
const uint16_t DICE_KIND_JUMP_TABLE8      = 0x0002;
const uint16_t DICE_KIND_JUMP_TABLE16     = 0x0003;
const uint16_t DICE_KIND_JUMP_TABLE32     = 0x0004;
const uint16_t DICE_KIND_ABS_JUMP_TABLE32 = 0x0005;

// .. LC_ENCRYPTION_INFO .......................................................

namespace lowlevel {

struct encryption_info_command {
  uint32_t cmd;
  uint32_t cmdsize;
  uint32_t cryptoff;
  uint32_t cryptsie;
  uint32_t cryptid;
};

struct encryption_info_command_64 {
  uint32_t cmd;
  uint32_t cmdsize;
  uint32_t cryptoff;
  uint32_t cryptsize;
  uint32_t cryptid;
  uint32_t pad;
};

}

// .. LC_VERSION_MIN_(MACOSX|IPHONEOS) .........................................

namespace lowlevel {

struct version_min_command {
  uint32_t cmd;
  uint32_t cmdsize;
  uint32_t version;
  uint32_t sdk;
};

}

inline lowlevel::version_min_command 
bswap(const lowlevel::version_min_command &c)
{
  lowlevel::version_min_command r = { bswap(c.cmd),
                                      bswap(c.cmdsize),
                                      bswap(c.version),
                                      bswap(c.sdk) };
  return r;
}

// .. LC_DYLD_INFO[_ONLY] ......................................................

namespace lowlevel {

struct dyld_info_command {
  uint32_t cmd;
  uint32_t cmdsize;

  uint32_t rebase_off;
  uint32_t rebase_size;
  uint32_t bind_off;
  uint32_t bind_size;
  uint32_t weak_bind_off;
  uint32_t weak_bind_size;
  uint32_t lazy_bind_off;       
  uint32_t lazy_bind_size;
  uint32_t export_off;
  uint32_t export_size;
};

}

const uint8_t REBASE_TYPE_POINTER         = 1;
const uint8_t REBASE_TYPE_TEXT_ABSOLUTE32 = 2;
const uint8_t REBASE_TYPE_TEXT_PCREL32    = 3;

const uint8_t REBASE_OPCODE_MASK    = 0xf0;
const uint8_t REBASE_IMMEDIATE_MASK = 0x0f;

const uint8_t REBASE_OPCODE_DONE                               = 0x00;
const uint8_t REBASE_OPCODE_SET_TYPE_IMM                       = 0x10;
const uint8_t REBASE_OPCODE_SET_SEGMENT_AND_OFFSET_ULEB        = 0x20;
const uint8_t REBASE_OPCODE_ADD_ADDR_ULEB                      = 0x30;
const uint8_t REBASE_OPCODE_ADD_ADDR_IMM_SCALED                = 0x40;
const uint8_t REBASE_OPCODE_DO_REBASE_IMM_TIMES                = 0x50;
const uint8_t REBASE_OPCODE_DO_REBASE_ULEB_TIMES               = 0x60;
const uint8_t REBASE_OPCODE_DO_REBASE_ADD_ADDR_ULEB            = 0x70;
const uint8_t REBASE_OPCODE_DO_REBASE_ULEB_TIMES_SKIPPING_ULEB = 0x80;

const uint8_t BIND_TYPE_POINTER         = 1;
const uint8_t BIND_TYPE_TEXT_ABSOLUTE32 = 2;
const uint8_t BIND_TYPE_TEXT_PCREL32    = 3;

const uint8_t BIND_SPECIAL_DYLIB_SELF            = 0;
const uint8_t BIND_SPECIAL_DYLIB_MAIN_EXECUTABLE = -1;
const uint8_t BIND_SPECIAL_DYLIB_FLAT_LOOKUP     = -2;

const uint8_t BIND_SYMBOL_FLAGS_WEAK_IMPORT         = 0x1;
const uint8_t BIND_SYMBOL_FLAGS_NON_WEAK_DEFINITION = 0x8;

const uint8_t BIND_OPCODE_MASK    = 0xf0;
const uint8_t BIND_IMMEDIATE_MASK = 0x0f;

const uint8_t BIND_OPCODE_DONE                             = 0x00;
const uint8_t BIND_OPCODE_SET_DYLIB_ORDINAL_IMM            = 0x10;
const uint8_t BIND_OPCODE_SET_DYLIB_ORDINAL_ULEB           = 0x20;
const uint8_t BIND_OPCODE_SET_DYLIB_SPECIAL_IMM            = 0x30;
const uint8_t BIND_OPCODE_SET_SYMBOL_TRAILING_FLAGS_IMM    = 0x40;
const uint8_t BIND_OPCODE_SET_TYPE_IMM                     = 0x50;
const uint8_t BIND_OPCODE_SET_ADDEND_SLEB                  = 0x60;
const uint8_t BIND_OPCODE_SET_SEGMENT_AND_OFFSET_ULEB      = 0x70;
const uint8_t BIND_OPCODE_ADD_ADDR_ULEB                    = 0x80;
const uint8_t BIND_OPCODE_DO_BIND                          = 0x90;
const uint8_t BIND_OPCODE_DO_BIND_ADD_ADDR_ULEB            = 0xa0;
const uint8_t BIND_OPCODE_DO_BIND_ADD_ADDR_IMM_SCALED      = 0xb0;
const uint8_t BIND_OPCODE_DO_BIND_ULEB_TIMES_SKIPPING_ULEB = 0xc0;

const uint8_t EXPORT_SYMBOL_FLAGS_KIND_MASK         = 0x03;
const uint8_t EXPORT_SYMBOL_FLAGS_KIND_REGULAR      = 0x00;
const uint8_t EXPORT_SYMBOL_FLAGS_KIND_THREAD_LOCAL = 0x01;
const uint8_t EXPORT_SYMBOL_FLAGS_WEAK_DEFINITION   = 0x04;
const uint8_t EXPORT_SYMBOL_FLAGS_REEXPORT          = 0x08;
const uint8_t EXPORT_SYMBOL_FLAGS_STUB_AND_RESOLVER = 0x10;

// .. LC_LINKER_OPTION .........................................................

namespace lowlevel {

struct linker_option_command {
  uint32_t cmd;
  uint32_t cmdsize;
  uint32_t count;

  // Followed by count NUL-terminated UTF-8 strings, then alignment padding
  char     strings[0];
};

}

// .. LC_SYMSEG ................................................................

namespace lowlevel {

struct symseg_command {
  uint32_t cmd;
  uint32_t cmdsize;
  uint32_t offset;
  uint32_t size;
};

}

// .. LC_IDENT .................................................................

namespace lowlevel {

struct ident_command {
  uint32_t cmd;
  uint32_t cmdsize;

  // Followed by NUL-terminated strings, then alignment padding
  char     strings[0];
};

}

// .. LC_FVMFILE ...............................................................

namespace lowlevel {

struct fvmfile_command {
  uint32_t cmd;
  uint32_t cmdsize;
  lc_str   name;
  uint32_t header_addr;
};

}

// .. LC_MAIN ..................................................................

namespace lowlevel {

struct entry_point_command {
  uint32_t cmd;
  uint32_t cmdsize;
  uint64_t entryoff;
  uint64_t stacksize;
};

}

// .. LC_SOURCE_VERSION ........................................................

namespace lowlevel {

struct source_version_command {
  uint32_t cmd;
  uint32_t cmdsize;
  uint64_t version; // A.B.C.D.E packed as a42.b10.c10.d10.e10
};

}

inline lowlevel::source_version_command
bswap(const lowlevel::source_version_command &c)
{
  lowlevel::source_version_command r = { bswap(c.cmd),
					 bswap(c.cmdsize),
					 bswap(c.version) };
  return r;
}

#pragma pack(pop)

END_MACHO_NS

#endif /* LIBMACHO_TYPES_H_ */
