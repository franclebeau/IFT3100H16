// IFT3100H16_ImageExport/main.cpp
// Exemple d'exportation du contenu actuel de la fen�tre d'affichage dans un fichier image situ�e le r�pertoire ./bin/data.
// L'exportation est d�clanch�e lorsque la barre d'espacement est relach�e.

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
