/* Untangle: string utilities */

#include <proto/exec.h>
#include <exec/memory.h>

#ifdef __AROS__
#include <exec/rawfmt.h>
#include <clib/alib_protos.h>
#endif

#include "strutils.h"

extern struct Library *SysBase;

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


ULONG VFmtLen(STRPTR fmt, IPTR *args)
{
	ULONG len = 0;

#ifdef __AROS__
	RawDoFmt(fmt, (RAWARG)args, RAWFMTFUNC_COUNT, &len);
#else
	RawDoFmt(fmt, args, ProcCountChars, &len);
#endif
	return len;
}


void VFmtPut(STRPTR dest, STRPTR fmt, IPTR *args)
{
#ifdef __AROS__
	RawDoFmt(fmt, (RAWARG)args, RAWFMTFUNC_STRING, dest);
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
	STRPTR dest;
	AROS_SLOWSTACKFORMAT_PRE(fmt);
	RawDoFmt(fmt, AROS_SLOWSTACKFORMAT_ARG(fmt), RAWFMTFUNC_STRING, dest);
	AROS_SLOWSTACKFORMAT_POST(fmt);
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
