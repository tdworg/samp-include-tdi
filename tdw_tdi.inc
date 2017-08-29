/** ======================================================================== **\
	TDW Textdraw Improvements

| Version:
	1.0.0

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

// Tag macros
#define TDI_UNTAG(%1)            (_:(%1))

// Color macros
#define TDI_RGBA(%1,%2,%3,%4)    ((((%1)&0xFF)<<24)|(((%2)&0xFF)<<16)|(((%3)&0xFF)<<8)|((%4)&0xFF))

// Useful colors.
#define TDI_DEFAULT_COLOR        TDI_RGBA(255,255,255,255)
#define TDI_DEFAULT_BOX_COLOR    TDI_RGBA(0,0,0,90)
#define TDI_DEFAULT_BG_COLOR     TDI_RGBA(0,0,0,90)
#define TDI_TRANSPARENT_COLOR    TDI_RGBA(0,0,0,0)

// Text macros
#define TDI_TEXTFONT_CLAMP(%1)   (clamp(TDI_UNTAG(%1), TDI_TEXTDRAW_FONT__0, TDI_TEXTDRAW_FONT__3))

// Bit macros
#define TDI_SET_BIT(%1,%2)       (TDI_UNTAG(%1) |= TDI_UNTAG(%2))

// Constants for handles.
#define TDI_TEXTDRAW_ID_MAX      (0xfff)
#define TDI_PLAYER_ID_MAX        (0x3ff)
#define TDI_TEXTDRAW_TYPE_MAX    (0x3)
#define TDI_TEXTDRAW_FLAG_MAX    (0xff)

#define TDI_TEXTDRAW_ID_OFFSET   (20)
#define TDI_PLAYER_ID_OFFSET     (10)
#define TDI_TEXTDRAW_TYPE_OFFSET (8)

#define TDI_TEXTDRAW_ID_MASK         (TDI_TEXTDRAW_ID_MAX   << TDI_TEXTDRAW_ID_OFFSET)
#define TDI_PLAYER_ID_MASK           (TDI_PLAYER_ID_MAX     << TDI_PLAYER_ID_OFFSET)
#define TDI_TEXTDRAW_TYPE_MASK       (TDI_TEXTDRAW_TYPE_MAX << TDI_TEXTDRAW_TYPE_OFFSET)

// Handle macros.
#define TDI_SET_TEXTDRAW_ID(%1,%2)   (TDI_SET_BIT((%1),((TDI_UNTAG(%2) & TDI_TEXTDRAW_ID_MAX) << TDI_TEXTDRAW_ID_OFFSET)))
#define TDI_SET_PLAYER_ID(%1,%2)     (TDI_SET_BIT((%1),((TDI_UNTAG(%2) & TDI_PLAYER_ID_MAX) << TDI_PLAYER_ID_OFFSET)))
#define TDI_SET_TEXTDRAW_TYPE(%1,%2) (TDI_SET_BIT((%1),((TDI_UNTAG(%2) & TDI_TEXTDRAW_TYPE_MAX) << TDI_TEXTDRAW_TYPE_OFFSET)))
#define TDI_SET_TEXTDRAW_FLAG(%1,%2) (TDI_SET_BIT((%1),((TDI_UNTAG(%2) & TDI_TEXTDRAW_FLAG_MAX))))

#define TDI_GET_TEXTDRAW_ID(%1)      ((TDI_UNTAG(%1) & TDI_TEXTDRAW_ID_MASK) >>> TDI_TEXTDRAW_ID_OFFSET)
#define TDI_GET_PLAYER_ID(%1)        ((TDI_UNTAG(%1) & TDI_PLAYER_ID_MASK) >>> TDI_PLAYER_ID_OFFSET)
#define TDI_GET_TEXTDRAW_TYPE(%1)    ((TDI_UNTAG(%1) & TDI_TEXTDRAW_TYPE_MASK) >>> TDI_TEXTDRAW_TYPE_OFFSET)
#define TDI_GET_TEXTDRAW_FLAG(%1,%2) ((TDI_UNTAG(%1) & (TDI_UNTAG(%2) & TDI_TEXTDRAW_FLAG_MAX)))


enum e_TDW_TDI_TEXTDRAW_FONTS {
	TDI_TEXTDRAW_FONT__0,
	TDI_TEXTDRAW_FONT__1,
	TDI_TEXTDRAW_FONT__2,
	TDI_TEXTDRAW_FONT__3,
	TDI_TEXTDRAW_FONT__SPRITE_DRAW,
	TDI_TEXTDRAW_FONT__MODELPREVIEW
};

enum e_TDW_TDI_TEXTDRAW_TYPES {
	TDI_TEXTDRAW_TYPE__TEXT,
	TDI_TEXTDRAW_TYPE__BOX,
	TDI_TEXTDRAW_TYPE__SPRITE_DRAW,
	TDI_TEXTDRAW_TYPE__MODELPREVIEW
};

enum e_TDW_TDI_TEXTDRAW_FLAGS (<<= 1) {
	TDI_TEXTDRAW_FLAG__USE_BOX = 1
};

// Support SA:MP Fixes
#if !defined _INC_SAMP_Community_fixes && !defined FIX_const
	// Global textdraws
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

	// Player textdraws
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

// ----------------------------------------------------------------------------
// API FUNCTIONS

// Creates a normal textdraw.  It returns a handle that is NOT an index.
stock TextDraw:tiCreateText(Float:x, Float:y, const text[],
	color = TDI_DEFAULT_COLOR, font = TDI_TEXTDRAW_FONT__1,
	playerid = INVALID_PLAYER_ID, Float:letter_width = 0.2,
	Float:letter_height = 1.0, Float:width = 0.0,
	boxcolor = TDI_TRANSPARENT_COLOR)
{
	new
		TextDraw:handle;
	if (playerid == INVALID_PLAYER_ID) {
		// Create a new global textdraw.
		new
			Text:td = TextDrawCreate(x, y, text);
		TextDrawFont(td, TDI_TEXTFONT_CLAMP(font));
		TextDrawColor(td, color);
		TextDrawLetterSize(td, letter_width, letter_height);
		TextDrawSetShadow(td, 0);
		TextDrawSetOutline(td, 0);

		if (floatcmp(width, 0.0) != 0) {
			// Auto-compute the height to use it in selectable mode.
			new n = tiComputeNumberOfLines(text, width + 8.0, letter_width);
			TextDrawUseBox(td, 1);
			TextDrawBoxColor(td, boxcolor);
			TextDrawTextSize(td, x + width, 8.0 * letter_height * float(n));
			TextDrawSetProportional(td, 1);
			TDI_SET_TEXTDRAW_FLAG(handle, TDI_TEXTDRAW_FLAG__USE_BOX);
		}

		// Store information to use it later.
		TDI_SET_PLAYER_ID(handle, TDI_TEXTDRAW_ID_MAX);
		TDI_SET_TEXTDRAW_ID(handle, td);
	} else {
		// Create a new textdraw for a player.
		new
			PlayerText:td = CreatePlayerTextDraw(playerid, x, y, text);
		PlayerTextDrawFont(playerid, td, TDI_TEXTFONT_CLAMP(font));
		PlayerTextDrawColor(playerid, td, color);
		PlayerTextDrawLetterSize(playerid, td, letter_width, letter_height);
		PlayerTextDrawSetShadow(playerid, td, 0);
		PlayerTextDrawSetOutline(playerid, td, 0);
		if (floatcmp(width, 0.0) != 0) {
			PlayerTextDrawUseBox(playerid, td, 1);
			PlayerTextDrawTextSize(playerid, td, x + width, 0.0);
		}
		// Store information to use it later.
		TDI_SET_PLAYER_ID(handle, playerid);
		TDI_SET_TEXTDRAW_ID(handle, td);
	}
	// Store the type in the handle.
	TDI_SET_TEXTDRAW_TYPE(handle, TDI_TEXTDRAW_TYPE__TEXT);
	return handle;
}

// Creates a box.  It returns a handle that is NOT an index.
// TODO: STUPID boxes
stock Float:floatnround(Float:value, n)
{
	new Float:dn = floatpower(10.0, float(n));
	return floatdiv(floatround(floatadd(floatmul(value, dn), 0.5)), dn);
}
stock TextDraw:tiCreateBox(Float:x, Float:y, Float:width, Float:height,
	boxcolor = TDI_DEFAULT_BOX_COLOR, playerid = INVALID_PLAYER_ID)
{
	new
		TextDraw:handle;
	if (playerid == INVALID_PLAYER_ID) {
		// Create a new global textdraw.
		new
			Text:td = TextDrawCreate(x, y, TDW_gscPlaceholder);
		TextDrawUseBox(td, 1);
		TextDrawBoxColor(td, boxcolor);
		TextDrawLetterSize(td, 0.0, height * 0.135);
		TextDrawTextSize(td, x + width, 0.0);
		TextDrawSetProportional(td, 1);
		// Store information to use it later.
		TDI_SET_PLAYER_ID(handle, TDI_TEXTDRAW_ID_MAX);
		TDI_SET_TEXTDRAW_ID(handle, td);
	} else {
		// Create a new textdraw for a player.
		new
			PlayerText:td = CreatePlayerTextDraw(playerid,
				x, y, TDW_gscPlaceholder);
		PlayerTextDrawUseBox(playerid, td, 1);
		PlayerTextDrawFont(playerid, td, 2);
		PlayerTextDrawBoxColor(playerid, td, boxcolor);
		PlayerTextDrawLetterSize(playerid, td, 0.0, (height) * 0.135);
		PlayerTextDrawTextSize(playerid, td, x + width, 0.0);
		PlayerTextDrawSetProportional(playerid, td, 1);
		PlayerTextDrawSetOutline(playerid, td, 0);
		PlayerTextDrawSetShadow(playerid, td, 0);
		// Store information to use it later.
		TDI_SET_PLAYER_ID(handle, playerid);
		TDI_SET_TEXTDRAW_ID(handle, td);
	}
	// Store the type in the handle.
	TDI_SET_TEXTDRAW_TYPE(handle, TDI_TEXTDRAW_TYPE__BOX);
	TDI_SET_TEXTDRAW_FLAG(handle, TDI_TEXTDRAW_FLAG__USE_BOX);
	return handle;
}

// Creates a `sprite` textdraw.  It returns a handle that is NOT an index.
stock TextDraw:tiCreateSprite(Float:x, Float:y, const name[],
	Float:width, Float:height, color = TDI_DEFAULT_COLOR,
	playerid = INVALID_PLAYER_ID)
{
	new
		TextDraw:handle;
	if (playerid == INVALID_PLAYER_ID) {
		// Create a new global textdraw.
		new
			Text:td = TextDrawCreate(x, y, name);
		TextDrawUseBox(td, 1);
		TextDrawFont(td, TDI_TEXTDRAW_FONT__SPRITE_DRAW);
		TextDrawTextSize(td, width, height);
		TextDrawColor(td, color);
		// Store information to use it later.
		TDI_SET_PLAYER_ID(handle, TDI_TEXTDRAW_ID_MAX);
		TDI_SET_TEXTDRAW_ID(handle, td);
	} else {
		// Create a new textdraw for a player.
		new
			PlayerText:td = CreatePlayerTextDraw(playerid, x, y,
				name);
		PlayerTextDrawUseBox(playerid, td, 1);
		PlayerTextDrawFont(playerid, td, TDI_TEXTDRAW_FONT__SPRITE_DRAW);
		PlayerTextDrawTextSize(playerid, td, width, height);
		// Store information to use it later.
		TDI_SET_PLAYER_ID(handle, playerid);
		TDI_SET_TEXTDRAW_ID(handle, td);
	}
	// Store the type in the handle.
	TDI_SET_TEXTDRAW_TYPE(handle, TDI_TEXTDRAW_TYPE__SPRITE_DRAW);
	TDI_SET_TEXTDRAW_FLAG(handle, TDI_TEXTDRAW_FLAG__USE_BOX);
	return handle;
}

// Create a `preview model` textdraw.  It returns a handle that is NOT an index.
stock TextDraw:tiCreateModelPreview(Float:x, Float:y, modelindex, Float:width,
	Float:height, color = TDI_DEFAULT_COLOR, bgcolor = TDI_DEFAULT_BG_COLOR,
	playerid = INVALID_PLAYER_ID)
{
	new
		TextDraw:handle;
	if (playerid == INVALID_PLAYER_ID) {
		// Create a new global textdraw.
		new
			Text:td = TextDrawCreate(x, y, TDW_gscPlaceholder);
		TextDrawUseBox(td, 1);
		TextDrawFont(td, TDI_TEXTDRAW_FONT__MODELPREVIEW);
		TextDrawTextSize(td, width, height);
		TextDrawSetPreviewModel(td, modelindex);
		TextDrawColor(td, color);
		TextDrawBackgroundColor(td, bgcolor);
		// Store information to use it later.
		TDI_SET_PLAYER_ID(handle, TDI_TEXTDRAW_ID_MAX);
		TDI_SET_TEXTDRAW_ID(handle, td);
	} else {
		// Create a new textdraw for a player.
		new
			PlayerText:td = CreatePlayerTextDraw(playerid, x, y,
				TDW_gscPlaceholder);
		PlayerTextDrawUseBox(playerid, td, 1);
		PlayerTextDrawFont(playerid, td, TDI_TEXTDRAW_FONT__MODELPREVIEW);
		PlayerTextDrawTextSize(playerid, td, width, height);
		PlayerTextDrawSetPreviewModel(playerid, td, modelindex);
		PlayerTextDrawColor(playerid, td, color);
		PlayerTextDrawBackgroundColor(playerid, td, bgcolor);
		// Store information to use it later.
		TDI_SET_PLAYER_ID(handle, playerid);
		TDI_SET_TEXTDRAW_ID(handle, td);
	}
	// Store the type in the handle.
	TDI_SET_TEXTDRAW_TYPE(handle, TDI_TEXTDRAW_TYPE__MODELPREVIEW);
	TDI_SET_TEXTDRAW_FLAG(handle, TDI_TEXTDRAW_FLAG__USE_BOX);
	return handle;
}

// Destroys a textdraw.
stock tiDestroy(TextDraw:handle)
{
	new
		playerid = TDI_GET_PLAYER_ID(handle),
		td = TDI_GET_TEXTDRAW_ID(handle);
	return
		(playerid == TDI_PLAYER_ID_MAX
		? (TextDrawDestroy(Text:td))
		: (PlayerTextDrawDestroy(playerid, PlayerText:td)));
}

// Shows a textdraw.
stock tiShow(TextDraw:handle, forplayerid = INVALID_PLAYER_ID)
{
	new
		playerid = TDI_GET_PLAYER_ID(handle),
		td = TDI_GET_TEXTDRAW_ID(handle);
	if (playerid == TDI_PLAYER_ID_MAX) {
		if (forplayerid == INVALID_PLAYER_ID) {
			TextDrawShowForAll(Text:td);
		} else {
			TextDrawShowForPlayer(playerid, Text:td);
		}
	} else {
		PlayerTextDrawShow(playerid, PlayerText:td);
	}
}

// Hides a textdraw.
stock tiHide(TextDraw:handle, forplayerid = INVALID_PLAYER_ID)
{
	new
		playerid = TDI_GET_PLAYER_ID(handle),
		td = TDI_GET_TEXTDRAW_ID(handle);
	if (playerid == TDI_PLAYER_ID_MAX) {
		if (forplayerid == INVALID_PLAYER_ID) {
			TextDrawHideForAll(Text:td);
		} else {
			TextDrawHideForPlayer(playerid, Text:td);
		}
	} else {
		PlayerTextDrawHide(playerid, PlayerText:td);
	}
}

// Sets a selectable for a textdraw.
stock tiSetSelectable(TextDraw:handle, bool:value)
{
	if (TDI_GET_TEXTDRAW_FLAG(handle, TDI_TEXTDRAW_FLAG__USE_BOX) == 0) {
		// error...
		return;
	}

	new
		playerid = TDI_GET_PLAYER_ID(handle),
		td = TDI_GET_TEXTDRAW_ID(handle);
	if (playerid == TDI_PLAYER_ID_MAX) {
		TextDrawSetSelectable(Text:td, value);
	} else {
		PlayerTextDrawSetSelectable(playerid, PlayerText:td, value);
	}
}

stock tiSetModelPreviewRots(TextDraw:handle, Float:rx, Float:ry, Float:rz, Float:zoom = 1.0)
{
	if (TDI_GET_TEXTDRAW_TYPE(handle) != _:TDI_TEXTDRAW_TYPE__MODELPREVIEW) {
		// error...
		return;
	}

	new
		playerid = TDI_GET_PLAYER_ID(handle),
		td = TDI_GET_TEXTDRAW_ID(handle);
	if (playerid == TDI_PLAYER_ID_MAX) {
		TextDrawSetPreviewRot(Text:td, rx, ry, rz, zoom);
	} else {
		PlayerTextDrawSetPreviewRot(playerid, PlayerText:td, rx, ry, rz, zoom);
	}
}

// ----------------------------------------------------------------------------
// INTERNAL FUNCTIONS

#define TDI_IS_TEXTFONT1_CHAR(%1)  (bool:(0 <= (%1) < sizeof TDW_gscLetterSizes))
#define TDI_TEXTFONT1_CHAR_LEN(%1) (Float:(TDI_IS_TEXTFONT1_CHAR(%1) ? TDW_gscLetterSizes[(%1)] : 0.0))

// Copied from <GTASA>/data/fonts.dat
static stock const  // font 1
	Float:TDW_gscLetterSizes[] =
{
    15.0,   9.0,  17.0,  27.0,  20.0,  34.0,  23.0,  12.0,
    12.0,  12.0,  21.0,  20.0,  12.0,  14.0,  12.0,  15.0,
    23.0,  15.0,  21.0,  21.0,  21.0,  21.0,  21.0,  21.0,
    20.0,  21.0,  12.0,  12.0,  24.0,  24.0,  24.0,  19.0,
    10.0,  22.0,  19.0,  19.0,  22.0,  16.0,  19.0,  24.0,
    22.0,  11.0,  16.0,  21.0,  15.0,  28.0,  24.0,  27.0,
    20.0,  25.0,  19.0,  19.0,  18.0,  23.0,  23.0,  31.0,
    23.0,  19.0,  21.0,  21.0,  13.0,  35.0,  11.0,  21.0,
    10.0,  19.0,  20.0,  14.0,  20.0,  19.0,  13.0,  20.0,
    19.0,   9.0,   9.0,  19.0,   9.0,  29.0,  19.0,  21.0,
    19.0,  19.0,  15.0,  15.0,  14.0,  18.0,  19.0,  27.0,
    20.0,  20.0,  17.0,  21.0,  17.0,  20.0,  15.0,  15.0,
    22.0,  22.0,  22.0,  22.0,  29.0,  19.0,  16.0,  16.0,
    16.0,  16.0,  11.0,  11.0,  11.0,  11.0,  27.0,  27.0,
    27.0,  27.0,  23.0,  23.0,  23.0,  23.0,  20.0,  19.0,
    19.0,  19.0,  19.0,  30.0,  14.0,  19.0,  19.0,  19.0,
    19.0,   9.0,   9.0,   9.0,   9.0,  21.0,  21.0,  21.0,
    21.0,  18.0,  18.0,  18.0,  18.0,  24.0,  19.0,  19.0,
    20.0,  18.0,  19.0,  19.0,  21.0,  19.0,  19.0,  19.0,
    19.0,  19.0,  16.0,  19.0,  19.0,  19.0,  20.0,  19.0,
    16.0,  19.0,  19.0,   9.0,  19.0,  20.0,  14.0,  29.0,
    19.0,  19.0,  19.0,  19.0,  19.0,  19.0,  21.0,  19.0,
    20.0,  32.0,  21.0,  19.0,  19.0,  19.0,  19.0,  19.0,
    19.0,  29.0,  19.0,  19.0,  19.0,  19.0,  19.0,   9.0,
     9.0,   9.0,   9.0,  19.0,  19.0,  19.0,  19.0,  19.0,
    19.0,  19.0,  19.0,  19.0,  21.0,  19.0,  10.0,   9.0
};


// Computes a text width in a box.
static stock Float:tiComputeTextWidthInBox(const text[], Float:letter_width)
{
	new
		length = strlen(text),
		index = 0,
		Float:result;
	do {
		result = floatadd(result, floatmul(TDI_TEXTFONT1_CHAR_LEN(text[index]),
			letter_width));
	} while (++index < length);
	return result;
}

// Computes a number of lines in a text.
static stock tiComputeNumberOfLines(const text[], Float:max_line_width,
	Float:letter_width)
{
	return
		floatround(floatdiv(tiComputeTextWidthInBox(text, letter_width),
		max_line_width), floatround_ceil);
}
