// IFT3100H16_ImageImport/main.cpp
// Exemple d'importation et d'affichage en pleine fenêtre d'une image,
// chargée à partir d'un fichier qui se trouve dans le répertoire ./bin/data
// ou à partir d'une image qui est glissée-déposée sur la fenêtre de l'application.

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
