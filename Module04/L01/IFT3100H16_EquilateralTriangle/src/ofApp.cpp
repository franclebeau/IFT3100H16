// IFT3100H16_EquilateralTriangle/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	ofSetWindowTitle("triangle équilatéral");

	ofLog() << "<ofApp::setup>";

	renderer = new Renderer();
	renderer->setup();
}

void ofApp::update()
{
	renderer->update();
}

void ofApp::draw()
{
	renderer->draw();
}

void ofApp::exit()
{
	ofLog() << "<ofApp::exit>";
}

void ofApp::keyReleased(int key)
{
	if(key == ' ')
		renderer->imageExport("render","png");
}

ofApp::~ofApp()
{
	if(nullptr != renderer)
		delete renderer;
}