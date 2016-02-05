// IFT3100H16_Move/main.cpp
// Mouvement dans l'espace sur le plan XZ à partir de l'état des flèches du clavier.

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