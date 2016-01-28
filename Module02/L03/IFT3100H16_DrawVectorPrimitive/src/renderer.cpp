// IFT3100H16_DrawVectorPrimitives/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer(){}

void Renderer::setup()
{
	ofSetFrameRate(60);

	ofSetWindowShape(512, 512);

	// nombre maximale de primitives vectorielles dans le tableau
	count = 100;

	// calculer la taille de la structure générique commune à toutes les primitives vectorielles
	stride = sizeof(StructVectorPrimitive);

	// calculer le nombre d'octets à allouer pour un tableau contenant toutes les primitives vectorielles
	size = count * stride;

	// allouer un espace mémoire de taille suffisante pour contenir les données de l'ensemble des primitives vectorielles
	shape = (StructVectorPrimitive *) calloc(size, stride);

	// mode de dessin par défaut
	drawMode = VECTOR_PRIMITIVE_POINT;

	// position de la prochaine primitive
	head = 0;

	// largeur de la ligne de contour
	strokeWidthDefault = 2;

	// couleur de la ligne de contour
	randomColorStroke();

	// couleur de la zone de remplissage
	randomColorFill();

	xMousePress   = yMousePress   = 0;
	xMouseCurrent = yMouseCurrent = 0;

	isMouseButtonPressed = false;

	isVerbose = false;
}

void Renderer::draw()
{
	ofClear(191);

	for(index = 0; index < count; ++index)
	{
		switch(shape[index].type)
		{
			case VECTOR_PRIMITIVE_PIXEL:

				ofFill();
				ofSetLineWidth(0);
				ofSetColor(
					shape[index].strokeColor[0],
					shape[index].strokeColor[1],
					shape[index].strokeColor[2]);
				drawPixel(
					shape[index].position2[0],
					shape[index].position2[1]);
				break;

			case VECTOR_PRIMITIVE_POINT:

				ofFill();
				ofSetLineWidth(0);
				ofSetColor(
					shape[index].strokeColor[0],
					shape[index].strokeColor[1],
					shape[index].strokeColor[2]);
				drawPoint(
					shape[index].position2[0],
					shape[index].position2[1],
					shape[index].strokeWidth);
				break;

			case VECTOR_PRIMITIVE_LINE:

				ofNoFill();
				ofSetLineWidth(shape[index].strokeWidth);
				ofSetColor(
					shape[index].strokeColor[0],
					shape[index].strokeColor[1],
					shape[index].strokeColor[2]);
				drawLine(
					shape[index].position1[0],
					shape[index].position1[1],
					shape[index].position2[0],
					shape[index].position2[1]);
				break;

			case VECTOR_PRIMITIVE_RECTANGLE:

				ofFill();
				ofSetLineWidth(0);
				ofSetColor(
					shape[index].fillColor[0],
					shape[index].fillColor[1],
					shape[index].fillColor[2]);
				drawRectangle(
					shape[index].position1[0],
					shape[index].position1[1],
					shape[index].position2[0],
					shape[index].position2[1]);
				ofNoFill();
				ofSetLineWidth(shape[index].strokeWidth);
				ofSetColor(
					shape[index].strokeColor[0],
					shape[index].strokeColor[1],
					shape[index].strokeColor[2]);
				drawRectangle(
					shape[index].position1[0],
					shape[index].position1[1],
					shape[index].position2[0],
					shape[index].position2[1]);
				break;

			case VECTOR_PRIMITIVE_ELLIPSE:

				ofFill();
				ofSetLineWidth(0);
				ofSetCircleResolution(48);
				ofSetColor(
					shape[index].fillColor[0],
					shape[index].fillColor[1],
					shape[index].fillColor[2]);
				drawEllipse(
					shape[index].position1[0],
					shape[index].position1[1],
					shape[index].position2[0],
					shape[index].position2[1]);
				ofNoFill();
				ofSetLineWidth(shape[index].strokeWidth);
				ofSetColor(
					shape[index].strokeColor[0],
					shape[index].strokeColor[1],
					shape[index].strokeColor[2]);
				drawEllipse(
					shape[index].position1[0],
					shape[index].position1[1],
					shape[index].position2[0],
					shape[index].position2[1]);
				break;

			default:
				break;
		}
	}

	// afficher la zone de sélection
	if(isMouseButtonPressed)
	{
		ofSetColor(255);
		ofSetLineWidth(3);
		ofNoFill();

		drawRectangle(
			xMousePress,
			yMousePress,
			min(max(0, xMouseCurrent), ofGetWidth()),
			min(max(0, yMouseCurrent), ofGetHeight()));
	}

	// afficher le curseur
	ofSetLineWidth(2);
	ofSetColor(32);

	drawCursor(xMouseCurrent, yMouseCurrent);
}

// fonction qui vide le tableau de primitives vectorielles
void Renderer::reset()
{
	for(index = 0; index < count; ++index)
		shape[index].type = VECTOR_PRIMITIVE_NONE;

	head = 0;

	ofLog() << "<reset>";
}

