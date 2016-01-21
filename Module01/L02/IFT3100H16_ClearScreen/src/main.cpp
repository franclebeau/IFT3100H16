// IFT3100H16_ClearScreen/main.cpp
// Exemple de configuration de la couleur d'arri�re-plan,
// avec une couleur fixe ou al�atoire (touches 1-6).

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
