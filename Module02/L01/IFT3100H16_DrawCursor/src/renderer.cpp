// IFT3100H16_DrawCursor/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer(){}

void Renderer::setup()
{
	ofSetFrameRate(60);

	ofSetWindowShape(512, 512);

	xMousePress   = yMousePress   = 0;
	xMouseCurrent = yMouseCurrent = 0;

	isMouseButtonPressed = false;

	isVerbose = false;
}

void Renderer::draw()
{
	ofClear(191);

	ofSetLineWidth(2);
	ofSetColor(32);

	// afficher le curseur
	drawCursor(xMouseCurrent, yMouseCurrent);
}

// fonction qui dessine un curseur
void Renderer::drawCursor(float x, float y) const
{
	float length = 10;
	float offset = 5;

	ofDrawLine(x + offset, y, x + offset + length, y);
	ofDrawLine(x - offset, y, x - offset - length, y);
	ofDrawLine(x, y + offset, x, y + offset + length);
	ofDrawLine(x, y - offset, x, y - offset - length);
}

void Renderer::imageExport(const string name, const string extension) const
{
	ofImage imageTemp;

	string timestamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

	string fileName = name + timestamp + "." + extension;

	imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	imageTemp.save(fileName);

	ofLog() << "<export image: " << fileName << ">";
}

Renderer::~Renderer(){}
