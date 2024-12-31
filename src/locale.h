/* Untangle game, localization macros and constants. */

#include <proto/locale.h>
#include <libraries/locale.h>

extern struct Library *LocaleBase;
extern struct Catalog *Cat;

static inline CONST_STRPTR LS(int lid, CONST_STRPTR defstr)
{
	return (LocaleBase ? (CONST_STRPTR)(GetCatalogStr(Cat, lid, defstr)) : defstr);
}
