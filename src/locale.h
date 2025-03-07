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
#define MSG_SCREEN_TITLE                 14
#define MSG_MAIN_WINDOW_TITLE            15
#define MSG_LEVEL_INFOBAR_TEXT           16
#define MSG_LOAD_ERROR_NO_MEMORY         17
#define MSG_LOAD_ERROR_OPEN_FAILED       18
#define MSG_LOAD_ERROR_NO_DOTS_CHUNK     19
#define MSG_LOAD_ERROR_NO_LINE_CHUNK     20
#define MSG_LOAD_ERROR_LINE_BEFORE_DOTS  21
#define MSG_LOAD_ERROR_TOO_MANY_DOTS     22
#define MSG_LOAD_ERROR_NEGATIVE_COORDS   23
#define MSG_LOAD_ERROR_BAD_DOT_INDEX     24
#define MSG_LOAD_ERROR_DUPLICATE_LINE    25
#define MSG_LOAD_ERROR_NO_MORE_LEVELS    26
#define MSG_LOAD_ERROR_REQ_TITLE         27
#define MSG_LOAD_ERROR_OK_BUTTON         28
#define MSG_LOAD_ERROR_IFFPARSE          29
#define MSG_MENU_GAME                    30
#define MSG_MENUITEM_NEW_GAME            31
#define MSG_MENUITEM_NEW_GAME_KEY        32
#define MSG_MENUITEM_LEVEL_LIST          33
#define MSG_MENUITEM_LEVEL_LIST_KEY      34
#define MSG_MENUITEM_SAVE_LEVEL          35
#define MSG_MENUITEM_SAVE_LEVEL_KEY      36
#define MSG_MENUITEM_QUIT                37
#define MSG_MENUITEM_QUIT_KEY            38
#define MSG_LEVEL_LIST_LEVEL             39
#define MSG_LEVEL_LIST_MOVES             40
#define MSG_LEVEL_LIST_TIME              41
