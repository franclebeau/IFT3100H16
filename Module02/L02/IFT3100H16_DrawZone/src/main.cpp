// IFT3100H16_DrawZone/main.cpp
// Dessiner une zone de dessin en fonction de la position où un des boutons de la souris a été appuyé
// et de la position courante du curseur de la souris, tout en restant dans les limites du canevas.

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
