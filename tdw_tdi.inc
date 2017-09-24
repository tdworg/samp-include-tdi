/*
 * TDW Textdraw Improvments
 *
 * Copyright (c) 2017 Double V
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgement in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#if defined _TDW_TDI_INC_
	#endinput
#endif
#define _TDW_TDI_INC_

/*
 * SA:MP fixes
 *
 * Some SA:MP natives don't use `const` qualifier when they could. We need
 * to redefine them to fix the problem.
 *
 * These declarations are used if the `SA:MP fixes` library is not
 * included before.
 */
#if !defined _INC_SAMP_Community_fixes && !defined FIX_const

	/*
	 * Global textdraws
	 */

	native Text:TDW_TDI_TextDrawCreate(Float:x, Float:y,
		const text[]) = TextDrawCreate;
	native TDW_TDI_TextDrawSetString(Text:text,
		const string[]) = TextDrawSetString;

	#if defined _ALS_TextDrawCreate
		#undef TextDrawCreate
	#else
		#define _ALS_TextDrawCreate
	#endif
	#define TextDrawCreate TDW_TDI_TextDrawCreate

	#if defined _ALS_TextDrawSetString
		#undef TextDrawSetString
	#else
		#define _ALS_TextDrawSetString
	#endif
	#define TextDrawSetString TDW_TDI_TextDrawSetString

	/*
	 * Player textdraws
	 */

	native PlayerText:TDW_TDI_CreatePlayerTextDraw(playerid, Float:x, Float:y,
		const text[]) = CreatePlayerTextDraw;
	native TDW_TDI_PlayerTextDrawSetString(playerid, PlayerText:text,
		const string[]) = PlayerTextDrawSetString;

	#if defined _ALS_CreatePlayerTextDraw
		#undef CreatePlayerTextDraw
	#else
		#define _ALS_CreatePlayerTextDraw
	#endif
	#define CreatePlayerTextDraw TDW_TDI_CreatePlayerTextDraw

	#if defined _ALS_PlayerTextDrawSetString
		#undef PlayerTextDrawSetString
	#else
		#define _ALS_PlayerTextDrawSetString
	#endif
	#define PlayerTextDrawSetString TDW_TDI_PlayerTextDrawSetString
#endif

/*
 * Useful macros
 */

/* Converts RGBA to HEX */
#define TDW_TDI_RGBA(%1,%2,%3,%4)\
	((((%1) & 0xFF) << 24) | (((%2) & 0xFF) << 16) | (((%3) & 0xFF) << 8) |\
		(((%4) & 0xFF)))

/* Returns only a valid font */
#define TDW_TDI_TEXTFONT_CLAMP(%1) clamp((%1), TDW_TDI_FONT_0, TDW_TDI_FONT_3)

/* Returns a mask. */
#define TDW_TDI_SHIFT_BITS(%1,%2) (_:(%1) << _:(%2))

/* Returns true when the passed array is packed, otherwise returns false. */
#define TDW_TDI_IS_PACKED_STRING(%1) (%1{0} != 0)

/* Returns true if the passed slot is used, otherwise returns false.  */
#define TDW_TDI_IS_USED_TEXTDRAW(%1) (TDW_TDI_IS_VALID_TEXTDRAW(%1) &&\
	TDW_gsData[_:(%1)][EI_TDW_TDI_DATA_BITS])

/* Returns true if the passed id is valid, otherwise returns false. */
#define TDW_TDI_IS_VALID_TEXTDRAW(%1) (0 <= _:(%1) < sizeof TDW_gsData)

/* Returns true if the passed id is valid for all player textdraws,
 * otherwise returns false.
 */
#define TDW_TDI_IS_PLAYER_TEXTDRAW(%1) (_:(%1) > TDW_TDI_MAX_TEXTDRAWS)

