#include <a_samp>
#include <tdi/tdw_tdi>

static
	Textdraw:text,
	Textdraw:sprite,
	Textdraw:preview_model,
	Textdraw:text_in_box;

public OnFilterScriptInit()
{
	text = tiCreateText(100.0, 10.0, !"This is text.");
	sprite = tiCreateSprite(100.0, 60.0, !"LD_CHAT:thumbup", 50.0, 50.0);
	preview_model = tiCreatePreviewModel(100.0, 110.0, 18646, 50.0, 50.0);

	tiChangeSelectable(sprite, true);
	tiChangeSelectable(preview_model, true);
	tiChangeSelectable(text_in_box, true);

	tiChangePreviewRotations(preview_model, 10.0, 10.0, 10.0);
	tiChangePreviewModel(preview_model, 1240);

	tiChangeText(text, !"This is updated text");

	tiChangeColor(text,          TDI_RGBA( 10,  10,  60, 255));
	tiChangeColor(sprite,        TDI_RGBA( 10,  10,  60, 255));
	tiChangeColor(preview_model, TDI_RGBA( 10,  10,  60, 255));

	tiShow(text);
	tiShow(sprite);
	tiShow(preview_model);
	tiShow(text_in_box);

	SelectTextDraw(0, TDI_RGBA(90, 90, 00, 255));
	return 1;
}

public OnFilterScriptExit()
{
	tiDestroy(text);
	tiDestroy(sprite);
	tiDestroy(preview_model);
	tiDestroy(text_in_box);
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (tiIsEqualId(sprite, clickedid)) {
		printf("Clicked!");
	}
	return 1;
}
