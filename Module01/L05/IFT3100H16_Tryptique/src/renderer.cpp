// IFT3100H16_Tryptique/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer()
{
	imageSource = imageLeft = imageCenter = imageRight = nullptr;
}

void Renderer::setup()
{
	ofSetFrameRate(0);

	// définir la valeur des espacements verticals et horizontals
	offsetVertical   = 32;
	offsetHorizontal = 32;

	// définir les dimensions des images de destination
	imageWidth  = 256;
	imageHeight = 256;

	// importer l'image source
	imageImport("forest.jpg", imageSource);

	// ajuster la dimension de la fenêtre en fonction des dimensions de l'image source et des espacements
	ofSetWindowShape(
		imageSource->getWidth()  + offsetHorizontal * 4,
		imageSource->getHeight() + offsetVertical   * 2);

	// copier différentes sections de l'image source dans les images de destination
	imageCopy(imageSource, imageLeft,   imageWidth * 0, 0, imageWidth, imageHeight);
	imageCopy(imageSource, imageCenter, imageWidth * 1, 0, imageWidth, imageHeight);
	imageCopy(imageSource, imageRight,  imageWidth * 2, 0, imageWidth, imageHeight);

	// supprimer l'image source car elle n'est plus nécessaire
	delete imageSource;
	imageSource = nullptr;
}

void Renderer::draw()
{
	ofClear(0);

	// dessiner l'image de gauche
	imageLeft->draw(
		offsetHorizontal,
		offsetVertical,
		imageWidth,
		imageHeight);

	// dessiner l'image du centre
	imageCenter->draw(
		imageWidth * 1 + offsetHorizontal * 2,
		offsetVertical,
		imageWidth,
		imageHeight);

	// dessiner l'image de droite
	imageRight->draw(
		imageWidth * 2 + offsetHorizontal * 3,
		offsetVertical,
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

// fonction qui copie une section d'une image dans une autre.
void Renderer::imageCopy(ofImage * imageSource, ofImage * & imageDestination, int x, int y, int w, int h)
{
	// validation de l'image source
	if(imageSource == nullptr)
		return;

	// validation des paramètres de la section
	if(x < 0 || y < 0 || w < 0 || h < 0)
		return;

	if(x + w > imageSource->getWidth())
		return;

	if(y + h > imageSource->getHeight())
		return;

	// détruire l'instance précédente de l'image si elle existe
	if(imageDestination != nullptr)
	{
		ofLog() << "<delete image: " << imageDestination << ">";
		delete imageDestination;
	}

	// allocation d'une nouvelle instance d'image
	imageDestination = new ofImage();

	// copier les pixels de la section de l'image source dans l'image de destination
	imageDestination->cropFrom(*imageSource, x, y, w, h);

	ofLog() << "<copy image: " << imageSource << " into: " << imageDestination << "\t(" << x << "\t" << y << "\t" << w  << "\t" << h << ")>";
}

Renderer::~Renderer()
{
	if(nullptr != imageSource)
		delete imageSource;
	if(nullptr != imageLeft)
		delete imageLeft;
	if(nullptr != imageCenter)
		delete imageCenter;
	if(nullptr != imageRight)
		delete imageRight;
}
