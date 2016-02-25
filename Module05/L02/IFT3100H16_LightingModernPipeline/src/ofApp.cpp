// IFT3100H16_LightingModernPipeline/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	isKeyPressUp    = false;
	isKeyPressDown  = false;
	isKeyPressLeft  = false;
	isKeyPressRight = false;

	renderer = nullptr;
}

void ofApp::setup()
{
	ofLog() << "<ofApp::setup>";

	ofSetWindowTitle("éclairage dynamique (pipeline moderne) [uplr, 1-4, f, r, s, v]");

	renderer = new Renderer();
	renderer->setup();

	isVerbose = false;
}

void ofApp::update()
{
	timeCurrent = ofGetElapsedTimef();
	timeElapsed = timeCurrent - timeLast;
	timeLast = timeCurrent;

	if(isKeyPressUp)
		renderer->zOffset += renderer->zDelta * timeElapsed;
	if(isKeyPressDown)
		renderer->zOffset -= renderer->zDelta * timeElapsed;
	if(isKeyPressLeft)
		renderer->xOffset += renderer->xDelta * timeElapsed;
	if(isKeyPressRight)
		renderer->xOffset -= renderer->xDelta * timeElapsed;

	renderer->update();
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

void ofApp::keyPressed(int key)
{
	switch(key)
	{
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
		case 49: // key 1
			renderer->isActiveLightAmbient = !renderer->isActiveLightAmbient;
			ofLog() << "<light ambient: " << renderer->isActiveLightAmbient << ">";
			break;
		case 50: // key 2
			renderer->isActiveLightDirectional = !renderer->isActiveLightDirectional;
			ofLog() << "<light directional: " << renderer->isActiveLightDirectional << ">";
			break;
		case 51: // key 3
			renderer->isActiveLightPoint = !renderer->isActiveLightPoint;
			ofLog() << "<light point: " << renderer->isActiveLightPoint << ">";
			break;
		case 52: // key 4
			renderer->isActiveLightSpot = !renderer->isActiveLightSpot;
			ofLog() << "<light spot: " << renderer->isActiveLightSpot << ">";
			break;
		case 102: // key f
			renderer->isFlipAxisY = !renderer->isFlipAxisY;
			ofLog() << "<axis Y is flipped: " << renderer->isFlipAxisY << ">";
			break;
		case 114: // key r
			renderer->reset();
			break;
		case 115: // key s
			renderer->useSmoothLighting = !renderer->useSmoothLighting;
			ofSetSmoothLighting(renderer->useSmoothLighting);
			ofLog() << "<smooth lighting: " << renderer->useSmoothLighting << ">";
			break;
		case 118: // key v
			isVerbose = !isVerbose;
			renderer->isVerbose = this->isVerbose;
			ofLog() << "<verbose mode:" << isVerbose << ">";
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
			imageExport("render","png");
			break;
		default:
			break;
	}
	if(isVerbose)
		ofLog() << "<ofApp::keyReleased: " << key << ">";
}

void ofApp::windowResized(int w, int h)
{
	renderer->reset();

	ofLog() << "<ofApp::windowResized: (" << w << ", " << h << ")>";
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
