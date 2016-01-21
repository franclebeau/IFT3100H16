// IFT3100H16_ImageExport/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer()
{
	image = nullptr;
}

void Renderer::setup()
{
	ofSetFrameRate(60);

	imageImport("field.jpg", image);

	ofSetWindowShape(image->getWidth(), image->getHeight());
}

void Renderer::draw()
{
	ofClear(0);

	image->draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
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

// fonction qui exporte une image à partir de son nom et de son extension, à partir du répertoire ./bin/data ou d'un chemin absolue
void Renderer::imageExport(const string name, const string extension) const
{
	ofImage imageTemp;

	// extraire des données temporelles formatées
	string timestamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

	// générer un nom de fichier unique et ordonné
	string fileName = name + timestamp + "." + extension;

	// capturer le contenu du framebuffer actif
	imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	// sauvegarder le fichier image
	imageTemp.save(fileName);

	ofLog() << "<export image: " << fileName << ">";
}

Renderer::~Renderer()
{
	if(nullptr != image)
		delete image;
}
