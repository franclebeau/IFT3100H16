// IFT3100H16_TriangleSoup/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer(){}

void Renderer::setup()
{
	// paramètres du programme
	triangleCount  = 1000;
	triangleRadius = 16;

	// paramètres de rendu
	ofSetFrameRate(60);
	ofEnableDepthTest();

	// initialisation des variables
	speed = 100;

	xOffset = 0;
	yOffset = 0;
	zOffset = 0;

	xDelta = speed;
	yDelta = speed;
	zDelta = speed;

	triangleBufferSize = triangleCount;
	triangleBufferHead = 0;

	// allouer un espace mémoire de taille suffisante pour contenir les données de l'ensemble des triangles de la soupe
	soup = (StructTriangle *) calloc(triangleBufferSize, sizeof(StructTriangle));

	// allocation de vecteurs pour stocker les attributs de transformation
	vectorOrigin     = new ofVec3f(0.0f, 0.0f, 0.0f);
	vectorPosition1  = new ofVec3f(0.0f, 0.0f, 0.0f);
	vectorPosition2  = new ofVec3f(0.0f, 0.0f, 0.0f);
	vectorPosition3  = new ofVec3f(0.0f, 0.0f, 0.0f);

	// allocation d'un vecteur pour stocker les attributs de couleur
	vectorColor = new ofColor(255);

	// allocation d'une node
	node = new ofNode();

	// initialisation de la scène
	reset();
}

void Renderer::draw()
{
	ofBackgroundGradient(ofColor(127), ofColor(32));

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
	xCenter = framebufferWidth  / 2.0f;
	yCenter = framebufferHeight / 2.0f;

	// déterminer le rayon de la soupe en fonction des dimensions de la fenêtre
	soupRadius = min(framebufferWidth * 0.45f, framebufferHeight * 0.45f);

	// distribuer les localisateur dans l'espace visible de la scène
	dispatchRandomTriangle(triangleCount, soupRadius);

	ofLog() << "<reset>";
}

// fonction qui distribue les triangles dans un hémisphère
void Renderer::dispatchRandomTriangle(int count, float range)
{
	// variable temporaire
	float scale;

	// validations
	if(count <= 0 || range <= 0 || count > triangleBufferSize)
		return;

	// calculer la valeur de la moitié du diamètre du cube
	float halfRange = range / 2.0f;

	// configurer le nombre de triangles
	triangleBufferHead = count;

	for(index = 0; index < triangleBufferHead; ++index)
	{
		// déterminer une position au hasard
		vectorOrigin->x = ofRandom(-1, 1);
		vectorOrigin->y = ofRandom(-1, 1);
		vectorOrigin->z = ofRandom(-1, 1);

		// normaliser la position
		vectorOrigin->normalize();

		// ramener la position dans une hémisphère
		vectorOrigin->z = abs(vectorOrigin->z) * -1;
		(*vectorOrigin) *= soupRadius;

		// déterminer des valeurs de position aléatoires dans le cube
		vectorPosition1->x = vectorOrigin->x + ofRandom(-triangleRadius, triangleRadius);
		vectorPosition1->y = vectorOrigin->y + ofRandom(-triangleRadius, triangleRadius);
		vectorPosition1->z = vectorOrigin->z + ofRandom(-triangleRadius, triangleRadius);

		vectorPosition2->x = vectorOrigin->x + ofRandom(-triangleRadius, triangleRadius);
		vectorPosition2->y = vectorOrigin->y + ofRandom(-triangleRadius, triangleRadius);
		vectorPosition2->z = vectorOrigin->z + ofRandom(-triangleRadius, triangleRadius);

		vectorPosition3->x = vectorOrigin->x + ofRandom(-triangleRadius, triangleRadius);
		vectorPosition3->y = vectorOrigin->y + ofRandom(-triangleRadius, triangleRadius);
		vectorPosition3->z = vectorOrigin->z + ofRandom(-triangleRadius, triangleRadius);

		// déterminer une couleur RGB au hasard
		vectorColor->r = ofRandom(0, 255);
		vectorColor->g = ofRandom(0, 255);
		vectorColor->b = ofRandom(0, 255);
		vectorColor->a = 255;

		// configurer les attributs de transformation du triangle
		soup[index].position1 [0] = vectorPosition1->x;
		soup[index].position1 [1] = vectorPosition1->y;
		soup[index].position1 [2] = vectorPosition1->z;

		soup[index].position2 [0] = vectorPosition2->x;
		soup[index].position2 [1] = vectorPosition2->y;
		soup[index].position2 [2] = vectorPosition2->z;

		soup[index].position3 [0] = vectorPosition3->x;
		soup[index].position3 [1] = vectorPosition3->y;
		soup[index].position3 [2] = vectorPosition3->z;

		soup[index].color     [0] = vectorColor->r;
		soup[index].color     [1] = vectorColor->g;
		soup[index].color     [2] = vectorColor->b;
		soup[index].color     [3] = vectorColor->a;
	}
}

// fonction fait le rendu des entités géométriques de la scène
void Renderer::drawScene()
{
	// copier la matrice de transformation courante sur le dessus de la pile
	ofPushMatrix();

	// transformer l'origine de la scène au milieu de la fenêtre d'affichage
	ofTranslate(xCenter + xOffset, yCenter, zOffset);

	// dessiner la soupe de triangles
	drawSoup();

	// dessiner l'origine de la scène
	drawLocator(3);

	// revenir à la matrice de transformation précédente dans la pile
	ofPopMatrix();
}

// fonction de rendu de la soupe
void Renderer::drawSoup()
{
	ofPushMatrix();

	// rotation en Y de la scène
	ofRotate(yOffset, 0, 1, 0);

	// légère rotation en Z de la soupe
	ofRotate(ofGetFrameNum() * 0.1f, 0, 0, 1);

	// dessiner les triangles
	for(index = 0; index < triangleBufferHead; ++index)
		drawTriangle(index);

	ofPopMatrix();
}

// fonction qui dessine un des triangles de la soupe
void Renderer::drawTriangle(int indexInSoup)
{
	ofFill();

	ofSetColor(
		soup[indexInSoup].color[0],
		soup[indexInSoup].color[1],
		soup[indexInSoup].color[2],
		soup[indexInSoup].color[3]);

	vectorPosition1->x = soup[index].position1[0];
	vectorPosition1->y = soup[index].position1[1];
	vectorPosition1->z = soup[index].position1[2];

	vectorPosition2->x = soup[index].position2[0];
	vectorPosition2->y = soup[index].position2[1];
	vectorPosition2->z = soup[index].position2[2];

	vectorPosition3->x = soup[index].position3[0];
	vectorPosition3->y = soup[index].position3[1];
	vectorPosition3->z = soup[index].position3[2];

	ofDrawTriangle(
		*vectorPosition1,
		*vectorPosition2,
		*vectorPosition3);
}

void Renderer::drawLocator(float scale)
{
	ofFill();
	ofSetColor(192);
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
	free(soup);

	delete vectorOrigin;

	delete vectorPosition1;
	delete vectorPosition2;
	delete vectorPosition3;

	delete vectorColor;
	delete node;
}
