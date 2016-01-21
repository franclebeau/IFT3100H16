// IFT3100H16_Empty/ofApp.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"

#include "Renderer.h"

class ofApp : public ofBaseApp
{
public:

	Renderer * renderer;

	ofApp();

	void setup();
	void update();
	void draw();
	void exit();

	~ofApp();
};
