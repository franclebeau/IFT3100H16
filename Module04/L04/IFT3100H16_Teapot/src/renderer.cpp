// IFT3100H16_Teapot/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer(){}

void Renderer::setup()
{
	ofSetFrameRate(60);
	ofEnableDepthTest();

	// initialisation des variables
	speed = 100;

	xOffset = 0;
	zOffset = 0;

	xDelta = speed;
	zDelta = speed;

	isFlipAxisY = false;

	isActiveTranslation = true;
	isActiveRotation    = true;
	isActiveDimension   = true;

	isVerbose = false;

	locatorCount = 100;
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

	// chargement du modèle 3D
	teapot = new ofxAssimpModelLoader();
	teapot->loadModel("teapot.obj");

	// création d'une lumière
	light = new ofLight();

	// initialisation de la scène
	reset();
}

void Renderer::draw()
{
	ofBackground(31);

	// rendre le contenu de la scène
	drawScene();
}

// fonction qui initialise la scène
void Renderer::reset()
{
	ofEnableDepthTest();
	ofEnableLighting();

	// activer la lumière
	light->setAmbientColor(ofColor(0, 255, 0));
	light->setDiffuseColor(ofColor(255, 255, 255));
	light->enable();

	// extraire la résolution du framebuffer
	framebufferWidth  = ofGetWidth();
	framebufferHeight = ofGetHeight();

	// calculer les coordonnées du centre du framebuffer
	xCenter = framebufferWidth  / 2.0f;
	yCenter = framebufferHeight / 2.0f;

	// distribuer les localisateur dans l'espace visible de la scène
	dispatchRandomLocator(locatorCount, min(framebufferWidth * 0.6f, framebufferHeight * 0.6f));

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
		scale = ofRandom(0.05f, 0.35f);
		
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

	// positionner la lumière
	light->setPosition(0, 0, 1000);

	// copier la matrice de transformation courante sur le dessus de la pile
	ofPushMatrix();

	// inverser l'axe Y pour qu'il pointe vers le haut
	ofScale(1, isFlipAxisY ? -1 : 1);

	// transformer l'origine de la scène au milieu de la fenêtre d'affichage
	ofTranslate(xCenter + xOffset, isFlipAxisY ? -yCenter : yCenter, zOffset);

	// légère rotation de la scène
	ofRotate(ofGetFrameNum() * 0.1f, 0, 1, 0);

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
			vectorPosition->x = 0.0f;
			vectorPosition->y = 0.0f;
			vectorPosition->z = 0.0f;
		}

		// assignation des attributs de translation
		node->setPosition(
			vectorPosition->x,
			vectorPosition->y,
			vectorPosition->z);

		teapot->setPosition(
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
		teapot->setRotation(0, vectorRotation->y, 0, 1, 0);

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

		teapot->setScale(
			vectorDimension->x,
			vectorDimension->y,
			vectorDimension->z);

		// dessiner un localisateur
		node->draw();

		// dessiner un teapot
		teapot->draw(OF_MESH_FILL);

		ofPopMatrix();
	}

	// dessiner l'origine de la scène
	drawLocator(1);

	// revenir à la matrice de transformation précédente dans la pile
	ofPopMatrix();
}

void Renderer::drawLocator(float scale)
{
	ofFill();
	ofSetColor(127);
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

	delete teapot;

	delete light;

	delete node;

	delete vectorPosition;
	delete vectorRotation;
	delete vectorDimension;
}
