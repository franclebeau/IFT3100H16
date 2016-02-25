// IFT3100H16_LightingFixedPipeline/ofApp.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"

#include "renderer.h"
#include "function.h"

class ofApp : public ofBaseApp
{
public:

	Renderer * renderer;

	float timeCurrent;
	float timeLast;
	float timeElapsed;

	bool isKeyPressUp;
	bool isKeyPressDown;
	bool isKeyPressLeft;
	bool isKeyPressRight;

	bool isVerbose;

	ofApp();

	void setup();

	void update();

	void draw();

	void keyPressed(int key);

	void keyReleased(int key);

	void mouseReleased(int x, int y, int button);

	void windowResized(int w, int h);

	void exit();

	~ofApp();
};