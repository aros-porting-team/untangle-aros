/*----------------------*/
/* loader of game state */
/*----------------------*/

#include "main.h"
#include "savestate.h"
#include "selector.h"

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/iffparse.h>

/*---------------------------------------------------------------------------*/
/* Should be called before the first unsolved level is added to the list.    */

static void LoadHighScores(struct App *app, struct IFFHandle *in)
{
	struct HighScoreRecord hsr;
	LONG cr;

	do
	{
		cr = ReadChunkRecords(in, &hsr, sizeof(struct HighScoreRecord), 1);

		if (cr == 1)
		{
			struct HighScore *hs;

			hs = AllocPooled(app->Selector.HighScorePool, sizeof(struct HighScore));

			if (hs)
			{
				hs->Seconds = hsr.seconds;
				hs->Moves = hsr.moves;
#ifdef __AROS__
				hs->Seconds = AROS_BE2LONG(hs->Seconds);
				hs->Moves = AROS_BE2LONG(hs->Moves);
#endif
				AddTail((struct List*)&app->Selector.HighScores, (struct Node*)hs);
				app->LevelNumber++;
				app->Selector.EntryCount++;
			}
			else cr = ERROR_NO_FREE_STORE;
		}
	}
	while (cr == 1);

	if (cr < 0) StateError(app, "reading highscores", cr);
}

/*---------------------------------------------------------------------------*/

static void LoadWinPositions(struct App *app, struct IFFHandle *in)
{
	struct WinPosRecordFile wprf[2];
	LONG err = 0;

	err = ReadChunkRecords(in, wprf, sizeof(struct WinPosRecordFile) * 2, 1);

	if (err == 1)
	{
#ifdef __AROS__
		app->MainWinPos.x = AROS_BE2WORD(wprf[0].x);
		app->MainWinPos.y = AROS_BE2WORD(wprf[0].y);
		app->MainWinPos.w = AROS_BE2WORD(wprf[0].w);
		app->MainWinPos.h = AROS_BE2WORD(wprf[0].h);
		app->Selector.SelWinPos.x = AROS_BE2WORD(wprf[1].x);
		app->Selector.SelWinPos.y = AROS_BE2WORD(wprf[1].y);
		app->Selector.SelWinPos.w = AROS_BE2WORD(wprf[1].w);
		app->Selector.SelWinPos.h = AROS_BE2WORD(wprf[1].h);
#else
		app->MainWinPos.x = wprf[0].x;
		app->MainWinPos.y = wprf[0].y;
		app->MainWinPos.w = wprf[0].w;
		app->MainWinPos.h = wprf[0].h;
		app->Selector.SelWinPos.x = wprf[1].x;
		app->Selector.SelWinPos.y = wprf[1].y;
		app->Selector.SelWinPos.w = wprf[1].w;
		app->Selector.SelWinPos.h = wprf[1].h;
#endif
	}
	else StateError(app, "reading window positions", err);
}

/*---------------------------------------------------------------------------*/

static void ParseState(struct App *app, struct IFFHandle *in)
{
	LONG err;
	struct ContextNode *curch;

	StopChunk(in, ID_UNTG, ID_HSCR);
	StopChunk(in, ID_UNTG, ID_WINP);

	do
	{
		if (!(err = ParseIFF(in, IFFPARSE_SCAN)))
		{
			curch = CurrentChunk(in);

			switch (curch->cn_ID)
			{
				case ID_HSCR:   LoadHighScores(app, in);	break;
				case ID_WINP:   LoadWinPositions(app, in);  break;
			}
		}
	}
	while (!err);

	if (err != IFFERR_EOF) StateError(app, "parse", err);
}

/*--------------------------------------------------------------------------*/

static void LoadState2(struct App *app, BPTR input)
{
	struct IFFHandle *in;

	if (in = AllocIFF())
	{
		LONG ecode;

		in->iff_Stream = (IPTR)input;
		InitIFFasDOS(in);

		if ((ecode = OpenIFF(in, IFFF_READ)) == 0)
		{
			ParseState(app, in);
			CloseIFF(in);
		}
		else StateError(app, "opening IFF stream for read", ecode);

		FreeIFF(in);
	}
	else StateError(app, "opening IFF stream for read", ERROR_NO_FREE_STORE);
}

/*--------------------------------------------------------------------------*/

void LoadState(struct App *app)
{
	BPTR input;

	if (input = Open("PROGDIR:Untangle.state", MODE_OLDFILE))
	{
		LoadState2(app, input);
		Close(input);
	}
	else 
	{
		LONG err = IoErr();

		// do not report "file not found", it may happen and should be
		// silently ignored

		if (err != ERROR_OBJECT_NOT_FOUND)
			StateError(app, "opening file for read", IoErr());
	}
}
