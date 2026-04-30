  #ifndef ERRORS_H
  #define ERRORS_H

  /*
    ELF header
  */
  #define ERROR_ELF_NULL_HEADER     2
  #define ERROR_ELF_BAD_MAGIC       3
  #define ERROR_ELF_BAD_CLASS       4
  #define ERROR_ELF_BAD_ENDIAN      5
  #define ERROR_ELF_BAD_VERSION     6
  #define ERROR_ELF_BAD_OSABI       7
  #define ERROR_ELF_BAD_ABI_VERSION 8
  #define ERROR_ELF_BAD_TYPE        9
  #define ERROR_ELF_BAD_MACHINE     10
  #define ERROR_ELF_BAD_EHSIZE      11

  /*
    program header, loading
  */
  #define ERROR_ELF_NO_PROGRAM_HEADERS 12
  #define ERROR_ELF_NO_LOAD_SEGMENTS   13
  #define ERROR_ELF_MAP_FAILED         14
  #define ERROR_ELF_UNSUPPORTED_TYPE   15

  /*
    dynamic section ERRORS
  */
  #define ERROR_DYN_NOT_PRESENT       16
  #define ERROR_DYN_NO_SYMTAB 17
  #define ERROR_DYN_NO_STRTAB 18
  #define ERROR_DYN_NO_SYMENT 19
  #define ERROR_DYN_NO_STRSZ 20
  #define ERROR_DYN_NO_HASH 21
  #define ERROR_DYN_NO_RELOCATIONS 22
  #define ERROR_DYN_NO_RELOC_SIZE 23
  #define ERROR_DYN_NO_RELOC_ENTSIZE 24
  #define ERROR_DYN_NO_PLTGOT 25
  #define ERROR_DYN_NO_JMPREL 26
  #define ERROR_DYN_NO_PLTRELSZ 27
  #define ERROR_DYN_NO_PLTREL_TYPE 28
  #define ERROR_DYN_NO_INIT 29
  #define ERROR_DYN_NO_FINI 30
  #define ERROR_DYN_NO_NEEDED 31
  #define ERROR_DYN_UNSUPPORTED_RELOC 32
  #define ERROR_DYN_UNRESOLVED_SYMBOL 33
  #define ERROR_DYN_NOT_ENOGUH_SPACE 34
  #define ERROR_SYM_NOT_FOUND 35
  #define ERROR_READING_ELF_FILE 36

  #endif