/* Returns the player's id, otherwise returns INVALID_PLAYER_ID. */
#define TDW_TDI_GET_PLAYER_ID(%1) (TDW_TDI_IS_PLAYER_TEXTDRAW(%1) ?\
 	((_:(%1) - TDW_TDI_MAX_TEXTDRAWS) / TDW_TDI_MAX_PLAYER_TEXTDRAWS) :\
 	INVALID_PLAYER_ID)

/*
 * Internal constants
 */

/* Fonts */
#define TDW_TDI_FONT_0             (0)
#define TDW_TDI_FONT_1             (1)
#define TDW_TDI_FONT_2             (2)
#define TDW_TDI_FONT_3             (3)
#define TDW_TDI_FONT_SPRITE_DRAW   (4)
#define TDW_TDI_FONT_PREVIEW_MODEL (5)

/* Align */
#define TDW_TDI_ALIGN_LEFT   (1)
#define TDW_TDI_ALIGN_CENTER (2)
#define TDW_TDI_ALIGN_RIGHT  (3)

/* Default values */
#define TDW_TDI_DEFAULT_FONT         (TDW_TDI_FONT_1)
#define TDW_TDI_DEFAULT_LWIDTH       (0.48)
#define TDW_TDI_DEFAULT_LHEIGHT      (1.12)
#define TDW_TDI_DEFAULT_OUTLINE_SIZE (0)
#define TDW_TDI_DEFAULT_SHADOW_SIZE  (2)
#define TDW_TDI_DEFAULT_COLOR        TDW_TDI_RGBA(255, 255, 255, 255)
#define TDW_TDI_DEFAULT_BCOLOR       TDW_TDI_RGBA( 80,  80,  80,  80)

/* Offsets for reading/writing the data in a cell */
#define TDW_TDI_BOF_SHADOW  (0)
#define TDW_TDI_BOF_OUTLINE (8)
#define TDW_TDI_BOF_ALIGN   (16)
#define TDW_TDI_BOF_FONT    (20)
#define TDW_TDI_BOF_BOX     (24)
#define TDW_TDI_BOF_TYPE    (25)

/* Textdraw types */
#define TDW_TDI_TYPE_TEXT          (0)
#define TDW_TDI_TYPE_SPRITE_DRAW   (1)
#define TDW_TDI_TYPE_PREVIEW_MODEL (2)
#define TDW_TDI_TYPE_BOX           (3)

/* Masks for reading/writing the data in a cell */
enum E_TDW_TDI_BITS (<<= 1) {
	EI_TDW_TDI_BITS_SHADOW  = TDW_TDI_SHIFT_BITS(0xff, TDW_TDI_BOF_SHADOW),
	EI_TDW_TDI_BITS_OUTLINE = TDW_TDI_SHIFT_BITS(0xff, TDW_TDI_BOF_OUTLINE),
	EI_TDW_TDI_BITS_ALIGN   = TDW_TDI_SHIFT_BITS(0xf,  TDW_TDI_BOF_ALIGN),
	EI_TDW_TDI_BITS_FONT    = TDW_TDI_SHIFT_BITS(0xf,  TDW_TDI_BOF_FONT),
	EI_TDW_TDI_BITS_BOX     = TDW_TDI_SHIFT_BITS(0x1,  TDW_TDI_BOF_BOX),
	EI_TDW_TDI_BITS_TYPE    = TDW_TDI_SHIFT_BITS(0x3,  TDW_TDI_BOF_TYPE)
};

/* Fields for each textdraws */
enum E_TDW_TDI_DATA {
	EI_TDW_TDI_DATA_ID,
	Float:EI_TDW_TDI_DATA_POS_X,
	Float:EI_TDW_TDI_DATA_POS_Y,
	Float:EI_TDW_TDI_DATA_LETTER_X,
	Float:EI_TDW_TDI_DATA_LETTER_Y,
	Float:EI_TDW_TDI_DATA_TEXT_X,
	Float:EI_TDW_TDI_DATA_TEXT_Y,
	EI_TDW_TDI_DATA_COLOR,
	EI_TDW_TDI_DATA_BG_COLOR,
	EI_TDW_TDI_DATA_BOX_COLOR,
	E_TDW_TDI_BITS:EI_TDW_TDI_DATA_BITS
};

