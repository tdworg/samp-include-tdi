#include <a_samp>
#include <tdi/tdw_tdi>

new Textdraw:td;
new Textdraw:mp;
new Textdraw:sp;
new Textdraw:bx;

public OnFilterScriptInit()
{
	td = tdiCreateText(32.0, 10.0, !"This is text", .playerid = 0);

	tdiShow(td);

	tdiSetString(td, !"Tthis is string!");
	tdiSetShadow(td, 2);
	tdiSetOutline(td, 0);
	tdiSetTextSize(td, 300.0, 50.0);
	tdiSetLetterSize(td, 0.3, 1.0);
	tdiSetFont(td, 2);
	tdiSetAlign(td, TDW_TDI_ALIGN_RIGHT);
	tdiSetBackgroundColor(td, TDW_TDI_RGBA(255, 20, 20, 230));
	tdiSetBoxColor(td, TDW_TDI_RGBA(255, 20, 20, 230));
	tdiSetColor(td, TDW_TDI_RGBA(20, 255, 20, 230));
	tdiShow(td);

	mp = tdiCreateModelPreview(200.0, 30.0, 500, 100.0, 100.0, .playerid = 0);
	tdiShow(mp);

	sp = tdiCreateSprite(200.0, 150.0, !"LD_SPAC:WHITE", 100.0, 100.0, .playerid = 0);
	tdiShow(sp);

	bx = tdiCreateBox(200.0, 260.0, 10.0, 10.0, .playerid = 0);
	tdiShow(bx);
}

public OnFilterScriptExit()
{
	tdiDestroy(td);
	tdiDestroy(mp);
	tdiDestroy(sp);
	tdiDestroy(bx);
}
