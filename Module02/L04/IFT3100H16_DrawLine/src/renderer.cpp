// IFT3100H16_DrawLine/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer(){}

void Renderer::setup()
{
	ofSetFrameRate(60);

	// prendre une copie de la résolution du framebuffer
	framebufferWidth  = ofGetWidth();
	framebufferHeight = ofGetHeight();

	// déterminer la résolution des gros pixels
	fatPixelResolution = 16;

	// déterminer la résolution de la grille de gros pixels
	fatPixelGridWidth  = framebufferWidth  / fatPixelResolution;

	// déterminer la résolution de la grille de gros pixels
	fatPixelGridHeight = framebufferHeight / fatPixelResolution;

	// nombre maximal de gros pixels dans l'image
	bufferCount = fatPixelGridWidth * fatPixelGridHeight;

	// calculer la taille de la structure commune à tous les gros pixels
	bufferStride = sizeof(StructFatPixel);

	// calculer le nombre d'octets à allouer pour un tableau contenant tous les gros pixels de l'image
	bufferSize = bufferCount * bufferStride;

	// allouer un espace mémoire de taille suffisante pour contenir les données de l'ensemble des gros pixels de l'image
	fatPixels = (StructFatPixel *) calloc(bufferSize, bufferStride);

	// initialisation des variables

	lineRasterMode = LINE_RASTERIZER_BRESENHAM;

	strokeColorOnR = 255;
	strokeColorOnG = 255;
	strokeColorOnB = 255;
	strokeColorOnA = 255;

	strokeColorOffR = 63;
	strokeColorOffG = 63;
	strokeColorOffB = 63;
	strokeColorOffA = 255;

	strokeColorPreviewR = 127;
	strokeColorPreviewG = 127;
	strokeColorPreviewB = 127;
	strokeColorPreviewA = 255;

	strokeWidthDefault = 2;

	xMousePress   = yMousePress   = 0;
	xMouseCurrent = yMouseCurrent = 0;

	isMouseButtonPressed = false;

	isVerbose = false;

	// initialisation de la scène
	reset();
}

void Renderer::draw()
{
	ofClear(191);

	for(index = 0; index < bufferCount; ++index)
	{
		drawFatPixel(
			fatPixels[index].position[0],
			fatPixels[index].position[1],
			fatPixelResolution);
	}

	ofSetLineWidth(1);
	ofSetColor(191);

	drawGrid(fatPixelResolution);

	if(isMouseButtonPressed)
	{
		ofNoFill();
		ofSetColor(255);
		ofSetLineWidth(3);

		drawZone(
			xMousePress,
			yMousePress,
			xMouseCurrent,
			yMouseCurrent);

		ofSetLineWidth(1);

		ofSetColor(31);

		drawLine(
			xMousePress,
			yMousePress,
			xMouseCurrent,
			yMouseCurrent);
	}

	ofSetLineWidth(2);
	ofSetColor(32);

	drawCursor(xMouseCurrent, yMouseCurrent);
}

// fonction qui initialise les gros pixels de l'image
void Renderer::reset()
{
	int xIndex;
	int yIndex;

	for(index = 0; index < bufferCount; ++index)
	{
		xIndex = index % fatPixelGridHeight;
		yIndex = index / fatPixelGridWidth;

		fatPixels[index].state = 0;

		fatPixels[index].position[0] = xIndex * fatPixelResolution;
		fatPixels[index].position[1] = yIndex * fatPixelResolution;

		fatPixels[index].color[0] = strokeColorOffR;
		fatPixels[index].color[1] = strokeColorOffG;
		fatPixels[index].color[2] = strokeColorOffB;
		fatPixels[index].color[3] = strokeColorOffA;
	}

	ofLog() << "<reset>";
}

// fonction qui manipule les attributs d'un des gros pixels de l'image
void Renderer::fatPixelStateChange(int index, int state)
{
	fatPixels[index].state = state;

	switch(fatPixels[index].state)
	{
		case FAT_PIXEL_STATE_ON:

			fatPixels[index].color[0] = strokeColorOnR;
			fatPixels[index].color[1] = strokeColorOnG;
			fatPixels[index].color[2] = strokeColorOnB;
			fatPixels[index].color[3] = strokeColorOnA;
			break;

		case FAT_PIXEL_STATE_OFF:

			fatPixels[index].color[0] = strokeColorOffR;
			fatPixels[index].color[1] = strokeColorOffG;
			fatPixels[index].color[2] = strokeColorOffB;
			fatPixels[index].color[3] = strokeColorOffA;
			break;

		case FAT_PIXEL_STATE_START:

			fatPixels[index].color[0] = 255;
			fatPixels[index].color[1] = 0;
			fatPixels[index].color[2] = 0;
			fatPixels[index].color[3] = 255;
			break;

		case FAT_PIXEL_STATE_END:

			fatPixels[index].color[0] = 0;
			fatPixels[index].color[1] = 255;
			fatPixels[index].color[2] = 0;
			fatPixels[index].color[3] = 255;
			break;


		case FAT_PIXEL_STATE_PREVIEW:

			fatPixels[index].color[0] = strokeColorPreviewR;
			fatPixels[index].color[1] = strokeColorPreviewG;
			fatPixels[index].color[2] = strokeColorPreviewB;
			fatPixels[index].color[3] = strokeColorPreviewA;
			break;
	}

	if(isVerbose)
		ofLog() << "<fat pixel index: " << index << " change to state: " << state << ")>";
}

// fonction qui détermine si une position 2D est à l'intérieur d'une zone rectangulaire
bool Renderer::isInside(int x, int y, int x1, int y1, int x2, int y2) const
{
	if(x < x1)
		return false;
	if(x > x2)
		return false;
	if(y < y1)
		return false;
	if(y > y2)
		return false;
	return true;
}

