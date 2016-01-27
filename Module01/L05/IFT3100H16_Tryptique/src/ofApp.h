// IFT3100H16_Tryptique/ofApp.cpp
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
	void draw();
	
	void keyReleased(int key);
	
	void windowResized(int w, int h);
	
	void exit();

	~ofApp();
};
