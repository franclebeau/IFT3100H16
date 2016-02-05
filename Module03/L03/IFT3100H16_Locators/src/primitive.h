// IFT3100H16_Locator/primitive.h
// Définition de nouveaux types primitifs.

#pragma once

// stucture d'un localisateur de transformation
typedef struct
{
	int   state;         // 1 * 4 = 4  octets
	float position  [3]; // 3 * 4 = 12 octets
	float rotation  [3]; // 3 * 4 = 12 octets
	float dimension [3]; // 3 * 4 = 12 octets
}   StructLocator;       //       = 40 octets
