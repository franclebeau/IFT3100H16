// IFT3100H16_Discography/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	ofSetWindowTitle("discography");

	ofLog() << "<ofApp::setup>";

	renderer = new Renderer();
	renderer->setup();
}

void ofApp::draw()
{
	renderer->draw();
}

void ofApp::keyReleased(int key)
{
	ofLog() << "<ofApp::keyReleased: " << key << ">";
	
	if(key == ' ')
		renderer->imageExport("render", "png");
}

void ofApp::windowResized(int w, int h)
{
	ofLog() << "<ofApp::windowResized to: (" << w << ", " << h << ")>";
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
