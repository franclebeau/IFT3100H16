// IFT3100H16_DrawVectorPrimitives/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	ofSetWindowTitle("dessin vectoriel (keys: 1-5, s, f, r)");

	ofLog() << "<ofApp::setup>";

	renderer = new Renderer();
	renderer->setup();

	isVerbose = false;
}

void ofApp::draw()
{
	renderer->draw();
}

void ofApp::mouseMoved(int x, int y)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	if(isVerbose)
		ofLog() << "<ofApp::mouse move at: (" << x << ", " << y << ")>";
}

void ofApp::mouseDragged(int x, int y, int button)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	if(isVerbose)
		ofLog() << "<ofApp::mouse drag at: (" << x << ", " << y << ") button:" << button <<">";
}

void ofApp::mousePressed(int x, int y, int button)
{
	renderer->isMouseButtonPressed = true;

	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	renderer->xMousePress = x;
	renderer->yMousePress = y;

	ofLog() << "<ofApp::mouse press at: (" << x << ", " << y << ")>";
}

void ofApp::mouseReleased(int x, int y, int button)
{
	renderer->isMouseButtonPressed = false;

	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	renderer->addVectorShape(renderer->drawMode);

	ofLog() << "<ofApp::mouse release at: (" << x << ", " << y << ")>";
}

void ofApp::mouseEntered(int x, int y)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	ofLog() << "<ofApp::mouse enter at: (" << x << ", " << y << ")>";
}

void ofApp::mouseExited(int x, int y)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	ofLog() << "<ofApp::mouse exit  at: (" << x << ", " << y << ")>";
}

void ofApp::keyReleased(int key)
{
	ofLog() << "<ofApp::keyReleased: " << key << ">";

	switch(key)
	{
		case 49:  // key 1
			renderer->drawMode = VECTOR_PRIMITIVE_PIXEL;
			ofLog() << "<draw mode: PIXEL>";
			break;
		case 50:  // key 2
			renderer->drawMode = VECTOR_PRIMITIVE_POINT;
			ofLog() << "<draw mode: POINT>";
			break;
		case 51:  // key 3
			renderer->drawMode = VECTOR_PRIMITIVE_LINE;
			ofLog() << "<draw mode: LINE>";
			break;
		case 52:  // key 4
			renderer->drawMode = VECTOR_PRIMITIVE_RECTANGLE;
			ofLog() << "<draw mode: RECTANGLE>";
			break;
		case 53:  // key 5
			renderer->drawMode = VECTOR_PRIMITIVE_ELLIPSE;
			ofLog() << "<draw mode: ELLIPSE>";
			break;
		case 102: // key f
			renderer->randomColorFill();
			break;
		case 114: // key r
			renderer->reset();
			break;
		case 115: // key s
			renderer->randomColorStroke();
			break;
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
