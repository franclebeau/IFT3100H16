// IFT3100H16_Locator/main.cpp
// Transformation d'un ensemble de localisateurs au hasard dans un espace cubique,
// avec possibilités d'activer et de désactiver les attributs de translation, de rotation et de dimension.

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