/* SA:MP limits */
#define TDW_TDI_MAX_TEXT_BUFFER_SIZE (1024)

/*
 * User constants
 */

#if !defined TDW_TDI_MAX_TEXTDRAWS
	#define TDW_TDI_MAX_TEXTDRAWS (256)
#else
	#assert TDW_TDI_MAX_TEXTDRAWS <= MAX_TEXT_DRAWS
#endif

#if !defined TDW_TDI_MAX_PLAYER_TEXTDRAWS
	#define TDW_TDI_MAX_PLAYER_TEXTDRAWS (16)
#else
	#assert TDW_TDI_MAX_PLAYER_TEXTDRAWS <= MAX_PLAYER_TEXT_DRAWS
#endif

/*
 * Data
 */

static stock
	TDW_gsData[TDW_TDI_MAX_TEXTDRAWS + (MAX_PLAYERS *
		TDW_TDI_MAX_PLAYER_TEXTDRAWS)][E_TDW_TDI_DATA],
	TDW_gsTextBuffer[TDW_TDI_MAX_TEXT_BUFFER_SIZE char];

static stock const
	TDW_gsPlaceholder[] = !"_";

/*
 * Internal functions
 */

/* Returns a free slot in the array */
static stock tdiGetFreeSlot(playerid = INVALID_PLAYER_ID)
{
	new
		end_index,
		start_index;

	if (playerid == INVALID_PLAYER_ID) {
		end_index = TDW_TDI_MAX_TEXTDRAWS;
		start_index = 0;
	} else {
		start_index = TDW_TDI_MAX_TEXTDRAWS + (playerid *
			TDW_TDI_MAX_PLAYER_TEXTDRAWS);
		end_index = start_index + TDW_TDI_MAX_PLAYER_TEXTDRAWS;
	}

	do {} while (--end_index >= start_index &&
		TDW_gsData[end_index][EI_TDW_TDI_DATA_BITS]);

	return end_index < start_index ? INVALID_TEXT_DRAW : end_index;
}

/**/
static stock tdiTrimRight(string[])
{
	new
		length = strlen(string),
		pos = length;

	if (TDW_TDI_IS_PACKED_STRING(string)) {
		while (pos-- != 0 && string{pos} == ' ')
		{}
	} else {
		while (pos-- != 0 && string[pos] == ' ')
		{}
	}

	return strdel(string, pos + 1, length);
}

/*
 * API functions
 */

