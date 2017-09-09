/** ======================================================================== **\
	TDW Textdraw Improvements

| Version:
	1.1.0

| License:
	Copyright (c) 2017 Double V

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgement in the product documentation would be
		appreciated but is not required.
	2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source distribution.
\** ======================================================================== **/

#if defined _TDW_TDI_INC
	#endinput
#endif
#define _TDW_TDI_INC

#define TDI_FONT_CLAMP(%1)     clamp((%1), TDI_FONT_0, TDI_FONT_3)

#define TDI_FONT_0             (0)
#define TDI_FONT_1             (1)
#define TDI_FONT_2             (2)
#define TDI_FONT_3             (3)
#define TDI_FONT_SPRITE_DRAW   (4)
#define TDI_FONT_MODEL_PREVIEW (5)

#define TDI_TYPE_TEXT          (0)
#define TDI_TYPE_BOX           (1)
#define TDI_TYPE_SPRITE_DRAW   (2)
#define TDI_TYPE_MODEL_PREVIEW (3)

#define TDI_RGBA(%1,%2,%3,%4) (\
	  (((%1) & 0xff) << 24)\
	| (((%2) & 0xff) << 16)\
	| (((%3) & 0xff) <<  8)\
	| (((%4) & 0xff)      ))

// Default colors
#define TDI_DEFAULT_COLOR     TDI_RGBA(225, 225, 225, 255)
#define TDI_DEFAULT_BCOLOR    TDI_RGBA( 80,  80,  80,  80)
#define TDI_TRANSPARENT_COLOR TDI_RGBA(  0,   0,   0,   0)

// Default SA:MP values
#define TDI_DEFAULT_LETTER_WIDTH     (0.48)
#define TDI_DEFAULT_LETTER_HEIGHT    (1.12)
#define TDI_DEFAULT_MAX_SHADOW_SIZE  (2)
#define TDI_DEFAULT_MAX_OUTLINE_SIZE (0)

// A     |B |C            |D
// 000000 00 000 0000 0000 0000 0000 0000
//
// A - Textdraw Id
// B - Player Id
// C - Type Id
// D - Flags

#define TDI_TAG(%1) (_:(%1))
#define TDI_SET(%1,%2) (TDI_TAG(%1) |= TDI_TAG(%2))
#define TDI_GET(%1,%2,%3) ((TDI_TAG((%1)) & ((%2) << (%3))) >>> (%3))

#define TDI_GET_TEXTDRAW_ID(%1)\
	(TDI_TAG((%1)) & TDI_TEXTDRAW_ID_MASK)
#define TDI_GET_PLAYER_ID(%1)\
	TDI_GET((%1), TDI_PLAYER_ID_MASK, TDI_PLAYER_ID_OFFSET)
#define TDI_GET_TEXTDRAW_TYPE(%1)\
	TDI_GET((%1), TDI_TEXTDRAW_TYPE_MASK, TDI_TEXTDRAW_TYPE_OFFSET)
#define TDI_GET_TEXTDRAW_FLAGS(%1)\
	TDI_GET((%1), TDI_TEXTDRAW_FLAGS_MASK, TDI_TEXTDRAW_FLAGS_OFFSET)

#define TDI_SET_TEXTDRAW_ID(%1,%2)\
	(TDI_SET((%1),\
		(TDI_TAG(%2) & TDI_TEXTDRAW_ID_MASK)))
#define TDI_SET_PLAYER_ID(%1,%2)\
	(TDI_SET((%1),\
		(TDI_TAG(%2) & TDI_PLAYER_ID_MASK) << TDI_PLAYER_ID_OFFSET))
#define TDI_SET_TEXTDRAW_TYPE(%1,%2)\
	(TDI_SET((%1),\
		(TDI_TAG(%2) & TDI_TEXTDRAW_TYPE_MASK) << TDI_TEXTDRAW_TYPE_OFFSET))
#define TDI_SET_TEXTDRAW_FLAGS(%1,%2)\
	(TDI_SET((%1),\
		(TDI_TAG(%2) & TDI_TEXTDRAW_FLAGS_MASK) << TDI_TEXTDRAW_FLAGS_OFFSET))

#define TDI_TEXTDRAW_ID_MASK      (0xfff)  // max - 4096
#define TDI_PLAYER_ID_MASK        (0x7ff)  // max - 2048
#define TDI_TEXTDRAW_TYPE_MASK    (0x3)    // max - 3
#define TDI_TEXTDRAW_FLAGS_MASK   (0x3f)   // max - 63 (6 flags available)

