#include <macho/types.h>

using namespace macho;

namespace lowlevel {

const char *SEG_PAGEZERO = "__PAGEZERO";
const char *SEG_TEXT = "__TEXT";
const char *SECT_TEXT = "__text";
const char *SECT_FVMLIB_INIT0 = "__fvmlib_init0";
const char *SECT_FVMLIB_INIT1 = "__fvmlib_init1";

const char *SEG_DATA = "__DATA";
const char *SECT_DATA = "__data";
const char *SECT_BSS = "__bss";
const char *SECT_COMMON = "__common";

const char *SEG_OBJC = "__OBJC";
const char *SECT_OBJC_SYMBOLS = "__symbol_table";
const char *SECT_OBJC_MODULES = "__module_info";
const char *SECT_OBJC_STRINGS = "__selector_strs";
const char *SECT_OBJC_REFS = "__selector_refs";

const char *SEG_ICON = "__ICON";
const char *SECT_ICON_HEADER = "__header";
const char *SECT_ICON_TIFF = "__tiff";

const char *SEG_LINKEDIT = "__LINKEDIT";

const char *SEG_UNIXSTACK = "__UNIXSTACK";

const char *SEG_IMPORT = "__IMPORT";

}