/* Creates a new textdraw */
stock Textdraw:tdiCreateText(Float:x, Float:y, const text[],
	color = TDW_TDI_DEFAULT_COLOR, font = TDW_TDI_DEFAULT_FONT,
	playerid = INVALID_PLAYER_ID,
	Float:letter_width = TDW_TDI_DEFAULT_LWIDTH,
	Float:letter_height = TDW_TDI_DEFAULT_LHEIGHT)
{
	// find the slot where we will store the textdraw's data.
	new
		slotid = tdiGetFreeSlot(playerid);
	if (slotid == INVALID_TEXT_DRAW)
		return Textdraw:INVALID_TEXT_DRAW;

	// prepare the passed settings to set and store them.
	font = TDW_TDI_TEXTFONT_CLAMP(font);

	// copy the passed string into the buffer to use it later.
	if (TDW_TDI_IS_PACKED_STRING(text)) {
		TDW_gsTextBuffer{0} = EOS;
		strcat(TDW_gsTextBuffer, text);
	} else {
		strpack(TDW_gsTextBuffer, text);
	}

	/* fix: If the last character in the text is a space (" "), the text will
	 * all be blank.
	 */
	tdiTrimRight(TDW_gsTextBuffer);

	// create a new textdraw.
	if (playerid == INVALID_PLAYER_ID) {  // global textdraw.
		new
			Text:textid = TextDrawCreate(x, y,
				TDW_gsTextBuffer);

		if (_:textid == INVALID_TEXT_DRAW)
			return Textdraw:INVALID_TEXT_DRAW;

		TextDrawFont(textid, font);
		TextDrawColor(textid, color);
		TextDrawLetterSize(textid, letter_width, letter_height);

		TextDrawSetShadow(textid, 0);

		TDW_gsData[slotid][EI_TDW_TDI_DATA_ID] = _:textid;
	} else {  // player textdraw.

		/* check the player's connection to the server, because
		 * CreatePlayerTextDraw returns zero when the player isn't
		 * connected (the function should return INVALID_TEXT_DRAW
		 * instead of zero)
		 */
		if (IsPlayerConnected(playerid) == 0)
			return Textdraw:INVALID_TEXT_DRAW;

		new
			PlayerText:textid = CreatePlayerTextDraw(playerid, x, y,
				TDW_gsTextBuffer);

		if (_:textid == INVALID_TEXT_DRAW)
			return Textdraw:INVALID_TEXT_DRAW;

		PlayerTextDrawFont(playerid, textid, font);
		PlayerTextDrawColor(playerid, textid, color);
		PlayerTextDrawLetterSize(playerid, textid, letter_width,
			letter_height);

		PlayerTextDrawSetShadow(playerid, textid, 0);

		TDW_gsData[slotid][EI_TDW_TDI_DATA_ID] = _:textid;
	}

	// store the passed settings in the array.
	TDW_gsData[slotid][EI_TDW_TDI_DATA_POS_X] = x;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_POS_Y] = y;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_COLOR] = color;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_LETTER_X] = letter_width;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_LETTER_Y] = letter_height;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_BITS] = E_TDW_TDI_BITS:(
		((TDW_TDI_TYPE_TEXT << TDW_TDI_BOF_TYPE) & _:EI_TDW_TDI_BITS_TYPE) |
		((_:font << TDW_TDI_BOF_FONT) & _:EI_TDW_TDI_BITS_FONT)
	);

	return Textdraw:slotid;
}

/* Destroys a textdraw */
stock bool:tdiDestroy(Textdraw:slotid)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawDestroy(playerid, PlayerText:textid);
	} else {
		TextDrawDestroy(Text:textid);
	}

	// reset the data to free the slot.
	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] = E_TDW_TDI_BITS:0;
	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID] = INVALID_TEXT_DRAW;

	return true;
}

/* Shows a textdraw */
stock tdiShow(Textdraw:slotid, forplayerid = INVALID_PLAYER_ID)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawShow(playerid, PlayerText:textid);
	} else {
		if (forplayerid == INVALID_PLAYER_ID) {
			TextDrawShowForAll(Text:textid);
		} else {
			TextDrawShowForPlayer(forplayerid, Text:textid);
		}
	}

	return true;
}

/* Hides a textdraw */
stock tdiHide(Textdraw:slotid, forplayerid = INVALID_PLAYER_ID)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawHide(playerid, PlayerText:textid);
	} else {
		if (forplayerid == INVALID_PLAYER_ID) {
			TextDrawHideForAll(Text:textid);
		} else {
			TextDrawHideForPlayer(forplayerid, Text:textid);
		}
	}

	return true;
}

/* Sets a new string */
stock tdiSetString(Textdraw:slotid, const text[])
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	// copy the passed string into the buffer to use it later.
	if (TDW_TDI_IS_PACKED_STRING(text)) {
		TDW_gsTextBuffer[0] = EOS;
		strcat(TDW_gsTextBuffer, text);
	} else {
		strpack(TDW_gsTextBuffer, text);
	}

	/* fix: If the last character in the text is a space (" "), the text will
	 * all be blank.
	 */
	tdiTrimRight(TDW_gsTextBuffer);

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawSetString(playerid, PlayerText:textid, TDW_gsTextBuffer);
	} else {
		TextDrawSetString(Text:textid, TDW_gsTextBuffer);
	}

	return true;
}

