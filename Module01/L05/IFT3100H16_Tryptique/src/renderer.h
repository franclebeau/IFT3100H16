// IFT3100H16_Tryptique/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{

public:

	ofImage * imageSource;

	ofImage * imageLeft;
	ofImage * imageCenter;
	ofImage * imageRight;

	int imageWidth;
	int imageHeight;

	int offsetVertical;
	int offsetHorizontal;

	Renderer();

	void setup();
	void draw();

	void imageImport(const string fileName, ofImage * & imageDestination);

	void imageExport(const string name, const string extension) const;

	void imageCopy(ofImage * source, ofImage * & destination, int x, int y, int w, int h);

	~Renderer();
};