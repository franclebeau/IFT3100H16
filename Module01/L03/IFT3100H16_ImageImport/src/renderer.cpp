// IFT3100H16_ImageImport/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer()
{
	image = nullptr;
}

void Renderer::setup()
{
	ofSetFrameRate(60);

	// importer une image située dans ./bin/data
	imageImport("field.jpg", image);

	// redimensionner la fenêtre aux dimensions de l'image
	ofSetWindowShape(image->getWidth(), image->getHeight());
}

void Renderer::draw()
{
	// couleur de l'arrière-plan
	ofClear(0);

	// tinte de l'image (blanc pour les couleurs d'origine)
	ofSetColor(255);

	// afficher l'image sur toute la surface de la fenêtre
	image->draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

// fonction qui importe une image à partir de son nom et de son extension, à partir du répertoire ./bin/data ou d'un chemin absolue
void Renderer::imageImport(const string fileName, ofImage * & imageDestination)
{
	// détruire l'instance précédente de l'image si elle existe
	if(imageDestination != nullptr)
	{
		ofLog() << "<delete image: " << imageDestination << ">";
		delete imageDestination;
	}
	
	// allocation d'une nouvelle instance d'image
	imageDestination = new ofImage();

	// chargement des donnés du fichier image dans l'objet image en mémoire (RAM)
	imageDestination->load(fileName);
	
	ofLog() << "<import image: " << fileName << " into: " << imageDestination << ">";
}

Renderer::~Renderer()
{
	if(nullptr != image)
		delete image;
}
