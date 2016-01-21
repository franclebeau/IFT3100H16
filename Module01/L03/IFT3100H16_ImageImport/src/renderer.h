// IFT3100H16_ImageImport/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

	ofImage * image;

	Renderer();
	
	void setup();
	void draw();
	
	void imageImport(const string fileName, ofImage * & imageDestination);
	
	~Renderer();
};