// fonction qui ajoute une primitive vectorielle au tableau
void Renderer::addVectorShape(EnumVectorDrawMode type)
{
	shape[head].type = type;

	shape[head].position1[0] = xMousePress;
	shape[head].position1[1] = yMousePress;

	shape[head].position2[0] = xMouseCurrent;
	shape[head].position2[1] = yMouseCurrent;

	shape[head].strokeColor[0] = strokeColorR;
	shape[head].strokeColor[1] = strokeColorG;
	shape[head].strokeColor[2] = strokeColorB;
	shape[head].strokeColor[3] = strokeColorA;

	shape[head].fillColor[0] = fillColorR;
	shape[head].fillColor[1] = fillColorG;
	shape[head].fillColor[2] = fillColorB;
	shape[head].fillColor[3] = fillColorA;

	switch(shape[head].type)
	{
		case VECTOR_PRIMITIVE_POINT:
			shape[head].strokeWidth = ofRandom(1,64);
			break;
		case VECTOR_PRIMITIVE_LINE:
			shape[head].strokeWidth = ofRandom(1,16);
			break;
		case VECTOR_PRIMITIVE_RECTANGLE:
			shape[head].strokeWidth = strokeWidthDefault;
			break;
		case VECTOR_PRIMITIVE_ELLIPSE:
			shape[head].strokeWidth = strokeWidthDefault;
			break;
		default:
			shape[head].strokeWidth = strokeWidthDefault;
			break;
	}

	head = ++head >= count ? 0: head; // boucler sur le tableau

	ofLog() << "<add primitive to shape at: " << head << ">";
}

// fonction qui dessine un pixel
void Renderer::drawPixel(float x, float y) const
{
	int xPixel = floorf(x);
	int yPixel = floorf(y);

	ofDrawRectangle(xPixel, yPixel, 1, 1);

	if(isVerbose)
		ofLog() << "<draw pixel at: (" << xPixel << ", " << yPixel << ")>";
}

// fonction qui dessine un point
void Renderer::drawPoint(float x, float y, float radius) const
{
	ofDrawEllipse(x, y, radius, radius);

	if(isVerbose)
		ofLog() << "<draw point at: (" << x << ", " << y <<  ", " << radius << ")>";
}

// fonction qui dessine une ligne
void Renderer::drawLine(float x1, float y1, float x2, float y2) const
{
	ofDrawLine(x1, y1, x2, y2);

	if(isVerbose)
		ofLog() << "<draw line between: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")>";
}

// fonction qui dessine un rectangle
void Renderer::drawRectangle(float x1, float y1, float x2, float y2) const
{
	ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);

	if(isVerbose)
		ofLog() << "<draw rectangle between: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")>";
}

// fonction qui dessine une ellipse
void Renderer::drawEllipse(float x1, float y1, float x2, float y2) const
{
	float xDiameter = x2 - x1;
	float yDiameter = y2 - y1;

	ofDrawEllipse(x1 + xDiameter/2.0f, y1 + yDiameter/2.0f, xDiameter, yDiameter);

	if(isVerbose)
		ofLog() << "<draw ellipse between: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")>";
}

// fonction qui détermine une couleur aléatoire pour les lignes de contour
void Renderer::randomColorStroke()
{
	strokeColorR = (int) ofRandom(0, 256);
	strokeColorG = (int) ofRandom(0, 256);
	strokeColorB = (int) ofRandom(0, 256);
	strokeColorA = 255;

	ofLog() << "<random color stroke>";
}

// fonction qui détermine une couleur aléatoire pour les zones de remplissage
void Renderer::randomColorFill()
{
	fillColorR = (int) ofRandom(0, 256);
	fillColorG = (int) ofRandom(0, 256);
	fillColorB = (int) ofRandom(0, 256);
	fillColorA = 255;

	ofLog() << "<random color fill>";
}

void Renderer::drawZone(float x1, float y1, float x2, float y2) const
{
	float x2Clamp = min(max(0.0f, x2), (float) ofGetWidth());
	float y2Clamp = min(max(0.0f, y2), (float) ofGetHeight());

	ofDrawRectangle(x1, y1, x2Clamp - x1, y2Clamp - y1);
}

void Renderer::drawCursor(float x, float y) const
{
	float length = 10;
	float offset = 5;

	ofDrawLine(x + offset, y, x + offset + length, y);
	ofDrawLine(x - offset, y, x - offset - length, y);
	ofDrawLine(x, y + offset, x, y + offset + length);
	ofDrawLine(x, y - offset, x, y - offset - length);
}

void Renderer::imageExport(const string name, const string extension) const
{
	ofImage imageTemp;

	string timestamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

	string fileName = name + timestamp + "." + extension;

	imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	imageTemp.save(fileName);

	ofLog() << "<export image: " << fileName << ">";
}

Renderer::~Renderer()
{
	free(shape);
}
