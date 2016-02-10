// IFT3100H16_DrawLine/primitive.h
// Définition de nouveaux types primitifs.

#pragma once

// énumération de différents états que peut avoir un gros pixel
typedef enum
{
	FAT_PIXEL_STATE_NONE,
	FAT_PIXEL_STATE_ON,
	FAT_PIXEL_STATE_OFF,
	FAT_PIXEL_STATE_START,
	FAT_PIXEL_STATE_END,
	FAT_PIXEL_STATE_PREVIEW
}   EnumPixelState;

// énumération de différents types d'algorithme de rastérisation de ligne
typedef enum
{
	LINE_RASTERIZER_NONE,
	LINE_RASTERIZER_DDA,
	LINE_RASTERIZER_BRESENHAM,
	LINE_RASTERIZER_XIAOLIN_WU,
	LINE_RASTERIZER_PO_HAN_LIN
}   EnumLineRasterMode;

// structure de primitive vectorielle générique
typedef struct
{
	int             state;        // 1 * 4 = 4  octets
	float           position [2]; // 2 * 4 = 8  octets
	unsigned char   color    [4]; // 4 * 1 = 4  octets
}   StructFatPixel;               //       = 16 octets