/* Sets shadow for a textdraw */
stock tdiSetShadow(Textdraw:slotid, size)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawSetShadow(playerid, PlayerText:textid, size);
	} else {
		TextDrawSetShadow(Text:textid, size);
	}

	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] &= ~EI_TDW_TDI_BITS_SHADOW;
	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] |= E_TDW_TDI_BITS:(
		size << TDW_TDI_BOF_SHADOW) & EI_TDW_TDI_BITS_SHADOW;

	return true;
}

/* Sets outline for a textdraw */
stock tdiSetOutline(Textdraw:slotid, size)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawSetOutline(playerid, PlayerText:textid, size);
	} else {
		TextDrawSetOutline(Text:textid, size);
	}

	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] &= ~EI_TDW_TDI_BITS_OUTLINE;
	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] |= E_TDW_TDI_BITS:(
		size << TDW_TDI_BOF_OUTLINE) & EI_TDW_TDI_BITS_OUTLINE;

	return true;
}

/* Sets text size for a textdraw. */
stock tdiSetTextSize(Textdraw:slotid, Float:x, Float:y)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawTextSize(playerid, PlayerText:textid, x, y);
	} else {
		TextDrawTextSize(Text:textid, x, y);
	}

	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_TEXT_X] = x;
	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_TEXT_Y] = y;

	return true;
}

/* Sets letter size for a textdraw. */
stock tdiSetLetterSize(Textdraw:slotid, Float:x, Float:y)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawLetterSize(playerid, PlayerText:textid, x, y);
	} else {
		TextDrawLetterSize(Text:textid, x, y);
	}

	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_LETTER_X] = x;
	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_LETTER_Y] = y;

	return true;
}

/* Sets a font for a textdraw. */
stock tdiSetFont(Textdraw:slotid, font)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	font = TDW_TDI_TEXTFONT_CLAMP(font);

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawFont(playerid, PlayerText:textid, font);
	} else {
		TextDrawFont(Text:textid, font);
	}

	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] &= ~EI_TDW_TDI_BITS_FONT;
	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] |= E_TDW_TDI_BITS:(
		font << TDW_TDI_BOF_FONT) & EI_TDW_TDI_BITS_FONT;

	return true;
}

/* Sets a align for a textdraw */
stock tdiSetAlign(Textdraw:slotid, align)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawAlignment(playerid, PlayerText:textid, align);
	} else {
		TextDrawAlignment(Text:textid, align);
	}

	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] &= ~EI_TDW_TDI_BITS_ALIGN;
	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] |= E_TDW_TDI_BITS:(
		align << TDW_TDI_BOF_ALIGN) & EI_TDW_TDI_BITS_ALIGN;

	return true;
}

/* Sets a box color for a textdraw. */
stock tdiSetBoxColor(Textdraw:slotid, boxcolor)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawBoxColor(playerid, PlayerText:textid, boxcolor);
	} else {
		TextDrawBoxColor(Text:textid, boxcolor);
	}

	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BOX_COLOR] = boxcolor;

	return true;
}

/* Sets a background color for a textdraw. */
stock tdiSetBackgroundColor(Textdraw:slotid, bgcolor)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawBackgroundColor(playerid, PlayerText:textid, bgcolor);
	} else {
		TextDrawBackgroundColor(Text:textid, bgcolor);
	}

	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BG_COLOR] = bgcolor;

	return true;
}

