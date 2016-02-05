// IFT3100H16_Locator/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer(){}

void Renderer::setup()
{
	ofSetFrameRate(60);

	// initialisation des variables
	speed = 100;

	xOffset = 0;
	zOffset = 0;

	xDelta = speed;
	zDelta = speed;

	isFlipAxisY = false;

	isActiveTranslation = true;
	isActiveRotation    = false;
	isActiveDimension   = false;

	isVerbose = false;

	locatorCount = 1000;
	locatorBufferSize = locatorCount;
	locatorBufferHead = 0;

	// allouer un espace mémoire de taille suffisante pour contenir les données de l'ensemble des localisateurs
	locators = (StructLocator *) calloc(locatorBufferSize, sizeof(StructLocator));

	// allocation d'une instance de node pour l'affichage des localisateurs
	node = new ofNode();

	// allocation de vecteurs pour stocker les attributs de transformation
	vectorPosition  = new ofVec3f(0.0f, 0.0f, 0.0f);
	vectorRotation  = new ofVec3f(0.0f, 0.0f, 0.0f);
	vectorDimension = new ofVec3f(1.0f, 1.0f, 1.0f);

	// initialisation de la scène
	reset();
}

void Renderer::draw()
{
	ofClear(63);

	// rendre le contenu de la scène
	drawScene();
}

// fonction qui initialise la scène
void Renderer::reset()
{
	// extraire la résolution du framebuffer
	framebufferWidth  = ofGetWidth();
	framebufferHeight = ofGetHeight();

	// calculer les coordonnées du centre du framebuffer
	xCenter = framebufferWidth  /2.0f;
	yCenter = framebufferHeight /2.0f;

	// distribuer les localisateur dans l'espace visible de la scène
	dispatchRandomLocator(locatorCount, min(framebufferWidth, framebufferHeight));

	ofLog() << "<reset>";
}

// fonction qui distribue les localisateurs dans un espace cubique
void Renderer::dispatchRandomLocator(int count, float range)
{
	// variable temporaire
	float scale;

	// validations
	if(count <= 0 || range <= 0 || count > locatorBufferSize)
		return;

	// calculer la valeur de la moitié du diamètre du cube
	float halfRange = range / 2.0f;

	// configurer le nombre de localisateurs
	locatorBufferHead = count;

	for(index = 0; index < locatorBufferHead; ++index)
	{
		// déterminer des valeurs de position aléatoires dans le cube
		vectorPosition->x = ofRandom(-halfRange, halfRange);
		vectorPosition->y = ofRandom(-halfRange, halfRange);
		vectorPosition->z = ofRandom(-halfRange, halfRange);

		// déterminer une rotation aléatoire sur l'axe Y
		vectorRotation->x = 0;
		vectorRotation->y = ofRandom(0, 360);
		vectorRotation->z = 0;

		// déterminer une dimension uniforme au hasard entre 10% et 200%
		scale = ofRandom(0.1f, 2.0f);
		
		vectorDimension->x = scale;
		vectorDimension->y = scale;
		vectorDimension->z = scale;

		// configurer les attributs de transformation du localisateur
		locators[index].position  [0] = vectorPosition->x;
		locators[index].position  [1] = vectorPosition->y;
		locators[index].position  [2] = vectorPosition->z;

		locators[index].rotation  [0] = vectorRotation->x;
		locators[index].rotation  [1] = vectorRotation->y;
		locators[index].rotation  [2] = vectorRotation->z;

		locators[index].dimension [0] = vectorDimension->x;
		locators[index].dimension [1] = vectorDimension->y;
		locators[index].dimension [2] = vectorDimension->z;
	}
}

// fonction fait le rendu des entités géométriques de la scène
void Renderer::drawScene()
{
	// configurer la représentation visuelle des localisateurs
	ofFill();
	ofSetLineWidth(2);
	ofSetColor(127);

	// copier la matrice de transformation courante sur le dessus de la pile
	ofPushMatrix();

	// inverser l'axe Y pour qu'il pointe vers le haut
	ofScale(1, isFlipAxisY ? -1 : 1);

	// transformer l'origine de la scène au milieu de la fenêtre d'affichage
	ofTranslate(xCenter + xOffset, isFlipAxisY ? -yCenter : yCenter, zOffset);

	for(index = 0; index < locatorBufferHead; ++index)
	{
		ofPushMatrix();

		if(isActiveTranslation)
		{
			// extraction des attributs de translation
			vectorPosition->x = locators[index].position[0];
			vectorPosition->y = locators[index].position[1];
			vectorPosition->z = locators[index].position[2];
		}
		else
		{
			// attributs de translation par défaut
			vectorRotation->x = 0.0f;
			vectorRotation->y = 0.0f;
			vectorRotation->z = 0.0f;
		}

		// assignation des attributs de translation
		node->setPosition(
			vectorPosition->x,
			vectorPosition->y,
			vectorPosition->z);

		if(isActiveRotation)
		{
			// extraction des attributs de rotation
			vectorRotation->x = locators[index].rotation[0];
			vectorRotation->y = locators[index].rotation[1];
			vectorRotation->z = locators[index].rotation[2];
		}
		else
		{
			// attributs de rotation par défaut
			vectorRotation->x = 0.0f;
			vectorRotation->y = 0.0f;
			vectorRotation->z = 0.0f;
		}

		// assignation des attributs de rotation
		node->setOrientation(*vectorRotation);

		if(isActiveDimension)
		{
			// extraction des attributs de dimension
			vectorDimension->x = locators[index].dimension[0];
			vectorDimension->y = locators[index].dimension[1];
			vectorDimension->z = locators[index].dimension[2];
		}
		else
		{
			// attributs de dimension par défaut
			vectorDimension->x = 1.0f;
			vectorDimension->y = 1.0f;
			vectorDimension->z = 1.0f;
		}

		// assignation des attributs de dimension
		node->setScale(
		   vectorDimension->x,
		   vectorDimension->y,
		   vectorDimension->z);

		// dessiner le localisateur
		node->draw();

		ofPopMatrix();
	}

	// dessiner l'origine de la scène
	drawLocator(10);

	// revenir à la matrice de transformation précédente dans la pile
	ofPopMatrix();
}

void Renderer::drawLocator(float scale)
{
	ofFill();
	ofPushMatrix();
	ofScale(scale, scale);
	node->setPosition(0, 0, 0);
	node->draw();
	ofPopMatrix();
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
	free(locators);

	delete node;

	delete vectorPosition;
	delete vectorRotation;
	delete vectorDimension;
}
