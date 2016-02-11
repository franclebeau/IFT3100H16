// IFT3100H16_Teapot/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

#include "primitive.h"

class Renderer
{

public:

	StructLocator * locators;

	ofNode * node;

	ofVec3f * vectorPosition;
	ofVec3f * vectorRotation;
	ofVec3f * vectorDimension;

	ofxAssimpModelLoader * teapot;

	ofLight * light;

	float xCenter;
	float yCenter;

	float speed;
	float xOffset;
	float zOffset;

	float xDelta;
	float zDelta;

	int locatorCount;

	int locatorBufferSize;
	int locatorBufferHead;

	int index;

	int framebufferWidth;
	int framebufferHeight;

	bool isFlipAxisY;

	bool isActiveTranslation;
	bool isActiveRotation;
	bool isActiveDimension;

	bool isVerbose;

	Renderer();

	void setup();
	void draw();

	void reset();

	void dispatchRandomLocator(int count, float range);

	void drawScene();

	void drawLocator(float scale);

	void imageExport(const string name, const string extension) const;

	~Renderer();
};