#define TDI_PLAYER_ID_OFFSET      (12)
#define TDI_TEXTDRAW_TYPE_OFFSET  (23)
#define TDI_TEXTDRAW_FLAGS_OFFSET (25)

#define TDI_INVALID_TEXTDRAW_ID   TDI_TEXTDRAW_ID_MASK
#define TDI_INVALID_PLAYER_ID     TDI_PLAYER_ID_MASK

// Flags
#define TDI_TEXTDRAW_FLAG_USE_BOX (1 << 1)

#if !defined _INC_SAMP_Community_fixes && !defined FIX_const
	native Text:CST_TextDrawCreate(Float:x, Float:y,
		const text[]) = TextDrawCreate;
	#if defined _ALS_TextDrawCreate
		#undef TextDrawCreate
	#else
		#define _ALS_TextDrawCreate
	#endif
	#define TextDrawCreate CST_TextDrawCreate

	native CST_TextDrawSetString(Text:text,
		const string[]) = TextDrawSetString;
	#if defined _ALS_TextDrawSetString
		#undef TextDrawSetString
	#else
		#define _ALS_TextDrawSetString
	#endif
	#define TextDrawSetString CST_TextDrawSetString

	native PlayerText:CST_CreatePlayerTextDraw(playerid, Float:x, Float:y,
		const text[]) = CreatePlayerTextDraw;
	#if defined _ALS_CreatePlayerTextDraw
		#undef CreatePlayerTextDraw
	#else
		#define _ALS_CreatePlayerTextDraw
	#endif
	#define CreatePlayerTextDraw CST_CreatePlayerTextDraw

	native CST_PlayerTextDrawSetString(playerid, PlayerText:text,
		const string[]) = PlayerTextDrawSetString;
	#if defined _ALS_PlayerTextDrawSetString
		#undef PlayerTextDrawSetString
	#else
		#define _ALS_PlayerTextDrawSetString
	#endif
	#define PlayerTextDrawSetString CST_PlayerTextDrawSetString
#endif

static stock const
	TDW_gscPlaceholder[] = !"_";

stock Textdraw:tiCreateText(Float:x, Float:y, const text[],
	color = TDI_DEFAULT_COLOR, font = TDI_FONT_1, playerid = INVALID_PLAYER_ID,
	Float:letter_width = TDI_DEFAULT_LETTER_WIDTH,
	Float:letter_height = TDI_DEFAULT_LETTER_HEIGHT)
{
	new Textdraw:handle;
	// Create a new textdraw.
	if (playerid == INVALID_PLAYER_ID) {
		new Text:td = TextDrawCreate(x, y, text);
		// Text settings.
		TextDrawFont(td, TDI_FONT_CLAMP(font));
		TextDrawColor(td, color);
		TextDrawLetterSize(td, letter_width, letter_height);
		// Set to zero the shadow size.
		TextDrawSetShadow(td, 0);
		// Store the textdrawid, playerid in the handle.
		TDI_SET_TEXTDRAW_ID(handle, td);
		TDI_SET_PLAYER_ID(handle, TDI_INVALID_PLAYER_ID);
	} else {
		new PlayerText:td = CreatePlayerTextDraw(playerid, x, y, text);
		// Text settings.
		PlayerTextDrawFont(playerid, td, TDI_FONT_CLAMP(font));
		PlayerTextDrawColor(playerid, td, color);
		PlayerTextDrawLetterSize(playerid, td, letter_width, letter_height);
		// Set to zero the shadow size.
		PlayerTextDrawSetShadow(playerid, td, 0);
		// Store the textdrawid, playerid in the handle.
		TDI_SET_TEXTDRAW_ID(handle, td);
		TDI_SET_PLAYER_ID(handle, playerid);
	}
	TDI_SET_TEXTDRAW_TYPE(handle, TDI_TYPE_TEXT);
	return handle;
}