// fonction qui détermine l'index d'un gros pixel à partir d'une coordonnée en X et Y dans l'espace de l'image
int Renderer::findIndexOfFatPixelByCoord(int x, int y) const
{
	return y * fatPixelGridWidth + x;
}

// fonction qui détermine l'index d'un gros pixel à partir d'une position dans l'espace de la fenêtre
int Renderer::findIndexOfFatPixelByPosition(int x, int y) const
{
	int xIndex = floor(x / (float) fatPixelResolution);
	int yIndex = floor(y / (float) fatPixelResolution);

	return yIndex * fatPixelGridWidth + xIndex;
}

// fonction qui dessine une ligne par rastérisation avec l'algorithme de DDA
void Renderer::rasterLineDDA(float x1, float y1, float x2, float y2)
{
	int pixelCount = 0;

	int index;

	int xDelta = x2 - x1;
	int yDelta = y2 - y1;

	int length = abs(abs(xDelta) >= abs(yDelta) ? xDelta : yDelta);

	if(length == 0)
		return;

	float xIncrement = xDelta / (float) length;
	float yIncrement = yDelta / (float) length;

	float x = x1 + 0.5f;
	float y = y1 + 0.5f;

	for(int i = 1 ; i <= length ; ++i)
	{
		index = findIndexOfFatPixelByCoord((int) x, (int) y);

		fatPixelStateChange(index, FAT_PIXEL_STATE_ON);

		pixelCount++;

		x += xIncrement;
		y += yIncrement;
	}

	ofLog() << "<raster line with DDA between: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ") with " << pixelCount << " fat pixels>";
}

// fonction qui dessine une ligne par rastérisation avec l'algorithme de Bresenham
void Renderer::rasterLineBresenham(float x1, float y1, float x2, float y2)
{
	int pixelCount = 0;

	int index;

	int xDelta = abs(x2 - x1);
	int yDelta = abs(y2 - y1);

	int xIncrement = (x1 < x2 ? 1 : -1);
	int yIncrement = (y1 < y2 ? 1 : -1);

	int error = (xDelta > yDelta ? xDelta : -yDelta);

	int t1;
	int t2;

	if(error < 0)
		error /= 2;  // éviter le bit shifting à droite des valeurs négatives
	else
		error >>= 1; // bit shifting à droite (division par 2)

	int tmp;

	bool isLineCompleted = false;

	while(!isLineCompleted)
	{
		index = findIndexOfFatPixelByCoord(x1, y1);

		fatPixelStateChange(index, FAT_PIXEL_STATE_ON);

		pixelCount++;

		if(x1 == x2 && y1 == y2)
		{
			isLineCompleted = true;
			continue;
		}

		tmp = error;

		if(tmp > -xDelta)
		{
			error -= yDelta;
			x1 += xIncrement;
		}
		if(tmp < yDelta)
		{
			error += xDelta;
			y1 += yIncrement;
		}
	}

	ofLog() << "<raster line with Bresensam between: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ") with " << pixelCount << " fat pixels>";
}

// fonction qui dessine un gros pixel
void Renderer::drawFatPixel(float x, float y, float diameter) const
{
	ofSetLineWidth(0);
	ofFill();

	ofSetColor(
	   fatPixels[index].color[0],
	   fatPixels[index].color[1],
	   fatPixels[index].color[2],
	   fatPixels[index].color[3]);

	ofDrawRectangle(x, y, diameter, diameter);

	if(isVerbose || false)
		ofLog() << "<draw fat pixel at: (" << x << ", " << y << ") of diameter: " << diameter << ")>";
}

// fonction qui dessine une grille
void Renderer::drawGrid(int cellSize) const
{
	int index;

	int xSubdivision = (int) framebufferWidth  / (float) cellSize;
	int ySubdivision = (int) framebufferHeight / (float) cellSize;

	for(index = 0 ; index <= xSubdivision; ++index)
		ofDrawLine(index * cellSize, 0, index * cellSize, framebufferHeight);

	for(index = 0 ; index <= ySubdivision; ++index)
		ofDrawLine(0, index * cellSize, framebufferWidth, index * cellSize);

	if(isVerbose)
		ofLog() << "<draw grid with celle size: " << cellSize << ")>";
}

void Renderer::drawLine(float x1, float y1, float x2, float y2) const
{
	ofDrawLine(x1, y1, x2, y2);

	if(isVerbose)
		ofLog() << "<draw line between: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")>";
}

void Renderer::drawRectangle(float x1, float y1, float x2, float y2) const
{
	ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);

	if(isVerbose)
		ofLog() << "<draw rectangle between: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")>";
}

void Renderer::drawZone(float x1, float y1, float x2, float y2) const
{
	float x2Clamp = min(max(0.0f, x2), (float) framebufferWidth);
	float y2Clamp = min(max(0.0f, y2), (float) framebufferHeight);

	ofDrawRectangle(x1, y1, x2Clamp - x1, y2Clamp - y1);
}

void Renderer::drawCursor(float x, float y) const
{
	float length = 10;
	float offset = 5;

	ofDrawLine(x + offset, y, x + offset + length, y);
	ofDrawLine(x - offset, y, x - offset - length, y);
	ofDrawLine(x, y + offset, x, y + offset + length);
	ofDrawLine(x, y - offset, x, y - offset - length);
}

void Renderer::imageExport(const string name, const string extension) const
{
	ofImage imageTemp;

	string timestamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

	string fileName = name + timestamp + "." + extension;

	imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	imageTemp.save(fileName);

	ofLog() << "<export image: " << fileName << ">";
}

Renderer::~Renderer()
{
	free(fatPixels);
}
