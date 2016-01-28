// IFT3100H16_DrawCursor/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	ofSetWindowTitle("draw cursor");

	ofLog() << "<ofApp::setup>";

	renderer = new Renderer();
	renderer->setup();

	isVerbose = false;
}

void ofApp::draw()
{
	// afficher le tableau de primitives vectorielles
	renderer->draw();
}

// fonction invoqu�e quand la position du curseur change
void ofApp::mouseMoved(int x, int y)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	if(isVerbose)
		ofLog() << "<ofApp::mouse move at: (" << x << ", " << y << ")>";
}

// fonction invoqu�e quand la position du curseur change pendant qu'un bouton de la souris est appuy�
void ofApp::mouseDragged(int x, int y, int button)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	if(isVerbose)
		ofLog() << "<ofApp::mouse drag at: (" << x << ", " << y << ") button:" << button <<">";
}

// fonction invoqu�e quand un bouton de la souris est appuy�
void ofApp::mousePressed(int x, int y, int button)
{
	renderer->isMouseButtonPressed = true;

	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	renderer->xMousePress = x;
	renderer->yMousePress = y;

	ofLog() << "<ofApp::mouse press at: (" << x << ", " << y << ")>";
}

// fonction invoqu�e quand un bouton de la souris est relach�
void ofApp::mouseReleased(int x, int y, int button)
{
	renderer->isMouseButtonPressed = false;

	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	ofLog() << "<ofApp::mouse release at: (" << x << ", " << y << ")>";
}

// fonction invoqu�e quand le curseur entre dans la fen�tre
void ofApp::mouseEntered(int x, int y)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	ofLog() << "<ofApp::mouse enter at: (" << x << ", " << y << ")>";
}

// fonction invoqu�e quand le curseur sort dans la fen�tre
void ofApp::mouseExited(int x, int y)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	ofLog() << "<ofApp::mouse exit  at: (" << x << ", " << y << ")>";
}

// fonction invoqu�e quand une touche du clavier est rel�ch�e
void ofApp::keyReleased(int key)
{
	ofLog() << "<ofApp::keyReleased: " << key << ">";

	switch(key)
	{
		case 118: // key v
			isVerbose = !isVerbose;
			renderer->isVerbose = this->isVerbose;
			ofLog() << "<verbose mode:" << isVerbose << ">";
			break;
		case ' ': // space
			renderer->imageExport("render","png");
			break;
		default:
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
