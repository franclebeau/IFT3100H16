// IFT3100H16_Move/ofApp.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"

#include "renderer.h"

class ofApp : public ofBaseApp
{
public:

	Renderer * renderer;

	float timeCurrent;
	float timeLast;
	float timeElapsed;

	bool isVerbose;

	bool isKeyPressUp;
	bool isKeyPressDown;
	bool isKeyPressLeft;
	bool isKeyPressRight;

	ofApp();

	void setup();

	void update();

	void draw();

	void keyPressed(int key);

	void keyReleased(int key);

	void mouseReleased(int x, int y, int button);

	void exit();

	~ofApp();
};
