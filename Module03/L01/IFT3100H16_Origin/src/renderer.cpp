// IFT3100H16_Origin/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer(){}

void Renderer::setup()
{
	ofSetFrameRate(60);

	// allocation d'une instance de ofNode pour l'affichage du localisateur
	node = new ofNode();

	isVerbose = false;

	// initialisation de la scène
	reset();
}

void Renderer::draw()
{
	ofClear(63);

	ofSetLineWidth(4);
	ofSetColor(127);

	drawScene();
}

// fonction qui initialise la scène
void Renderer::reset()
{
	// extraire la résolution du framebuffer
	framebufferWidth  = ofGetWidth();
	framebufferHeight = ofGetHeight();

	// calculer les coordonnées du centre du framebuffer
	xCenter = framebufferWidth  / 2.0f;
	yCenter = framebufferHeight / 2.0f;

	ofLog() << "<reset>";
}

// fonction fait le rendu des entités géométriques de la scène
void Renderer::drawScene()
{
	// rendre l'origine de la scène avant transformation du système de coordonnées
	drawLocator(10);

	// copier la matrice de transformation courante sur le dessus de la pile
	ofPushMatrix();

	// transformer l'origine de la scène au milieu de la fenêtre d'affichage
	ofTranslate(xCenter, yCenter, 0);

	// rendre l'origine de la scène après transformation du système de coordonnées
	drawLocator(10);

	// revenir à la matrice de transformation précédente dans la pile
	ofPopMatrix();
}

// fonction qui dessine un localisateur à l'origine de la scène
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