// IFT3100H16_RegularPolygon/main.cpp
// Dessiner les polygones réguliers du triangle au dodécagone.

#include "ofMain.h"
#include "ofApp.h"

// point d'entrée de l'application
int main( )
{
	// création du contexte de rendu (OpenGL 2.1 par défaut)
	ofSetupOpenGL(512, 512, OF_WINDOW);
	
	// instancier et lancer le framework (OpenFrameworks 0.9.0)
	ofRunApp(new ofApp());
}