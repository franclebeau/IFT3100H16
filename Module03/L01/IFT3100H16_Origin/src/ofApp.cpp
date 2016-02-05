// IFT3100H16_Origin/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	ofLog() << "<ofApp::setup>";

	ofSetWindowTitle("origine");

	renderer = new Renderer();
	renderer->setup();

	isVerbose = false;
}

void ofApp::draw()
{
	renderer->draw();
}

void ofApp::mouseReleased(int x, int y, int button)
{
	renderer->reset();

	if(isVerbose)
		ofLog() << "<ofApp::mouse release at: (" << x << ", " << y << ")>";
}

void ofApp::keyReleased(int key)
{
	switch(key)
	{
		case ' ': // space
			renderer->imageExport("render","png");
			break;
		default:
			renderer->reset();
			break;
	}
	if(isVerbose)
		ofLog() << "<ofApp::keyReleased: " << key << ">";
}

void ofApp::exit()
{
	ofLog() << "<ofApp::exit>";
}

ofApp::~ofApp()
{
	if(nullptr != renderer)
		delete renderer;
}
