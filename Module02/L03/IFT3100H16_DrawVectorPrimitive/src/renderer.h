// IFT3100H16_DrawVectorPrimitives/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

#include "primitive.h"

class Renderer
{

public:

	EnumVectorDrawMode drawMode;

	StructVectorPrimitive * shape;

	int count;
	int size;
	int stride;

	int index;
	int head;

	int xMousePress;
	int yMousePress;

	int xMouseCurrent;
	int yMouseCurrent;

	float strokeWidthDefault;

	unsigned char strokeColorR;
	unsigned char strokeColorG;
	unsigned char strokeColorB;
	unsigned char strokeColorA;

	unsigned char fillColorR;
	unsigned char fillColorG;
	unsigned char fillColorB;
	unsigned char fillColorA;

	bool isMouseButtonPressed;

	bool isVerbose;

	Renderer();

	void setup();
	void draw();

	void reset();

	void addVectorShape(EnumVectorDrawMode type);

	void drawPixel(float x, float y) const;
	void drawPoint(float x, float y, float radius) const;
	void drawLine(float x1, float y1, float x2, float y2) const;
	void drawRectangle(float x1, float y1, float x2, float y2) const;
	void drawEllipse(float x1, float y1, float x2, float y2) const;

	void randomColorStroke();
	void randomColorFill();

	void drawZone(float x1, float y1, float x2, float y2) const;
	void drawCursor(float x, float y) const;

	void imageExport(const string name, const string extension) const;

	~Renderer();
};
