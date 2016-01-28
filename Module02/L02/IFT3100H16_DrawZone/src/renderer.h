// IFT3100H16_DrawZone/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{

public:

	int xMousePress;
	int yMousePress;

	int xMouseCurrent;
	int yMouseCurrent;

	bool isMouseButtonPressed;

	bool isVerbose;

	Renderer();

	void setup();
	void draw();

	void reset();

	void drawZone(float x1, float y1, float x2, float y2) const;

	void drawCursor(float x, float y) const;

	void imageExport(const string name, const string extension) const;

	~Renderer();
};
