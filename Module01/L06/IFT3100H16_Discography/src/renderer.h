// IFT3100H16_Discography/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{

public:

	ofImage * imageTopLeft;
	ofImage * imageTopCenter;
	ofImage * imageTopRight;

	ofImage * imageMiddleLeft;
	ofImage * imageMiddleCenter;
	ofImage * imageMiddleRight;

	ofImage * imageBottomLeft;
	ofImage * imageBottomCenter;
	ofImage * imageBottomRight;

	int imageWidth;
	int imageHeight;

	int offsetVertical;
	int offsetHorizontal;

	Renderer();

	void setup();
	void draw();

	void imageImport(const string fileName, ofImage * & imageDestination);

	void imageExport(const string name, const string extension) const;

	~Renderer();
};

