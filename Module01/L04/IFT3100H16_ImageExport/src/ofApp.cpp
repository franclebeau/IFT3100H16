// IFT3100H16_ImageExport/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	ofSetWindowTitle("image export");

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
	
	// valider si la clé relâchée est la barre d'espacement (space)
	if(key == ' ')
		renderer->imageExport("render","png");
}

void ofApp::windowResized(int w, int h)
{
	ofLog() << "<ofApp::windowResized to: (" << w << ", " << h << ")>";
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
	ofLog() << "<ofApp::ofDragInfo file[0]: " << dragInfo.files.at(0)
	<< " at : " << dragInfo.position << ">";

	renderer->imageImport(dragInfo.files.at(0), renderer->image);

	if(renderer->image->getWidth() > 0 && renderer->image->getHeight() > 0)
		ofSetWindowShape(renderer->image->getWidth(), renderer->image->getHeight());
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
