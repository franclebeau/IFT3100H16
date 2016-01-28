// IFT3100H16_DrawZone/main.cpp
// Dessiner une zone de dessin en fonction de la position o� un des boutons de la souris a �t� appuy�
// et de la position courante du curseur de la souris, tout en restant dans les limites du canevas.

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
