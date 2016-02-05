// IFT3100H16_DrawLine/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	ofLog() << "<ofApp::setup>";

	renderer = new Renderer();
	renderer->setup();

	switch(renderer->lineRasterMode)
	{
		case LINE_RASTERIZER_DDA:
			ofSetWindowTitle("rastérisation de lignes (DDA)");
			break;
		case LINE_RASTERIZER_BRESENHAM:
			ofSetWindowTitle("rastérisation de lignes (Bresenham)");
			break;
		default:
			ofSetWindowTitle("rastérisation de lignes");
			break;
	}

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
}

void ofApp::mouseDragged(int x, int y, int button)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;
}

void ofApp::mousePressed(int x, int y, int button)
{
	renderer->isMouseButtonPressed = true;

	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	renderer->xMousePress = x;
	renderer->yMousePress = y;

	if(renderer->isInside(x, y, 0, 0, renderer->framebufferWidth, renderer->framebufferHeight))
	{
		int fatPixelIndex = renderer->findIndexOfFatPixelByPosition(x, y);

		renderer->fatPixelStateChange(fatPixelIndex, FAT_PIXEL_STATE_ON);
	}

	if(isVerbose)
		ofLog() << "<ofApp::mouse press at: (" << x << ", " << y << ")>";
}

void ofApp::mouseReleased(int x, int y, int button)
{
	renderer->isMouseButtonPressed = false;

	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	if(renderer->isInside(x, y, 0, 0, renderer->framebufferWidth, renderer->framebufferHeight))
	{
		int fatPixelIndex1 = renderer->findIndexOfFatPixelByPosition(renderer->xMousePress,   renderer->yMousePress);
		int fatPixelIndex2 = renderer->findIndexOfFatPixelByPosition(renderer->xMouseCurrent, renderer->yMouseCurrent);

		int x1 = fatPixelIndex1 % renderer->fatPixelGridHeight;
		int y1 = fatPixelIndex1 / renderer->fatPixelGridWidth;
		int x2 = fatPixelIndex2 % renderer->fatPixelGridHeight;
		int y2 = fatPixelIndex2 / renderer->fatPixelGridWidth;

		switch(renderer->lineRasterMode)
		{
			case LINE_RASTERIZER_DDA:
				renderer->rasterLineDDA(x1, y1, x2, y2);
				break;

			case LINE_RASTERIZER_BRESENHAM:
				renderer->rasterLineBresenham(x1, y1, x2, y2);
				break;

			default:
				break;
		}

		renderer->fatPixelStateChange(fatPixelIndex1, FAT_PIXEL_STATE_START);
		renderer->fatPixelStateChange(fatPixelIndex2, FAT_PIXEL_STATE_END);
	}

	if(isVerbose)
		ofLog() << "<ofApp::mouse release at: (" << x << ", " << y << ")>";
}

void ofApp::mouseEntered(int x, int y)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;
}

void ofApp::mouseExited(int x, int y)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;
}

void ofApp::keyReleased(int key)
{
	switch(key)
	{
		case 49:  // key 1
			renderer->lineRasterMode = LINE_RASTERIZER_DDA;
			ofSetWindowTitle("rastérisation de lignes (DDA)");
			ofLog() << "<draw mode: DDA>";
			break;
		case 50:  // key 2
			renderer->lineRasterMode = LINE_RASTERIZER_BRESENHAM;
			ofSetWindowTitle("rastérisation de lignes (Bresenham)");
			ofLog() << "<draw mode: BRESENHAM>";
			break;
		case 114: // key r
			renderer->reset();
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
