// IFT3100H16_EquilateralTriangle/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer(){}

void Renderer::setup()
{
	ofSetFrameRate(1);
	ofSetCircleResolution(64);

	pointDiameter = 16;
}

void Renderer::update()
{
	// déterminer la position du centre de la fenêtre d'affichage
	xViewportCenter = ofGetWidth()  / 2.0f;
	yViewportCenter = ofGetHeight() / 2.0f;

	// déterminer la position du centre du triangle
	xTriangleCenter = xViewportCenter;
	yTriangleCenter = yViewportCenter;

	// déterminer la longueur de la moitié d'une arête du triangle
	edgeDiameterHalf = min(ofGetWidth(), ofGetHeight()) / 3.0f;

	// déterminer la longueur des arêtes du triangle
	edgeDiameter = edgeDiameterHalf * 2.0f;

	// déterminer les rayons des cercles intérieur et extérieur du triangle
	radiusInnercircle =  edgeDiameter * sqrt(3.0f) / 6.0f;
	radiusCircumcircle = edgeDiameter * sqrt(3.0f) / 3.0f;

	// déterminer l'altitude du triangle
	triangleAltitude = edgeDiameterHalf * sqrt(3.0f);

	// déterminer le périmètre de la surface du triangle
	trianglePerimeter = edgeDiameter * 3.0f;

	// déterminer l'aire de la surface du triangle
	triangleArea = edgeDiameter * edgeDiameter * (sqrt(3.0f) / 4.0f);

	// déterminer la position du point d'intersection de la ligne médiane du premier sommet avec l'arête opposée du triangle
	xTriangleOrigin = xViewportCenter;
	yTriangleOrigin = yViewportCenter + radiusInnercircle;

	// déterminer la position des 3 sommets du triangle
	xVertex1 = xTriangleOrigin;
	yVertex1 = yTriangleOrigin - triangleAltitude;
	xVertex2 = xTriangleOrigin + edgeDiameterHalf;
	yVertex2 = yTriangleOrigin;
	xVertex3 = xTriangleOrigin - edgeDiameterHalf;
	yVertex3 = yTriangleOrigin;

	ofLog()     << setprecision(4)    << "<triangle: "    <<
	"v1:("  << xVertex1 << ", "   << yVertex1 << ") " <<
	"v2:("  << xVertex2 << ", "   << yVertex2 << ") " <<
	"v3:("  << xVertex3 << ", "   << yVertex3 << ") " <<
	"ri:"   << radiusInnercircle  << " "              <<
	"rc:"   << radiusCircumcircle << " "              <<
	"edge:"	<< edgeDiameter       << " "              <<
	"alti:" << triangleAltitude   << " "              <<
	"peri:" << trianglePerimeter  << " "              <<
	"area:" << (int)triangleArea  << ">";
}

void Renderer::draw()
{
	// couleurs d'arrière-plan dégradées
	ofBackgroundGradient(ofColor(191), ofColor(127));

	// dessiner une grille sur le plan XY
	ofDrawGrid(max(ofGetWidth(), ofGetHeight())/8.0f, 8, false, false, false, true);

	// dessiner la zone de remplissage du triangle
	ofFill();
	ofSetColor(255);
	ofDrawTriangle(
		xVertex1, yVertex1,
		xVertex2, yVertex2,
		xVertex3, yVertex3);

	// dessiner les cercles interne et externe du triangle
	ofNoFill();
	ofSetLineWidth(2);
	ofSetColor(191);
	ofDrawEllipse(xViewportCenter, yViewportCenter, radiusInnercircle * 2, radiusInnercircle * 2);
	ofDrawEllipse(xViewportCenter, yViewportCenter, radiusCircumcircle * 2, radiusCircumcircle * 2);

	// dessiner la ligne de contour du triangle
	ofNoFill();
	ofSetColor(31);
	ofSetLineWidth(3);
	ofDrawTriangle(
		xVertex1, yVertex1,
		xVertex2, yVertex2,
		xVertex3, yVertex3);

	// dessiner les trois sommets du triangle dans l'ordre
	ofFill();
	ofSetColor(191, 0, 0);
	ofDrawEllipse(xVertex1, yVertex1, pointDiameter, pointDiameter);
	ofSetColor(0, 191, 0);
	ofDrawEllipse(xVertex2, yVertex2, pointDiameter, pointDiameter);
	ofSetColor(0, 0, 191);
	ofDrawEllipse(xVertex3, yVertex3, pointDiameter, pointDiameter);

	// dessiner le centre du triangle
	ofSetColor(63);
	ofDrawEllipse(xTriangleCenter, yTriangleCenter, pointDiameter, pointDiameter);

	// dessiner le point d'intersection de la ligne médiane du premier sommet avec l'arête opposée du triangle
	ofSetColor(191);
	ofDrawEllipse(xTriangleOrigin, yTriangleOrigin, pointDiameter, pointDiameter);
}

void Renderer::imageExport(const string name, const string extension) const
{
	ofImage imageTemp;

	string timestamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

	string fileName = name + timestamp + "." + extension;

	imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	imageTemp.save(fileName);

	ofLog() << "<export image: " << fileName << ">";
}

Renderer::~Renderer(){}