stock Textdraw:tiCreateSprite(Float:x, Float:y, const name[],
	Float:width, Float:height, color = TDI_DEFAULT_COLOR,
	playerid = INVALID_PLAYER_ID)
{
	new Textdraw:handle;
	// Create a new textdraw.
	if (playerid == INVALID_PLAYER_ID) {
		new Text:td = TextDrawCreate(x, y, name);
		// Text settings.
		TextDrawFont(td, TDI_FONT_SPRITE_DRAW);
		TextDrawColor(td, color);
		TextDrawTextSize(td, width, height);
		// Store the textdrawid, playerid in the handle.
		TDI_SET_TEXTDRAW_ID(handle, td);
		TDI_SET_PLAYER_ID(handle, TDI_INVALID_PLAYER_ID);
	} else {
		new PlayerText:td = CreatePlayerTextDraw(playerid, x, y, name);
		// Text settings.
		PlayerTextDrawFont(playerid, td, TDI_FONT_SPRITE_DRAW);
		PlayerTextDrawColor(playerid, td, color);
		PlayerTextDrawTextSize(playerid, td, width, height);
		// Store the textdrawid, playerid in the handle.
		TDI_SET_TEXTDRAW_ID(handle, td);
		TDI_SET_PLAYER_ID(handle, playerid);
	}
	TDI_SET_TEXTDRAW_TYPE(handle, TDI_TYPE_SPRITE_DRAW);
	TDI_SET_TEXTDRAW_FLAGS(handle, TDI_TEXTDRAW_FLAG_USE_BOX);
	return handle;
}

stock Textdraw:tiCreatePreviewModel(Float:x, Float:y, modelindex, Float:width,
	Float:height, color = TDI_DEFAULT_COLOR, bgcolor = TDI_DEFAULT_BCOLOR,
	playerid = INVALID_PLAYER_ID)
{
	new Textdraw:handle;
	// Create a new textdraw.
	if (playerid == INVALID_PLAYER_ID) {
		new Text:td = TextDrawCreate(x, y, TDW_gscPlaceholder);
		// Text settings.
		TextDrawFont(td, TDI_FONT_MODEL_PREVIEW);
		TextDrawColor(td, color);
		TextDrawTextSize(td, width, height);
		// Box settings.
		TextDrawUseBox(td, 1);
		TextDrawBackgroundColor(td, bgcolor);
		// Preview model settings.
		TextDrawSetPreviewModel(td, modelindex);
		// Store the textdrawid, playerid in the handle.
		TDI_SET_TEXTDRAW_ID(handle, td);
		TDI_SET_PLAYER_ID(handle, TDI_INVALID_PLAYER_ID);
	} else {
		new PlayerText:td = CreatePlayerTextDraw(playerid, x, y,
			TDW_gscPlaceholder);
		// Text settings.
		PlayerTextDrawFont(playerid, td, TDI_FONT_MODEL_PREVIEW);
		PlayerTextDrawColor(playerid, td, color);
		PlayerTextDrawTextSize(playerid, td, width, height);
		// Box settings.
		PlayerTextDrawUseBox(playerid, td, 1);
		PlayerTextDrawBackgroundColor(playerid, td, bgcolor);
		// Preview model settings.
		PlayerTextDrawSetPreviewModel(playerid, td, modelindex);
		// Store the textdrawid, playerid in the handle.
		TDI_SET_TEXTDRAW_ID(handle, td);
		TDI_SET_PLAYER_ID(handle, playerid);
	}
	TDI_SET_TEXTDRAW_TYPE(handle, TDI_TYPE_MODEL_PREVIEW);
	TDI_SET_TEXTDRAW_FLAGS(handle, TDI_TEXTDRAW_FLAG_USE_BOX);
	return handle;
}

stock tiShow(Textdraw:handle, forplayerid = INVALID_PLAYER_ID)
{
	new
		playerid = TDI_GET_PLAYER_ID(handle),
		textdrawid = TDI_GET_TEXTDRAW_ID(handle),
		ret;
	if (playerid == TDI_INVALID_PLAYER_ID) {
		if (forplayerid == INVALID_PLAYER_ID) {
			ret = TextDrawShowForAll(Text:textdrawid);
		} else {
			ret = TextDrawShowForPlayer(playerid, Text:textdrawid);
		}
	} else {
		ret = PlayerTextDrawShow(playerid, PlayerText:textdrawid);
	}
	return ret;
}

stock tiHide(Textdraw:handle, forplayerid = INVALID_PLAYER_ID)
{
	new
		playerid = TDI_GET_PLAYER_ID(handle),
		textdrawid = TDI_GET_TEXTDRAW_ID(handle),
		ret;
	if (playerid == TDI_INVALID_PLAYER_ID) {
		if (forplayerid == INVALID_PLAYER_ID) {
			ret = TextDrawHideForAll(Text:textdrawid);
		} else {
			ret = TextDrawHideForPlayer(playerid, Text:textdrawid);
		}
	} else {
		ret = PlayerTextDrawHide(playerid, PlayerText:textdrawid);
	}
	return ret;
}

