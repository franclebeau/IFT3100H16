// IFT3100H16_Empty/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

	float timeCurrent;
	float timeLast;
	float timeElapsed;

	Renderer();
	
	void setup();
	void update();
	void draw();
	
	~Renderer();
};