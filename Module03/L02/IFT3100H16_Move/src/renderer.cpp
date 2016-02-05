// IFT3100H16_Move/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer(){}

void Renderer::setup()
{
	ofSetFrameRate(60);

	speed = 100;

	xDelta = speed;
	zDelta = speed;

	isVerbose = false;

	node = new ofNode();

	reset();
}

void Renderer::draw()
{
	ofClear(63);

	drawScene();
}

void Renderer::reset()
{
	xOffset = 0;
	zOffset = 0;

	framebufferWidth  = ofGetWidth();
	framebufferHeight = ofGetHeight();

	xCenter = framebufferWidth  /2.0f;
	yCenter = framebufferHeight /2.0f;

	ofLog() << "<reset>";
}

void Renderer::drawScene()
{
	// configurer la représentation visuelle des localisateurs
	ofFill();
	ofSetLineWidth(2);
	ofSetColor(127);

	// copier la matrice de transformation courante sur le dessus de la pile
	ofPushMatrix();

	// transformer l'origine de la scène en fonction du mouvement par rapport au milieu de la fenêtre d'affichage
	ofTranslate(xCenter + xOffset, yCenter, zOffset);

	// dessiner l'origine de la scène
	drawLocator(10);

	// revenir à la matrice de transformation précédente dans la pile
	ofPopMatrix();
}

void Renderer::drawLocator(float scale)
{
	ofFill();
	ofPushMatrix();
	ofScale(scale, scale);
	node->setPosition(0, 0, 0);
	node->draw();
	ofPopMatrix();
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
	delete node;
}
