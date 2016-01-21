// IFT3100H16_Tryptique/main.cpp
// Exemple d'échantillonnage dans une image chargée en mémoire pour en extraire 3 images différentes,
// qui sont affichées sur une rangée avec un espacement horizontal et vertical.

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
