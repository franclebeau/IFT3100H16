// IFT3100H16_LightingModernPipeline/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer(){}

void Renderer::setup()
{
	ofSetFrameRate(60);
	ofEnableDepthTest();
	ofSetSphereResolution(32);

	// paramètres
	cameraOffset     = 350;
	speedMotion      = 150;
	speedOscillation = 7500;
	xInitial         = 0;
	yInitial         = -100;
	scaleCube        = 100.0f;
	scaleSphere      = 80.0f;
	scaleTeapot      = 0.618f;

	// initialisation des variables

	xOffset = xInitial;
	zOffset = yInitial;

	xDelta = speedMotion;
	zDelta = speedMotion;

	useSmoothLighting = true;

	isFlipAxisY = false;

	isActiveLightAmbient     = true;
	isActiveLightDirectional = true;
	isActiveLightPoint       = true;
	isActiveLightSpot        = true;

	isVerbose = false;

	// vecteurs de position des géométries
	positionCube   = new ofVec3f();
	positionSphere = new ofVec3f();
	positionTeapot = new ofVec3f();

	// orientations des lumières
	orientationDirectional = new ofQuaternion();
	orientationSpot = new ofQuaternion();

	// chargement du modèle 3D
	teapot = new ofxAssimpModelLoader();
	teapot->loadModel("teapot.obj");

	// instanciation des lumières dynamiques
	lightAmbient     = new ofColor();
	lightDirectional = new ofLight();
	lightPoint       = new ofLight();
	lightSpot        = new ofLight();

	// instanciation des matériaux
	materialCube   = new ofMaterial();
	materialSphere = new ofMaterial();
	materialTeapot = new ofMaterial();

	// initialisation de la scène
	reset();
}

void Renderer::reset()
{
	// initialisation des variables
	framebufferWidth  = ofGetWidth();
	framebufferHeight = ofGetHeight();

	// centre du framebuffer
	xCenter = framebufferWidth  / 2.0f;
	yCenter = framebufferHeight / 2.0f;

	// déterminer la position des géométries
	positionCube->set(-framebufferWidth * (1.0f/4.0f), 0, 0);
	positionSphere->set(0, 0, 0);
	positionTeapot->set(framebufferWidth * (1.0f/4.0f), 50, 0);

	// configurer le matériau du cube
	materialCube->setAmbientColor  (ofColor( 63,  63,  63));
	materialCube->setDiffuseColor  (ofColor(127,   0,   0));
	materialCube->setEmissiveColor (ofColor( 31,   0,   0));
	materialCube->setSpecularColor (ofColor(127, 127, 127));
	materialCube->setShininess     (16.0f);

	// configurer le matériau de la sphère
	materialSphere->setAmbientColor  (ofColor( 63,  63,  63));
	materialSphere->setDiffuseColor  (ofColor(191,  63,   0));
	materialSphere->setEmissiveColor (ofColor(  0,  31,   0));
	materialSphere->setSpecularColor (ofColor(255, 255,  64));
	materialSphere->setShininess     (8.0f);

	// configurer le matériau du teapot
	materialTeapot->setAmbientColor  (ofColor( 63,  63,  63));
	materialTeapot->setDiffuseColor  (ofColor(191,   0,  63));
	materialTeapot->setEmissiveColor (ofColor(  0,   0,  31));
	materialTeapot->setSpecularColor (ofColor(191, 191, 191));
	materialTeapot->setShininess     (8.0f);

	// configurer la lumière ambiante
	lightAmbient = new ofColor(127, 127, 127);

	// configurer la lumière directionnelle
	lightDirectional->setDiffuseColor  (ofColor(31,  255,  31));
	lightDirectional->setSpecularColor (ofColor(191, 191, 191));
	lightDirectional->setOrientation(ofVec3f(0.0f, 0.0f, 0.0f));
	lightDirectional->setDirectional();

	// configurer la lumière ponctuelle
	lightPoint->setDiffuseColor  (ofColor(255, 255, 255));
	lightPoint->setSpecularColor (ofColor(191, 191, 191));
	lightPoint->setPointLight();

	// configurer la lumière projecteur
	lightSpot->setDiffuseColor  (ofColor(191, 191, 191));
	lightSpot->setSpecularColor (ofColor(191, 191, 191));
	lightSpot->setOrientation(ofVec3f(0.0f, 0.0f, 0.0f));
	lightSpot->setSpotConcentration(2);
	lightSpot->setSpotlightCutOff(30);
	lightSpot->setSpotlight();

	ofLog() << "<reset>";
}

