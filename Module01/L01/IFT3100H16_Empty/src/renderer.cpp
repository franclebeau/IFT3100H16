// IFT3100H16_Empty/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

// constructeur de la classe
Renderer::Renderer(){}

// fonction d'initialisation
void Renderer::setup()
{
	// fréquence de rafraichissement du rendu par seconde
	ofSetFrameRate(60);
}

// fonction de mise à jour
void Renderer::update()
{
	// temps courant en secondes
	timeCurrent = ofGetElapsedTimef();

	// le temps écoulé depuis le dernier frame en secondes
	timeElapsed = timeCurrent - timeLast;

	// le temps courant sera le temps précédent du prochain frame
	timeLast = timeCurrent;

	ofLog() << std::setprecision(2) << "<frame: " << ofGetFrameNum() << " time current: " << timeCurrent << " time elapsed: " << timeElapsed << ">";
}

// fonction de rendu
void Renderer::draw()
{
	// couleur d'arrière-plan en tons de gris en fonction du frame courant.
	ofClear(ofGetFrameNum() % 255);
}

// destructeur de la classe
Renderer::~Renderer(){}
