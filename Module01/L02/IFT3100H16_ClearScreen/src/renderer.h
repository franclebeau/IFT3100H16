// IFT3100H16_ClearScreen/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

#include "primitive.h"

class Renderer
{
public:

	EnumClearMode clearMode;

	int clearColorGray;

	int clearColorRed;
	int clearColorGreen;
	int clearColorBlue;

	bool hasChanged;

	Renderer();

	void setup();
	void draw();

	void clear() const;
	void clearToBlack() const;
	void clearToWhite() const;
	void clearToGrayscale(int g);
	void clearToColor(int r, int g, int b);
	void clearToRandom();

	~Renderer();
};