stock tiDestroy(Textdraw:handle)
{
	new
		playerid = TDI_GET_PLAYER_ID(handle),
		textdrawid = TDI_GET_TEXTDRAW_ID(handle),
		ret;
	if (playerid == TDI_INVALID_PLAYER_ID) {
		ret = TextDrawDestroy(Text:textdrawid);
	} else {
		ret = PlayerTextDrawDestroy(playerid, PlayerText:textdrawid);
	}
	return ret;
}

stock bool:tiChangeSelectable(Textdraw:handle, bool:value)
{
	if (TDI_GET_TEXTDRAW_FLAGS(handle) & TDI_TEXTDRAW_FLAG_USE_BOX == 0)
		return false;
	new
		playerid = TDI_GET_PLAYER_ID(handle),
		td = TDI_GET_TEXTDRAW_ID(handle);
	if (playerid == TDI_INVALID_PLAYER_ID) {
		TextDrawSetSelectable(Text:td, value);
	} else {
		PlayerTextDrawSetSelectable(playerid, PlayerText:td, value);
	}
	return true;
}

stock bool:tiChangePreviewRotations(Textdraw:handle, Float:x, Float:y, Float:z,
	Float:zoom = 1.0)
{
	if (TDI_GET_TEXTDRAW_TYPE(handle) != TDI_TYPE_MODEL_PREVIEW)
		return false;
	new
		playerid = TDI_GET_PLAYER_ID(handle),
		td = TDI_GET_TEXTDRAW_ID(handle);
	if (playerid == TDI_INVALID_PLAYER_ID) {
		TextDrawSetPreviewRot(Text:td, x, y, z, zoom);
	} else {
		PlayerTextDrawSetPreviewRot(playerid, PlayerText:td, x, y, z, zoom);
	}
	return true;
}

stock bool:tiChangePreviewModel(Textdraw:handle, modelindex)
{
	if (TDI_GET_TEXTDRAW_TYPE(handle) != TDI_TYPE_MODEL_PREVIEW)
		return false;
	new
		playerid = TDI_GET_PLAYER_ID(handle),
		td = TDI_GET_TEXTDRAW_ID(handle);
	if (playerid == TDI_INVALID_PLAYER_ID) {
		TextDrawSetPreviewModel(Text:td, modelindex);
	} else {
		PlayerTextDrawSetPreviewModel(playerid, PlayerText:td, modelindex);
	}
	return true;
}

stock tiChangeText(Textdraw:handle, const text[])
{
	if (TDI_GET_TEXTDRAW_TYPE(handle) != TDI_TYPE_TEXT)
		return 0;
	new
		playerid = TDI_GET_PLAYER_ID(handle),
		td = TDI_GET_TEXTDRAW_ID(handle),
		ret;
	if (playerid == TDI_INVALID_PLAYER_ID) {
		ret = TextDrawSetString(Text:td, text);
	} else {
		ret = PlayerTextDrawSetString(playerid, PlayerText:td, text);
	}
	return ret;
}

stock tiChangeColor(Textdraw:handle, color)
{
	new
		playerid = TDI_GET_PLAYER_ID(handle),
		td = TDI_GET_TEXTDRAW_ID(handle),
		ret;
	if (playerid == TDI_INVALID_PLAYER_ID) {
		ret = TextDrawColor(Text:td, color);
	} else {
		ret = PlayerTextDrawColor(playerid, PlayerText:td, color);
	}
	return ret;
}

stock bool:tiIsEqualId(Textdraw:handle, {PlayerText, Text}:id, tag = tagof(id))
{
	static
		playerid,
		td;
	playerid = TDI_GET_PLAYER_ID(handle);
	td = TDI_GET_TEXTDRAW_ID(handle);
	switch (tag) {
		case (tagof(PlayerText:)): {
			return (playerid == TDI_INVALID_PLAYER_ID)
				? false
				: (_:td == _:id);
		}
		case (tagof(Text:)): {
			return (playerid != TDI_INVALID_PLAYER_ID)
				? false
				: (_:td == _:id);
		}
	}
	return false;
}
