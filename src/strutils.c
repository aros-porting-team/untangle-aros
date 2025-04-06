/* Untangle: string utilities */

#include <proto/exec.h>
#include <exec/memory.h>

#ifdef __AROS__
#include <exec/rawfmt.h>
#include <clib/alib_protos.h>
//#define DEBUG 1
#include <aros/debug.h>
#endif

#include "strutils.h"

#ifdef __AROS__
/* ExecBase contains pointer for bug() function */
extern struct ExecBase *SysBase;
#else
extern struct Library *SysBase;
#endif


#ifndef __AROS__
static void ProcPutChar(void)
{
	asm("move.b d0,(a3)+");
}


static void ProcCountChars(void)
{
	asm("addq.l #1,(a3)");
}
#endif

#ifndef __AROS__
ULONG VFmtLen(STRPTR fmt, LONG *args)
{
	ULONG len = 0;

	RawDoFmt(fmt, args, ProcCountChars, &len);

	return len;
}
#endif

void VFmtPut(STRPTR dest, STRPTR fmt, IPTR *args)
{
#ifdef __AROS__
	RawDoFmt(fmt, (RAWARG)args, RAWFMTFUNC_STRING, dest);
	D(bug("VFmtPut: %s -> %s\n", fmt, dest));
#else
	RawDoFmt(fmt, args, ProcPutChar, dest);
#endif
}


#ifdef __AROS__
void FmtPut(STRPTR dest, STRPTR fmt, ...)
{
	AROS_SLOWSTACKFORMAT_PRE(fmt)
	RawDoFmt(fmt, AROS_SLOWSTACKFORMAT_ARG(fmt), RAWFMTFUNC_STRING, dest);
	AROS_SLOWSTACKFORMAT_POST(fmt)
	D(bug("FmtPut: %s -> %s\n", fmt, dest));
}
#else
void FmtPut(STRPTR dest, STRPTR fmt, LONG arg1, ...)
{
	LONG *_args = &arg1;
	VFmtPut(dest, fmt, _args);
}
#endif

#ifndef __AROS__
STRPTR VFmtNew(STRPTR fmt, LONG *args)
{
	ULONG len;
	STRPTR dest;

	len = VFmtLen(fmt, args) + 1;

	if (dest = StrAlloc(len)) VFmtPut(dest, fmt, args);
	return dest;
}
#endif


#ifdef __AROS__
STRPTR FmtNew(STRPTR fmt, ...)
{
	ULONG len = 0;
	STRPTR dest;

	AROS_SLOWSTACKFORMAT_PRE(fmt);
	RawDoFmt(fmt, AROS_SLOWSTACKFORMAT_ARG(fmt), RAWFMTFUNC_COUNT, &len);
	/* len includes \0 */
	if (dest = StrAlloc(len))
	{
		RawDoFmt(fmt, AROS_SLOWSTACKFORMAT_ARG(fmt), RAWFMTFUNC_STRING, dest);
	}
	AROS_SLOWSTACKFORMAT_POST(fmt);
	D(bug("FmtNew: %s -> %s, len=%d\n", fmt, dest, len));
	return dest;
}
#else
STRPTR FmtNew(STRPTR fmt, LONG arg1, ...)
{
	LONG *_args = &arg1;
	return VFmtNew(fmt, _args);
}
#endif

	
ULONG StrLen(STRPTR s)
{
	STRPTR v = s;

	while (*v) v++;
	return (ULONG)(v - s);
}


STRPTR StrClone(STRPTR s)
{
	STRPTR d;

	if (d = StrAlloc(StrLen(s) + 1)) StrCopy(s, d);
	return d;
}


STRPTR StrCopy(STRPTR s, STRPTR d)
{
	while (*d++ = *s++);
	return (--d);
}

#if 0

STRPTR VStrJoin(STRPTR d, STRPTR *strs, WORD count)
{
	WORD i;

	for (i = 0; i < count; i++) d = StrCopy(strs[i], d);
	return d;
}


STRPTR VStrMerge(STRPTR *strs, WORD count)
{
	LONG i, len = 0;
	STRPTR d;

	for (i = 0; i < count; i++) len += StrLen(strs[i]);
	if (d = (STRPTR)AllocVec(len + 1, MEMF_ANY)) VStrJoin(d, strs, count);
	return d;
}

#endif
