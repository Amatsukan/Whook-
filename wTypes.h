// Copyright (c) SuperNov4 - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef _BASETYPES_H_
#define _BASETYPES_H_

#include <time.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>

#define get_tick() timeGetTime()

typedef char				int8;
typedef short				int16;
typedef int					int32;
typedef long long           int64;

typedef signed char			sint8;
typedef signed short		sint16;
typedef signed int			sint32;
typedef signed long long    sint64;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long  uint64;

typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;
typedef unsigned long long  ulonglong;

typedef const char          cchar;
typedef const unsigned char cuchar;

#ifndef __cplusplus
typedef char bool;

 #define false	(1==0)
 #define true	(1==1)
#endif // not cplusplus

#define ISALNUM(c) (isalnum((unsigned char)(c)))
#define ISALPHA(c) (isalpha((unsigned char)(c)))
#define ISCNTRL(c) (iscntrl((unsigned char)(c)))
#define ISDIGIT(c) (isdigit((unsigned char)(c)))
#define ISGRAPH(c) (isgraph((unsigned char)(c)))
#define ISLOWER(c) (islower((unsigned char)(c)))
#define ISPRINT(c) (isprint((unsigned char)(c)))
#define ISPUNCT(c) (ispunct((unsigned char)(c)))
#define ISSPACE(c) (isspace((unsigned char)(c)))
#define ISUPPER(c) (isupper((unsigned char)(c)))
#define ISXDIGIT(c) (isxdigit((unsigned char)(c)))
#define TOASCII(c) (toascii((unsigned char)(c)))
#define TOLOWER(c) (tolower((unsigned char)(c)))
#define TOUPPER(c) (toupper((unsigned char)(c)))

#endif // _BASETYPES_H_

