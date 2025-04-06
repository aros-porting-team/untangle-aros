#include <proto/exec.h>
#include "strutils.h"
#include <aros/debug.h>

/* some kind of unit test. Actually only for AROS */

static void test_vfmtput(void)
{
	TEXT dest[50];
	IPTR args[] = { (IPTR)"123", 456 };
	VFmtPut(dest, "ab%sc%ldde", args);
	bug("VFmtPut: %s\n", dest);
}

static void test_fmtput(void)
{
	TEXT dest[50];
	FmtPut(dest, "ab%sc%ldde", "123", 456);
	bug("FmtPut: %s\n", dest);
}

static void test_fmtnew(void)
{
	STRPTR dest = FmtNew("ab%sc%ldde", "123", 456);
	bug("FmtNew: %s\n", dest);
	StrFree(dest);
	AvailMem(MEMF_CLEAR); /* trigger mungwall check */
}

static void test_fmtnew2(void)
{
	STRPTR dest = FmtNew("x");
	bug("FmtNew: %s\n", dest);
	StrFree(dest);
	AvailMem(MEMF_CLEAR); /* trigger mungwall check */
}

int main(void)
{
	bug("----------------\n");
	test_vfmtput();
	test_fmtput();
	test_fmtnew();
	test_fmtnew2();

	return 0;
}
