// IFT3100H16_Empty/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

// constructeur de la classe
ofApp::ofApp()
{
	renderer = nullptr;
}

// fonction invoquée à l'initialisation de l'application
void ofApp::setup()
{
	ofSetWindowTitle("empty project");
	
	renderer = new Renderer();
	renderer->setup();
	
	ofLog() << "<ofApp::setup>";
}

// fonction invoquée lors d'une mise à jour de la logique de l'application
void ofApp::update()
{
	renderer->update();
}

// fonction invoquée lors d'une mise à jour du rendu de la fenêtre de l'application
void ofApp::draw()
{
	renderer->draw();
}

// fonction invoquée quand l'application quitte
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
