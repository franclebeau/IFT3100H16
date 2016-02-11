// IFT3100H16_RegularPolygon/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	ofSetWindowTitle("polygones réguliers (keys: [0-9])");

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

void ofApp::keyReleased(int key)
{
	switch(key)
	{
		case 48:  // key 0
			renderer->side = 12;
			ofLog() << "<draw mode: DODÉCAGONE>";
			break;
		case 49:  // key 1
			renderer->side = 3;
			ofLog() << "<draw mode: TRIANGLE>";
			break;
		case 50:  // key 2
			renderer->side = 4;
			ofLog() << "<draw mode: CARRÉ>";
			break;
		case 51:  // key 3
			renderer->side = 5;
			ofLog() << "<draw mode: PENTAGONE>";
			break;
		case 52:  // key 4
			renderer->side = 6;
			ofLog() << "<draw mode: HEXAGONE>";
			break;
		case 53:  // key 5
			renderer->side = 7;
			ofLog() << "<draw mode: HEPTAGONE>";
			break;
		case 54:  // key 5
			renderer->side = 8;
			ofLog() << "<draw mode: OCTOGONE>";
			break;
		case 55:  // key 5
			renderer->side = 9;
			ofLog() << "<draw mode: NONAGONE>";
			break;
		case 56:  // key 5
			renderer->side = 10;
			ofLog() << "<draw mode: DÉCAGONE>";
			break;
		case 57:  // key 5
			renderer->side = 11;
			ofLog() << "<draw mode: HENDÉCAGONE>";
			break;
		case ' ': // space
			renderer->imageExport("render","png");
			break;
		default:
			ofLog() << "<ofApp::keyReleased: " << key << ">";
			break;
	}
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