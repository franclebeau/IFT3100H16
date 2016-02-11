// IFT3100H16_TriangleSoup/primitive.h
// Définition de nouveaux types primitifs.

#pragma once

// structure d'un localisateur de transformation
typedef struct
{
	int   state;         // 1 * 4 = 4  octets
	float position  [3]; // 3 * 4 = 12 octets
	float rotation  [3]; // 3 * 4 = 12 octets
	float dimension [3]; // 3 * 4 = 12 octets
}   StructLocator;       //       = 40 octets


// structure d'un triangle
typedef struct
{
	int           state;         // 1 * 4 = 4  octets
	float         position1 [3]; // 3 * 4 = 12 octets
	float         position2 [3]; // 3 * 4 = 12 octets
	float         position3 [3]; // 3 * 4 = 12 octets
	unsigned char color     [4]; // 4 * 1 = 4  octets
}   StructTriangle;              //       = 44 octets


