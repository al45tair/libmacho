#include <macho/types.h>
#include <macho/architecture.h>
#include <cstdio>

using namespace macho;

#define SUBTYPE(x, s)                           \
case CPU_SUBTYPE_##x:                           \
  cpustype = s;                                 \
  break

std::ostream &
macho::operator<<(std::ostream &os, const architecture &a)
{
  const char *cputype = NULL;
  const char *cpustype = NULL;
  char cputbuf[40];
  char cpustbuf[40];

  switch (a.cpu_type & ~CPU_ARCH_MASK) {
  case CPU_TYPE_ANY:
    cputype = "any"; 
    switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
      SUBTYPE(MULTIPLE, "any");
      SUBTYPE(LITTLE_ENDIAN, "little-endian");
      SUBTYPE(BIG_ENDIAN, "big-endian");
    }
    break;
  case CPU_TYPE_VAX:
    cputype = "VAX";
    switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
      SUBTYPE(VAX_ALL, "all");
      SUBTYPE(VAX780, "VAX-11/780");
      SUBTYPE(VAX785, "VAX-11/785");
      SUBTYPE(VAX750, "VAX-11/750");
      SUBTYPE(VAX730, "VAX-11/730");
      SUBTYPE(UVAXI, "MicroVAX I");
      SUBTYPE(UVAXII, "MicroVAX II");
      SUBTYPE(VAX8200, "VAX 8200");
      SUBTYPE(VAX8500, "VAX 8500");
      SUBTYPE(VAX8600, "VAX 8600");
      SUBTYPE(VAX8650, "VAX 8650");
      SUBTYPE(VAX8800, "VAX 8800");
      SUBTYPE(UVAXIII, "MicroVAX III");
    }
    break;
  case CPU_TYPE_MC680x0:
    cputype = "MC68K";
    switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
      SUBTYPE(MC680x0_ALL, "all");
      SUBTYPE(MC68040, "MC68040");
      SUBTYPE(MC68030, "MC68030");
    }
    break;
  case CPU_TYPE_X86:
    // What idiot put Itanium in here?! It doesn't run x86 code!
    if (a.cpu_subtype == CPU_SUBTYPE_ITANIUM
        || a.cpu_subtype == CPU_SUBTYPE_ITANIUM_2) {
      cputype = "Itanium";
      switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
        SUBTYPE(ITANIUM, "Itanium");
        SUBTYPE(ITANIUM_2, "Itanium 2");
      }
    } else if ((a.cpu_type & CPU_ARCH_MASK) == CPU_ARCH_ABI64) {
      cputype = "x86_64";
      switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
        SUBTYPE(X86_ALL, "all");
        SUBTYPE(X86_ARCH1, "arch 1");
      }
    } else {
      cputype = "x86";
      switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
        SUBTYPE(X86_ALL, "all");
        SUBTYPE(486, "i486");
        SUBTYPE(486SX, "i486sx");
        SUBTYPE(PENT, "Pentium");
        SUBTYPE(PENTPRO, "Pentium Pro");
        SUBTYPE(PENTII_M3, "Pentium II M3");
        SUBTYPE(PENTII_M5, "Pentium II M5");
        SUBTYPE(CELERON, "Celeron");
        SUBTYPE(CELERON_MOBILE, "Celeron M");
        SUBTYPE(PENTIUM_3, "Pentium III");
        SUBTYPE(PENTIUM_3_M, "Pentium III M");
        SUBTYPE(PENTIUM_3_XEON, "Pentium III Xeon");
        SUBTYPE(PENTIUM_M, "Pentium M");
        SUBTYPE(PENTIUM_4, "Pentium 4");
        SUBTYPE(PENTIUM_4_M, "Pentium 4 M");
        SUBTYPE(XEON, "Xeon");
        SUBTYPE(XEON_MP, "Xeon MP");
      }
    }
    break;
  case CPU_TYPE_MIPS:
    cputype = "MIPS";
    switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
      SUBTYPE(MIPS_ALL, "all");
      SUBTYPE(MIPS_R2300, "R2300");
      SUBTYPE(MIPS_R2600, "R2600");
      SUBTYPE(MIPS_R2800, "R2800");
      SUBTYPE(MIPS_R2000a, "R2000a");
      SUBTYPE(MIPS_R2000, "R2000");
      SUBTYPE(MIPS_R3000a, "R3000a");
      SUBTYPE(MIPS_R3000, "R3000");
    }
    break;
  case CPU_TYPE_MC98000:
    cputype = "MC98K";
    switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
      SUBTYPE(MC98000_ALL, "all");
      SUBTYPE(MC98601, "MC98601");
    }
    break;
  case CPU_TYPE_HPPA:
    cputype = "HPPA";
    switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
      SUBTYPE(HPPA_ALL, "all");
      SUBTYPE(HPPA_7100LC, "PA-7100LC");
    }
    break;
  case CPU_TYPE_MC88000:
    cputype = "MC88K";
    switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
      SUBTYPE(MC88000_ALL, "all");
      SUBTYPE(MC88100, "MC88100");
      SUBTYPE(MC88110, "MC88110");
    }
    break;
  case CPU_TYPE_SPARC:
    cputype = "SPARC";
    switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
      SUBTYPE(SPARC_ALL, "all");
    }
    break;
  case CPU_TYPE_I860:
    cputype = "i860";
    switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
      SUBTYPE(I860_ALL, "all");
      SUBTYPE(I860_860, "i860");
    }
    break;
  case CPU_TYPE_POWERPC:
    if ((a.cpu_type & CPU_ARCH_MASK) == CPU_ARCH_ABI64) {
      cputype = "PowerPC64";
      switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
        SUBTYPE(POWERPC_ALL, "all");
        SUBTYPE(POWERPC_620, "620");
        SUBTYPE(POWERPC_970, "970");
      }
    } else {
      cputype = "PowerPC";
      switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
        SUBTYPE(POWERPC_ALL, "all");
        SUBTYPE(POWERPC_601, "601");
        SUBTYPE(POWERPC_602, "602");
        SUBTYPE(POWERPC_603, "603");
        SUBTYPE(POWERPC_603e, "603e");
        SUBTYPE(POWERPC_603ev, "603ev");
        SUBTYPE(POWERPC_604, "604");
        SUBTYPE(POWERPC_604e, "604e");
        SUBTYPE(POWERPC_620, "620");
        SUBTYPE(POWERPC_750, "750");
        SUBTYPE(POWERPC_7400, "7400");
        SUBTYPE(POWERPC_7450, "7450");
        SUBTYPE(POWERPC_970, "970");
      }
    }
    break;
  case CPU_TYPE_ARM:
    if ((a.cpu_type & CPU_ARCH_MASK) == CPU_ARCH_ABI64) {
      cputype = "ARM64";
      switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
        SUBTYPE(ARM64_ALL, "all");
        SUBTYPE(ARM64_V8, "ARMv8");
      }
    } else {
      cputype = "ARM";
      switch (a.cpu_subtype & ~CPU_SUBTYPE_MASK) {
        SUBTYPE(ARM_ALL, "all");
        SUBTYPE(ARM_V4T, "ARMv4T");
        SUBTYPE(ARM_V6, "ARMv6");
        SUBTYPE(ARM_V5TEJ, "ARMv5TEJ");
        SUBTYPE(ARM_XSCALE, "XScale");
        SUBTYPE(ARM_V7, "ARMv7");
        SUBTYPE(ARM_V7F, "ARMv7F");
        SUBTYPE(ARM_V7S, "ARMv7S");
        SUBTYPE(ARM_V7K, "ARMv7K");
        SUBTYPE(ARM_V6M, "ARMv6M");
        SUBTYPE(ARM_V7M, "ARMv7M");
        SUBTYPE(ARM_V7EM, "ARMv7EM");
        SUBTYPE(ARM_V8, "ARMv8");
      }
    }
    break;
  }

  if (!cputype) {
    cputype = cputbuf;
    sprintf (cputbuf, "<cputype %08x>", a.cpu_type);
  }

  if (!cpustype) {
    cpustype = cpustbuf;
    sprintf (cpustbuf, "<subtype %08x>", a.cpu_subtype);
  }

  os << cputype << "/" << cpustype;

  if (a.cpu_subtype & CPU_SUBTYPE_LIB64)
    os << "-lib64";

  return os;
}
