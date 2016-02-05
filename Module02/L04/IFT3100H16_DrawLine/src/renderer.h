// IFT3100H16_DrawLine/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

#include "primitive.h"

class Renderer
{

public:

	EnumLineRasterMode lineRasterMode;

	StructFatPixel * fatPixels;

	int fatPixelResolution;

	int fatPixelGridWidth;
	int fatPixelGridHeight;

	int bufferCount;
	int bufferSize;
	int bufferStride;

	int xMousePress;
	int yMousePress;

	int xMouseCurrent;
	int yMouseCurrent;

	int framebufferWidth;

	int framebufferHeight;

	int index;

	float strokeWidthDefault;

	unsigned char strokeColorOnR;
	unsigned char strokeColorOnG;
	unsigned char strokeColorOnB;
	unsigned char strokeColorOnA;

   	unsigned char strokeColorOffR;
    unsigned char strokeColorOffG;
    unsigned char strokeColorOffB;
    unsigned char strokeColorOffA;

	unsigned char strokeColorPreviewR;
	unsigned char strokeColorPreviewG;
	unsigned char strokeColorPreviewB;
	unsigned char strokeColorPreviewA;

	bool isMouseButtonPressed;

	bool isVerbose;

	Renderer();

	void setup();
	
	void draw();

	void reset();

	void fatPixelStateChange(int index, int state);

	bool isInside(int x, int y, int x1, int y1, int x2, int y2) const;

	int findIndexOfFatPixelByCoord(int x, int y) const;

	int findIndexOfFatPixelByPosition(int x, int y) const;

	void rasterLineDDA(float x1, float y1, float x2, float y2);

	void rasterLineBresenham(float x1, float y1, float x2, float y2);

	void drawFatPixel(float x, float y, float diameter) const;

	void drawGrid(int cellSize) const;
	
	void drawLine(float x1, float y1, float x2, float y2) const;

	void drawRectangle(float x1, float y1, float x2, float y2) const;

	void drawZone(float x1, float y1, float x2, float y2) const;

	void drawCursor(float x, float y) const;

	void imageExport(const string name, const string extension) const;

	~Renderer();
};
