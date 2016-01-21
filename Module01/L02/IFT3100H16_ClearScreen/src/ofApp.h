// IFT3100H16_ClearScreen/ofApp.h
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
	void draw();

	void keyReleased(int key);

	void exit();

	~ofApp();
};
