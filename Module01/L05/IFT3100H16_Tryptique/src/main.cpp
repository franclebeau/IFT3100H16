// IFT3100H16_Tryptique/main.cpp
// Exemple d'�chantillonnage dans une image charg�e en m�moire pour en extraire 3 images diff�rentes,
// qui sont affich�es sur une rang�e avec un espacement horizontal et vertical.

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
