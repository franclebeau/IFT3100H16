// IFT3100H16_DrawZone/renderer.cpp
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

	// afficher la zone de sélection
	if(isMouseButtonPressed)
	{
		ofSetColor(255);
		ofSetLineWidth(3);
		ofNoFill();

		drawZone(
			xMousePress,
			yMousePress,
			xMouseCurrent,
			yMouseCurrent);
	}

	// afficher le curseur
	ofSetLineWidth(2);
	ofSetColor(32);

	drawCursor(xMouseCurrent, yMouseCurrent);
}

// fonction qui dessine une zone rectangulaire
void Renderer::drawZone(float x1, float y1, float x2, float y2) const
{
	float x2Clamp = min(max(0.0f, x2), (float) ofGetWidth());
	float y2Clamp = min(max(0.0f, y2), (float) ofGetHeight());

	ofDrawRectangle(x1, y1, x2Clamp - x1, y2Clamp - y1);
}

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
