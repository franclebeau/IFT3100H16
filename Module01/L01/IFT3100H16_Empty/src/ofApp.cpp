// IFT3100H16_Empty/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

// constructeur de la classe
ofApp::ofApp()
{
	renderer = nullptr;
}

// fonction invoqu�e � l'initialisation de l'application
void ofApp::setup()
{
	ofSetWindowTitle("empty project");
	
	renderer = new Renderer();
	renderer->setup();
	
	ofLog() << "<ofApp::setup>";
}

// fonction invoqu�e lors d'une mise � jour de la logique de l'application
void ofApp::update()
{
	renderer->update();
}

// fonction invoqu�e lors d'une mise � jour du rendu de la fen�tre de l'application
void ofApp::draw()
{
	renderer->draw();
}

// fonction invoqu�e quand l'application quitte
void ofApp::exit()
{
	ofLog() << "<ofApp::exit>";
}

// destructeur de la classe
ofApp::~ofApp()
{
	if(nullptr != renderer)
		delete renderer;
}
