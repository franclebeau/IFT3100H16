// IFT3100H16_EquilateralTriangle/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{

public:

	float xViewportCenter;
	float yViewportCenter;

	float xTriangleCenter;
	float yTriangleCenter;

	float xTriangleOrigin;
	float yTriangleOrigin;

	float xVertex1;
	float yVertex1;

	float xVertex2;
	float yVertex2;

	float xVertex3;
	float yVertex3;

	float edgeDiameterHalf;
	float edgeDiameter;

	float radiusInnercircle;
	float radiusCircumcircle;

	float triangleAltitude;
	float trianglePerimeter;
	float triangleArea;

	float pointDiameter;

	Renderer();

	void setup();

	void update();

	void draw();

	void reset();

	void imageExport(const string name, const string extension) const;

	~Renderer();
};