/* Sets a color for a textdraw. */
stock tdiSetColor(Textdraw:slotid, color)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	new
		textid = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_ID];

	if (TDW_TDI_IS_PLAYER_TEXTDRAW(slotid)) {
		new
			playerid = TDW_TDI_GET_PLAYER_ID(slotid);

		PlayerTextDrawColor(playerid, PlayerText:textid, color);
	} else {
		TextDrawColor(Text:textid, color);
	}

	TDW_gsData[_:slotid][EI_TDW_TDI_DATA_COLOR] = color;

	return true;
}

/* Creates a new textdraw model preview */
stock Textdraw:tdiCreateModelPreview(Float:x, Float:y, modelindex,
	Float:width, Float:height, color = TDW_TDI_DEFAULT_COLOR,
	bgcolor = TDW_TDI_DEFAULT_BCOLOR, playerid = INVALID_PLAYER_ID)
{
	// find the slot where we will store the textdraw's data.
	new
		slotid = tdiGetFreeSlot(playerid);
	if (slotid == INVALID_TEXT_DRAW)
		return Textdraw:INVALID_TEXT_DRAW;

	// create a new textdraw.
	if (playerid == INVALID_PLAYER_ID) {  // global textdraw.
		new
			Text:textid = TextDrawCreate(x, y,
				TDW_gsPlaceholder);

		if (_:textid == INVALID_TEXT_DRAW)
			return Textdraw:INVALID_TEXT_DRAW;

		TextDrawFont(textid, TDW_TDI_FONT_PREVIEW_MODEL);
		TextDrawColor(textid, color);
		TextDrawTextSize(textid, width, height);

		TextDrawUseBox(textid, 1);
		TextDrawBackgroundColor(textid, bgcolor);

		TextDrawSetPreviewModel(textid, modelindex);

		TDW_gsData[slotid][EI_TDW_TDI_DATA_ID] = _:textid;
	} else {  // player textdraw.

		/* check the player's connection to the server, because
		 * CreatePlayerTextDraw returns zero when the player isn't
		 * connected (the function should return INVALID_TEXT_DRAW
		 * instead of zero)
		 */
		if (IsPlayerConnected(playerid) == 0)
			return Textdraw:INVALID_TEXT_DRAW;

		new
			PlayerText:textid = CreatePlayerTextDraw(playerid, x, y,
				TDW_gsPlaceholder);

		if (_:textid == INVALID_TEXT_DRAW)
			return Textdraw:INVALID_TEXT_DRAW;

		PlayerTextDrawFont(playerid, textid, TDW_TDI_FONT_PREVIEW_MODEL);
		PlayerTextDrawColor(playerid, textid, color);
		PlayerTextDrawTextSize(playerid, textid, width, height);

		PlayerTextDrawUseBox(playerid, textid, 1);
		PlayerTextDrawBackgroundColor(playerid, textid, bgcolor);

		PlayerTextDrawSetPreviewModel(playerid, textid, modelindex);

		TDW_gsData[slotid][EI_TDW_TDI_DATA_ID] = _:textid;
	}

	// store the passed settings in the array.
	TDW_gsData[slotid][EI_TDW_TDI_DATA_POS_X] = x;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_POS_Y] = y;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_TEXT_X] = width;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_TEXT_Y] = height;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_COLOR] = color;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_BG_COLOR] = bgcolor;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_BITS] = E_TDW_TDI_BITS:(
		((TDW_TDI_TYPE_PREVIEW_MODEL << TDW_TDI_BOF_TYPE) &
			_:EI_TDW_TDI_BITS_TYPE) |
		((TDW_TDI_FONT_PREVIEW_MODEL << TDW_TDI_BOF_FONT) &
			_:EI_TDW_TDI_BITS_FONT) |
		((1 << TDW_TDI_BOF_BOX) & _:EI_TDW_TDI_BITS_BOX)
	);

	return Textdraw:slotid;
}

