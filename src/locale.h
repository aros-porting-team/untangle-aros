/* Untangle game, localization macros and constants. */

#include <proto/locale.h>
#include <libraries/locale.h>

extern struct Library *LocaleBase;
extern struct Catalog *Cat;

static inline STRPTR LS(int lid, STRPTR defstr)
{
	return (LocaleBase ? GetCatalogStr(Cat, lid, defstr) : defstr);
}

#define MSG_STARTUP_NO_IFFPARSE           0
#define MSG_STARTUP_WINDOW_FAILED         1
#define MSG_STARTUP_OUT_OF_CHIP_MEMORY    2
#define MSG_STARTUP_MENU_LAYOUT_FAILED    3
#define MSG_STARTUP_NO_ASL                4
#define MSG_STARTUP_NO_TIMER_DEVICE       5
#define MSG_STARTUP_OUT_OF_MEMORY         6
#define MSG_REQ_EXIT_LEVEL_BODY           7
#define MSG_REQ_EXIT_LEVEL_GADGETS        8
#define MSG_MAINWIN_INFOBAR_SIZING        9
#define MSG_ENDGAME_CONGRATULATIONS      10
#define MSG_ENDGAME_LEVELS_COMPLETED     11
#define MSG_ENDGAME_MOVES_TOTAL          12
#define MSG_ENDGAME_TIME_TOTAL           13
