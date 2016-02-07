// IFT3100H16_Discography/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer()
{
	imageTopLeft    = imageTopCenter    = imageTopRight    = nullptr;
	imageMiddleLeft = imageMiddleCenter = imageMiddleRight = nullptr;
	imageBottomLeft = imageBottomCenter = imageBottomRight = nullptr;
}

void Renderer::setup()
{
	ofSetFrameRate(0);

	// définir la valeur des espacements verticals et horizontals
	offsetVertical   = 16;
	offsetHorizontal = 16;

	// définir les dimensions des pochettes au rendu
	imageWidth  = 256;
	imageHeight = 256;

	// ajuster la dimension de la fenêtre
	ofSetWindowShape(
		imageWidth  * 3 + offsetHorizontal * 4,
		imageHeight * 3 + offsetVertical   * 4);

	// importer les pochettes d'album
	imageImport("[1976]-Sad-Wings-of-Destiny.jpg", imageTopLeft);
	imageImport("[1977]-Sin-After-Sin.jpg", imageTopCenter);
	imageImport("[1978]-Hell-Bent-For-Leather.jpg", imageTopRight);

	imageImport("[1982]-Screaming-for-Vengeance.jpg", imageMiddleLeft);
	imageImport("[1984]-Defenders-Of-The-Faith.jpg", imageMiddleCenter);
	imageImport("[1986]-Turbo.jpg",imageMiddleRight);

	imageImport("[1988]-Ram-It-Down.jpg", imageBottomLeft);
	imageImport("[1990]-Painkiller.jpg", imageBottomCenter);
	imageImport("[2005]-Angel-Of-Retribution.jpg", imageBottomRight);
}

void Renderer::draw()
{
	ofClear(32);

	// dessiner l'image du haut à gauche
	imageTopLeft->draw(
		offsetHorizontal,
		imageHeight * 0 + offsetVertical * 1,
		imageWidth,
		imageHeight);

	// dessiner l'image du haut au centre
	imageTopCenter->draw(
		imageWidth  * 1 + offsetHorizontal * 2,
		imageHeight * 0 + offsetVertical * 1,
		imageWidth,
		imageHeight);

	// dessiner l'image du haut à droite
	imageTopRight->draw(
		imageWidth * 2 + offsetHorizontal * 3,
		imageHeight * 0 + offsetVertical * 1,
		imageWidth,
		imageHeight);

	// dessiner l'image du milieu à gauche
	imageMiddleLeft->draw(
		offsetHorizontal,
		imageHeight * 1 + offsetVertical * 2,
		imageWidth,
		imageHeight);

	// dessiner l'image du milieu au centre
	imageMiddleCenter->draw(
		imageWidth  * 1 + offsetHorizontal * 2,
		imageHeight * 1 + offsetVertical * 2,
		imageWidth,
		imageHeight);

	// dessiner l'image du milieu à droite
	imageMiddleRight->draw(
		imageWidth  * 2 + offsetHorizontal * 3,
		imageHeight * 1 + offsetVertical * 2,
		imageWidth,
		imageHeight);

	// dessiner l'image du bas à gauche
	imageBottomLeft->draw(
		offsetHorizontal,
		imageHeight * 2 + offsetVertical * 3,
		imageWidth,
		imageHeight);

	// dessiner l'image du bas au centre
	imageBottomCenter->draw(
		imageWidth  * 1 + offsetHorizontal * 2,
		imageHeight * 2 + offsetVertical * 3,
		imageWidth,
		imageHeight);

	// dessiner l'image du bas à droite
	imageBottomRight->draw(
		imageWidth  * 2 + offsetHorizontal * 3,
		imageHeight * 2 + offsetVertical * 3,
		imageWidth,
		imageHeight);
}

void Renderer::imageImport(const string fileName, ofImage * & imageDestination)
{
	if(imageDestination != nullptr)
	{
		ofLog() << "<delete image: " << imageDestination << ">";
		delete imageDestination;
	}

	imageDestination = new ofImage();

	imageDestination->load(fileName);

	ofLog() << "<import image: " << fileName << " into: " << imageDestination << ">";
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
	if(nullptr != imageTopLeft)
		delete imageTopLeft;
	if(nullptr != imageTopCenter)
		delete imageTopCenter;
	if(nullptr != imageTopRight)
		delete imageTopRight;

	if(nullptr != imageMiddleLeft)
		delete imageMiddleLeft;
	if(nullptr != imageMiddleCenter)
		delete imageMiddleCenter;
	if(nullptr != imageMiddleRight)
		delete imageMiddleRight;

	if(nullptr != imageBottomLeft)
		delete imageBottomLeft;
	if(nullptr != imageBottomCenter)
		delete imageBottomCenter;
	if(nullptr != imageBottomRight)
		delete imageBottomRight;
}
