// IFT3100H16_ClearScreen/primitive.h
// Définition de nouveaux types primitifs.

#pragma once

// énumération des différents modes pour effacer un framebuffer
typedef enum
{
	CLEAR_MODE_NONE,
	CLEAR_MODE_DEFAULT,
	CLEAR_MODE_BLACK,
	CLEAR_MODE_WHITE,
	CLEAR_MODE_GRAYSCALE,
	CLEAR_MODE_COLOR,
	CLEAR_MODE_RANDOM
}   EnumClearMode;