/* Creates a new textdraw with sprite */
stock Textdraw:tdiCreateSprite(Float:x, Float:y, const sprite[],
	Float:width, Float:height, color = TDW_TDI_DEFAULT_COLOR,
	playerid = INVALID_PLAYER_ID)
{
	// find the slot where we will store the textdraw's data.
	new
		slotid = tdiGetFreeSlot(playerid);
	if (slotid == INVALID_TEXT_DRAW)
		return Textdraw:INVALID_TEXT_DRAW;

	// create a new textdraw.
	if (playerid == INVALID_PLAYER_ID) {  // global textdraw.
		new
			Text:textid = TextDrawCreate(x, y,
				sprite);

		if (_:textid == INVALID_TEXT_DRAW)
			return Textdraw:INVALID_TEXT_DRAW;

		TextDrawFont(textid, TDW_TDI_FONT_SPRITE_DRAW);
		TextDrawColor(textid, color);
		TextDrawTextSize(textid, width, height);

		TDW_gsData[slotid][EI_TDW_TDI_DATA_ID] = _:textid;
	} else {  // player textdraw.

		/* check the player's connection to the server, because
		 * CreatePlayerTextDraw returns zero when the player isn't
		 * connected (the function should return INVALID_TEXT_DRAW
		 * instead of zero)
		 */
		if (IsPlayerConnected(playerid) == 0)
			return Textdraw:INVALID_TEXT_DRAW;

		new
			PlayerText:textid = CreatePlayerTextDraw(playerid, x, y,
				sprite);

		if (_:textid == INVALID_TEXT_DRAW)
			return Textdraw:INVALID_TEXT_DRAW;

		PlayerTextDrawFont(playerid, textid, TDW_TDI_FONT_SPRITE_DRAW);
		PlayerTextDrawColor(playerid, textid, color);
		PlayerTextDrawTextSize(playerid, textid, width, height);

		TDW_gsData[slotid][EI_TDW_TDI_DATA_ID] = _:textid;
	}

	// store the passed settings in the array.
	TDW_gsData[slotid][EI_TDW_TDI_DATA_POS_X] = x;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_POS_Y] = y;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_TEXT_X] = width;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_TEXT_Y] = height;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_COLOR] = color;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_BITS] = E_TDW_TDI_BITS:(
		((TDW_TDI_TYPE_SPRITE_DRAW << TDW_TDI_BOF_TYPE) &
			_:EI_TDW_TDI_BITS_TYPE) |
		((TDW_TDI_FONT_SPRITE_DRAW << TDW_TDI_BOF_FONT) &
			_:EI_TDW_TDI_BITS_FONT) |
		((1 << TDW_TDI_BOF_BOX) & _:EI_TDW_TDI_BITS_BOX)
	);

	return Textdraw:slotid;
}

