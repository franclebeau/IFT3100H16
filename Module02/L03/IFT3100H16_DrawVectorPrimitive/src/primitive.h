// IFT3100H16_DrawVectorPrimitives/primitive.h
// Définition de nouveaux types primitifs.

#pragma once

// énumération des différents types de primitives vectorielles
typedef enum
{
	VECTOR_PRIMITIVE_NONE,
	VECTOR_PRIMITIVE_PIXEL,
	VECTOR_PRIMITIVE_POINT,
	VECTOR_PRIMITIVE_LINE,
	VECTOR_PRIMITIVE_RECTANGLE,
	VECTOR_PRIMITIVE_ELLIPSE,
}   EnumVectorDrawMode;

// stucture de primitive vectorielle générique
typedef struct
{
	EnumVectorDrawMode type;             	// 1 * 4 = 4  octets
	float              position1    [2];	// 2 * 4 = 8  octets
	float              position2    [2];	// 2 * 4 = 8  octets
	float              strokeWidth;	        // 1 * 4 = 4  octets
	unsigned char      strokeColor	[4];	// 4 * 1 = 4  octets
	unsigned char      fillColor	[4];    // 4 * 1 = 4  octets
}   StructVectorPrimitive;                  //       = 32 octets