void Renderer::update()
{
	ofPushMatrix();

	if(isActiveLightDirectional)
	{
		// transformer la lumière directionnelle
		orientationDirectional->makeRotate(int(ofGetElapsedTimeMillis() * 0.1f) % 360, 0, 1, 0);

		lightDirectional->setPosition(xCenter, yCenter + 60, cameraOffset * 0.75f);
		lightDirectional->setOrientation(*orientationDirectional);
	}

	if(isActiveLightPoint)
	{
		// transformer la lumière ponctuelle
		lightPoint->setPosition(ofGetMouseX(), ofGetMouseY(), cameraOffset * 0.75f);
	}

	if(isActiveLightSpot)
	{
		// transformer la lumière projecteur
		oscillation = oscillate(ofGetElapsedTimeMillis(), 45, speedOscillation, 0, 0);

		orientationSpot->makeRotate(30, ofVec3f(1, 0, 0), oscillation, ofVec3f(0, 1, 0), 0, ofVec3f(0, 0, 1));

		lightSpot->setOrientation(*orientationSpot);

		lightSpot->setPosition (xCenter, yCenter - 75, cameraOffset * 0.75f);
	}

	ofPopMatrix();
}

void Renderer::draw()
{
	ofBackground(0);

	ofPushMatrix();

		// afficher un repère visuel pour les lumières
		if(isActiveLightPoint)
			lightPoint->draw();
		if(isActiveLightDirectional)
			lightDirectional->draw();
		if(isActiveLightSpot)
			lightSpot->draw();

	ofPopMatrix();

	ofPushMatrix();

		// inverser l'axe Y pour qu'il pointe vers le haut
		ofScale(1, isFlipAxisY ? -1 : 1);

		// transformer l'origine de la scène au milieu de la fenêtre d'affichage
		ofTranslate(xCenter + xOffset, isFlipAxisY ? -yCenter : yCenter, zOffset);

		// légère rotation de la scène
		ofRotate(ofGetFrameNum() * 0.25f, 0, 1, 0);

		ofPushMatrix();

			// position
			ofTranslate(
				positionCube->x,
				positionCube->y,
				positionCube->z);

			// rotation locale
			ofRotate(ofGetFrameNum() * 1.0f, 0, 1, 0);

			// activer l'éclairage dynamique
			ofEnableLighting();

			// activer les lumières
			lightingOn();

			// activer le matériau
			materialCube->begin();

			// dessiner un cube
			ofDrawBox(0, 0, 0, scaleCube);

			// désactiver le matériau
			materialCube->end();

			// désactiver les lumières
			lightingOff();

			// désactiver l'éclairage dynamique
			ofDisableLighting();

		ofPopMatrix();

		ofPushMatrix();

			// position
			ofTranslate(
				positionSphere->x,
				positionSphere->y,
				positionSphere->z);

			// rotation locale
			ofRotate(ofGetFrameNum() * 1.0f, 0, 1, 0);

			// activer l'éclairage dynamique
			ofEnableLighting();

			// activer les lumières
			lightingOn();

			// activer le matériau
			materialSphere->begin();

			// dessiner une sphère
			ofDrawSphere(0, 0, 0, scaleSphere);

			// désactiver le matériau
			materialSphere->end();

			// désactiver les lumières
			lightingOff();

			// désactiver l'éclairage dynamique
			ofDisableLighting();

		ofPopMatrix();

		ofPushMatrix();

			// position
			teapot->setPosition(
				positionTeapot->x,
				positionTeapot->y + 15,
				positionTeapot->z);

			// rotation locale
			teapot->setRotation(0, ofGetFrameNum() * -1.0f, 0, 1, 0);

			// dimension
			teapot->setScale(
				scaleTeapot,
				scaleTeapot,
				scaleTeapot);

			// activer l'éclairage dynamique
			ofEnableLighting();

			// activer les lumières
			lightingOn();

			// activer le matériau
			materialTeapot->begin();

			// dessiner un teapot
			teapot->draw(OF_MESH_FILL);

			// désactiver le matériau
			materialTeapot->end();

			// désactiver les lumières
			lightingOff();

			// désactiver l'éclairage dynamique
			ofDisableLighting();

		ofPopMatrix();

	ofPopMatrix();
}

// désactivation des lumières dynamiques
void Renderer::lightingOn()
{
	if(isActiveLightAmbient)
		ofSetGlobalAmbientColor(*lightAmbient);
	else
		ofSetGlobalAmbientColor(ofColor(0, 0, 0));

	if(isActiveLightDirectional)
		lightDirectional->enable();

	if(isActiveLightPoint)
		lightPoint->enable();

	if(isActiveLightSpot)
		lightSpot->enable();
}

// activation des lumières dynamiques
void Renderer::lightingOff()
{
	ofSetGlobalAmbientColor(ofColor(0, 0, 0));
	lightDirectional->disable();
	lightPoint->disable();
	lightSpot->disable();
}

Renderer::~Renderer()
{
	delete lightAmbient;
	delete lightDirectional;
	delete lightPoint;
	delete lightSpot;

	delete materialCube;
	delete materialSphere;
	delete materialTeapot;

	delete teapot;

	delete orientationDirectional;
	delete orientationSpot;

	delete positionCube;
	delete positionSphere;
	delete positionTeapot;
}
