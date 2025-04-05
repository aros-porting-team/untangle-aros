/* Untangle: string utilities */

#define StrAlloc(len) (STRPTR)AllocVec((len), MEMF_ANY)
#define StrFree(str) FreeVec(str)

#ifdef __AROS__
STRPTR FmtNew(STRPTR fmt, ...);
void FmtPut(STRPTR dest, STRPTR fmt, ...);
#else
STRPTR FmtNew(STRPTR fmt, LONG arg1, ...);
void FmtPut(STRPTR dest, STRPTR fmt, ...);
#endif
ULONG VFmtLen(STRPTR fmt, LONG *args);
void VFmtPut(STRPTR dest, STRPTR fmt, IPTR *args);
STRPTR VFmtNew(STRPTR fmt, LONG *args);
ULONG StrLen(STRPTR s);
STRPTR StrCopy(STRPTR s, STRPTR d);
STRPTR StrClone(STRPTR s);
STRPTR VStrJoin(STRPTR d, STRPTR *strs, WORD count);
STRPTR VStrMerge(STRPTR *strs, WORD count);
