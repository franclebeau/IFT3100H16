// IFT3100H16_TriangleSoup/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	isKeyPressUp    = false;
	isKeyPressDown  = false;
	isKeyPressLeft  = false;
	isKeyPressRight = false;
	isKeyPressZ     = false;
	isKeyPressX     = false;

	renderer = nullptr;
}

void ofApp::setup()
{
	ofLog() << "<ofApp::setup>";

	ofSetWindowTitle("soupe au triangles (keys: arrows, z, x, any)");

	renderer = new Renderer();
	renderer->setup();

	isVerbose = false;
}

void ofApp::update()
{
	timeCurrent = ofGetElapsedTimef();
	timeElapsed = timeCurrent - timeLast;
	timeLast = timeCurrent;

	// déplacement sur le plan XZ en fonction de l'état des flèches du clavier
	if(isKeyPressUp)
		renderer->zOffset += renderer->zDelta * timeElapsed;
	if(isKeyPressDown)
		renderer->zOffset -= renderer->zDelta * timeElapsed;
	if(isKeyPressLeft)
		renderer->xOffset += renderer->xDelta * timeElapsed;
	if(isKeyPressRight)
		renderer->xOffset -= renderer->xDelta * timeElapsed;

	// rotation en Y en fonction de l'état des touches Z et X
	if(isKeyPressZ)
		renderer->yOffset += renderer->yDelta * timeElapsed;
	if(isKeyPressX)
		renderer->yOffset -= renderer->yDelta * timeElapsed;
}

void ofApp::draw()
{
	renderer->draw();
}

void ofApp::mouseReleased(int x, int y, int button)
{
	// réinitialiser la scène
	renderer->reset();

	if(isVerbose)
		ofLog() << "<ofApp::mouse release at: (" << x << ", " << y << ")>";
}

void ofApp::keyPressed(int key)
{
	switch(key)
	{
		case 120: // X
			isKeyPressX = true;
			break;
		case 122: // Z
			isKeyPressZ = true;
			break;
		case 356: // key left
			isKeyPressLeft = true;
			break;
		case 357: // key up
			isKeyPressUp = true;
			break;
		case 358: // key right
			isKeyPressRight = true;
			break;
		case 359: // key down
			isKeyPressDown = true;
			break;
		default:
			break;
	}
}

void ofApp::keyReleased(int key)
{
	switch(key)
	{
		case 120: // X
			isKeyPressX = false;
			break;
		case 122: // Z
			isKeyPressZ = false;
			break;
		case 356: // key left
			isKeyPressLeft = false;
			break;
		case 357: // key up
			isKeyPressUp = false;
			break;
		case 358: // key right
			isKeyPressRight = false;
			break;
		case 359: // key down
			isKeyPressDown = false;
			break;
		case ' ': // space
			renderer->imageExport("render","png");
			break;
		default:
			// réinitialiser la scène
			renderer->reset();
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
