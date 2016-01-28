// IFT3100H16_ImageExport/main.cpp
// Exemple d'exportation du contenu actuel de la fenêtre d'affichage dans un fichier image située le répertoire ./bin/data.
// L'exportation est déclanchée lorsque la barre d'espacement est relachée.

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
