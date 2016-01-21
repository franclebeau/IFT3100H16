// IFT3100H16_ImageImport/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	ofSetWindowTitle("import image");

	ofLog() << "<ofApp::setup>";

	renderer = new Renderer();
	renderer->setup();
}

void ofApp::draw()
{
	renderer->draw();
}

void ofApp::windowResized(int w, int h)
{
	ofLog() << "<ofApp::windowResized to: (" << w << ", " << h << ")>";
}

// fonction invoqu�e quand une s�lection de fichiers est d�pos� sur la fen�tre de l'application
void ofApp::dragEvent(ofDragInfo dragInfo)
{
	ofLog() << "<ofApp::ofDragInfo file[0]: " << dragInfo.files.at(0)
			<< " at : " << dragInfo.position << ">";

	// importer le premier fichier d�pos� sur la fen�tre si c'est une image (attention : aucune validation du type de fichier !)
	renderer->imageImport(dragInfo.files.at(0), renderer->image);

	// redimensionner la fen�tre aux dimensions de l'image
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
