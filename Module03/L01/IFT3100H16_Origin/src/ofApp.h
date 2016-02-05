// IFT3100H16_Origin/ofApp.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"

#include "renderer.h"

class ofApp : public ofBaseApp
{
public:

	Renderer * renderer;

	bool isVerbose;

	ofApp();

	void setup();
	
	void draw();

	void keyReleased(int key);

	void mouseReleased(int x, int y, int button);

	void exit();

	~ofApp();
};
