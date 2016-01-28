// IFT3100H16_DrawVectorPrimitives/main.cpp
// Dessiner des primitives vectorielles dans la zone de dessin (pixel, point, ligne, rectangle et ellipse)
// avec des couleurs al�atoires pour les lignes de contour et les zones de remplissage.

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