/* Creates a new textdraw with only box (Experimental) */
stock Textdraw:tdiCreateBox(Float:x, Float:y, Float:width, Float:height,
	bgcolor = TDW_TDI_DEFAULT_BCOLOR, playerid = INVALID_PLAYER_ID)
{
	// find the slot where we will store the textdraw's data.
	new
		slotid = tdiGetFreeSlot(playerid);
	if (slotid == INVALID_TEXT_DRAW)
		return Textdraw:INVALID_TEXT_DRAW;

	// create a new textdraw.
	if (playerid == INVALID_PLAYER_ID) {  // global textdraw.
		new
			Text:textid = TextDrawCreate(x, y,
				TDW_gsPlaceholder);

		if (_:textid == INVALID_TEXT_DRAW)
			return Textdraw:INVALID_TEXT_DRAW;

		TextDrawLetterSize(textid, 0.0, height * 0.135);
		TextDrawTextSize(textid, x + width, height);

		TextDrawUseBox(textid, 1);
		TextDrawBackgroundColor(textid, bgcolor);

		TDW_gsData[slotid][EI_TDW_TDI_DATA_ID] = _:textid;
	} else {  // player textdraw.

		/* check the player's connection to the server, because
		 * CreatePlayerTextDraw returns zero when the player isn't
		 * connected (the function should return INVALID_TEXT_DRAW
		 * instead of zero)
		 */
		if (IsPlayerConnected(playerid) == 0)
			return Textdraw:INVALID_TEXT_DRAW;

		new
			PlayerText:textid = CreatePlayerTextDraw(playerid, x, y,
				TDW_gsPlaceholder);

		if (_:textid == INVALID_TEXT_DRAW)
			return Textdraw:INVALID_TEXT_DRAW;

		PlayerTextDrawLetterSize(playerid, textid, 0.0, height * 0.135);
		PlayerTextDrawTextSize(playerid, textid, x + width, height);

		PlayerTextDrawUseBox(playerid, textid, 1);
		PlayerTextDrawBackgroundColor(playerid, textid, bgcolor);

		TDW_gsData[slotid][EI_TDW_TDI_DATA_ID] = _:textid;
	}

	// store the passed settings in the array.
	TDW_gsData[slotid][EI_TDW_TDI_DATA_POS_X] = x;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_POS_Y] = y;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_LETTER_X] = 0.0;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_LETTER_Y] = height;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_TEXT_X] = width;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_TEXT_Y] = height;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_BG_COLOR] = bgcolor;
	TDW_gsData[slotid][EI_TDW_TDI_DATA_BITS] = E_TDW_TDI_BITS:(
		((TDW_TDI_TYPE_BOX << TDW_TDI_BOF_TYPE) &
			_:EI_TDW_TDI_BITS_TYPE) |
		((1 << TDW_TDI_BOF_BOX) & _:EI_TDW_TDI_BITS_BOX)
	);

	return Textdraw:slotid;
}

/*
 * Data API functions
 */

stock bool:tdiGetPos(Textdraw:slotid, &Float:x, &Float:y)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	x = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_POS_X];
	y = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_POS_Y];

	return true;
}

stock bool:tdiGetLetterSize(Textdraw:slotid, &Float:x, &Float:y)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	x = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_LETTER_X];
	y = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_LETTER_Y];

	return true;
}

stock bool:tdiGetTextSize(Textdraw:slotid, &Float:x, &Float:y)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	x = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_TEXT_X];
	y = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_TEXT_Y];

	return true;
}

stock bool:tdiGetColor(Textdraw:slotid, &color)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	color = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_COLOR];

	return true;
}

stock bool:tdiGetBoxColor(Textdraw:slotid, &boxcolor)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	boxcolor = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BOX_COLOR];

	return true;
}

stock bool:tdiGetBackgroundColor(Textdraw:slotid, &bgcolor)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	bgcolor = TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BG_COLOR];

	return true;
}

stock bool:tdiGetShadowSize(Textdraw:slotid, &size)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	size = (TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] &
		EI_TDW_TDI_BITS_SHADOW) >>> TDW_TDI_BOF_SHADOW;

	return true;
}

stock bool:tdiGetOutlineSize(Textdraw:slotid, &size)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	size = (TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] &
		EI_TDW_TDI_BITS_OUTLINE) >>> TDW_TDI_BOF_OUTLINE;

	return true;
}

stock bool:tdiGetAlign(Textdraw:slotid, &align)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	align = (TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] &
		EI_TDW_TDI_BITS_ALIGN) >>> TDW_TDI_BOF_ALIGN;

	return true;
}

stock bool:tdiGetFont(Textdraw:slotid, &font)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	font = (TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] &
		EI_TDW_TDI_BITS_FONT) >>> TDW_TDI_BOF_FONT;

	return true;
}

stock bool:tdiGetBox(Textdraw:slotid, &use)
{
	if (_:TDW_TDI_IS_USED_TEXTDRAW(slotid) == 0)
		return false;

	use = (TDW_gsData[_:slotid][EI_TDW_TDI_DATA_BITS] &
		EI_TDW_TDI_BITS_BOX) >>> TDW_TDI_BOF_BOX;

	return true;
}
