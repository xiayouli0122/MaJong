//
//  TypeDef.h
//  xzdd
//
//  Created by  on 12-2-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xzdd_TypeDef_h
#define xzdd_TypeDef_h

#ifndef _WIN32

#define far

#ifndef BYTE
typedef  unsigned char BYTE;
#endif

#ifndef DWORD
typedef  unsigned long DWORD;
#endif

#ifndef WORD
typedef  unsigned short WORD;
#endif

#ifndef UINT
typedef  unsigned int   UINT;
#endif

typedef int             BOOL;

typedef const void far  *LPCVOID;
typedef const char      *LPCSTR, *PCSTR;

typedef char            *LPSTR, *PSTR;

typedef void far        *LPVOID;
typedef LPCSTR LPCTSTR;

#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    1
#endif

#endif

#endif
