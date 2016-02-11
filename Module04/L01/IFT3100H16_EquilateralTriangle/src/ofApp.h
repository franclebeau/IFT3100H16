// IFT3100H16_EquilateralTriangle/ofApp.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"

#include "renderer.h"

class ofApp : public ofBaseApp
{
public:

	Renderer * renderer;

	ofApp();

	void setup();

	void update();

	void draw();

	void exit();

	void keyReleased(int key);

	~ofApp();
};