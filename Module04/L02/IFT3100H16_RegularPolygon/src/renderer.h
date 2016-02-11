// IFT3100H16_RegularPolygon/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{

public:

	float xPolygonCenter;
	float yPolygonCenter;

	float xPositionVertex;
	float yPositionVertex;

	float angle;
	float offset;
	float radius;

	float pointDiameter;

	int side;

	int index;

	Renderer();

	void setup();

	void update();

	void draw();

	void reset();

	void imageExport(const string name, const string extension) const;

	~Renderer();
};

/*


int sideMin = 3;
int countPolygon = 12;

int side = sideMin;

int indexPolygon;
int indexVertex;

float angle  = 0;
float offset = 0;

float xPosition = 0;
float yPosition = 0;

float xPolygon = 0;
float yPolygon = 0;

float diameter = width  / countPolygon;
float radius   = height / 3.0;

// une itération de la boucle pour chaque polygone
for(indexPolygon = 0; indexPolygon < countPolygon; indexPolygon++)
{
	// calculer l'angle qui sépare chaque sommet du polygone
	offset = radians(360.0 / side);

	// calculer la position du centre du polygone
	xPolygon = radius + indexPolygon * diameter;
	yPolygon = height / 2.0;

	// débuter une nouvelle forme vectorielle
	beginShape();

	// une itération pour chaque sommet du polygone
	for(indexVertex = 0; indexVertex < side; indexVertex++)
	{
		// calculer la position du sommet
		xPosition = xPolygon + cos(angle) * radius;
		yPosition = yPolygon + sin(angle) * radius;

		// ajouter un sommet à la forme vectorielle
		vertex(xPosition, yPosition);

		// incrémenter l'angle pour le prochain sommet
		angle += offset;
	}

	// terminer et rendre la forme vectorielle
	endShape(CLOSE);

	// incrémenter l'index de l'itérateur
	side++;
}

saveFrame("render.png");

*/
