// IFT3100H16_Discography/main.cpp
// Programme qui fait une mise en page de 9 pochettes d'album dans une grille de 3x3,
// avec un léger espacement horizontal et vertical,
// par dessus une couleur d'arrière-plan dans un ton de gris très foncé.
// Les pochettes d'album sont importées sous forme de 9 fichiers images distincts.


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
