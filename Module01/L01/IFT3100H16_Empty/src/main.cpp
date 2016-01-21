// IFT3100H16_Empty/main.cpp
// Exemple d'un projet relativement vide, mais avec une bonne structure de base
// et une simple animation de la couleur d'arri�re-plan en fonction des frames et du temps �coul�s.
// Un bon point de d�part pour commencer un nouveau projet.

#include "ofMain.h"
#include "ofApp.h"

// point d'entr�e de l'application
int main( )
{
	// cr�ation du contexte de rendu (OpenGL 2.1 par d�faut)
	ofSetupOpenGL(512, 512, OF_WINDOW);

	// instancier et lancer le framework (OpenFrameworks 0.9.0)
	ofRunApp(new ofApp());
}
