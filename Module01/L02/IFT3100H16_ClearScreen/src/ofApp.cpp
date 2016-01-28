// IFT3100H16_ClearScreen/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	ofSetWindowTitle("clear screen (key: 1-6)");

	ofLog() << "<ofApp::setup>";

	renderer = new Renderer();
	renderer->setup();
}

void ofApp::draw()
{
	renderer->draw();
}

// fonction invoquée quand une touche du clavier est relâchée
void ofApp::keyReleased(int key)
{
	ofLog() << "<ofApp::keyReleased: " << key << ">";
	
	switch(key)
	{
	case 49: // key 1
		renderer->clearMode = CLEAR_MODE_DEFAULT;
		ofLog() << "<clear mode: DEFAULT>";
		break;
	case 50: // key 2
		renderer->clearMode = CLEAR_MODE_BLACK;
		ofLog() << "<clear mode: BLACK>";
		break;
	case 51: // key 3
		renderer->clearMode = CLEAR_MODE_WHITE;
		ofLog() << "<clear mode: WHITE>";
		break;
	case 52: // key 4
		renderer->clearMode = CLEAR_MODE_GRAYSCALE;
		ofLog() << "<clear mode: GRAYSCALE>";
		break;
	case 53: // key 5
		renderer->clearMode = CLEAR_MODE_COLOR;
		ofLog() << "<clear mode: COLOR>";
		break;
	case 54: // key 6
		renderer->clearMode = CLEAR_MODE_RANDOM;
		ofLog() << "<clear mode: RANDOM>";
		break;
	default:
		renderer->clearMode = CLEAR_MODE_RANDOM;
		break;
	}
	
	renderer->hasChanged = true;
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
