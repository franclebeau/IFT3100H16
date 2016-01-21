// IFT3100H16_ImageImport/main.cpp
// Exemple d'importation et d'affichage en pleine fen�tre d'une image,
// charg�e � partir d'un fichier qui se trouve dans le r�pertoire ./bin/data
// ou � partir d'une image qui est gliss�e-d�pos�e sur la fen�tre de l'application.

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
