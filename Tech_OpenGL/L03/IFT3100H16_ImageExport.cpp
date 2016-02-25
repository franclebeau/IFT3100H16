void IFT3100H16_ImageExport()
{
	// préconditions :
	// - l'identifiant unique du framebuffer à copier
	GLuint framebuffer;
	Gluint framebufferID;

	// postconditions :
	// - un fichier image contenant une copie du framebuffer
	// - ensemble des propriétés de l'image
	int imageWidth;
	int imageHeight;
	int imageComponent;
	int imagePixelCount;
	int imageSize;

	// déclarer un pointeur vers un espace mémoire qui servira à stocker les pixels de l'image
	// (GLubyte = 'unsigned byte' de 8 bits donc 256 niveaux de couleur par composante)
	GLubyte * pixels;

	// sélectionner le framebuffer à échantillonner
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// extraire les propriétés de largeur et de hauteur du framebuffer
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH,  &imageWidth);
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &imageHeight);

	// déterminer le nombre de composantes de couleur selon le format de l'image
	imageComponent = 4; // RGBA

	// calculer le nombre total de pixels de l'image
	imagePixelCount = imageWidth * imageHeight;

	// calculer le nombre total d'octets à allouer en mémoire pour contenir l'image
	// (largeur x hauteur x nombre de composantes de couleurs)
	imageSize = imagePixelCount * imageComponent;

	// allocation d'un espace mémoire pouvant contenir tous les pixels de l'image
	pixels = (GLubyte *) calloc(imageSize, sizeof(GLubyte));

	// lire le contenu du framebuffer actif et copier les pixels en mémoire RAM
	glReadPixels(0, 0, imageWidth, imageHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	// ouvrir un nouveau fichier image en mode écriture

	// écrire le contenu de l'image de la mémoire (RAM) vers le fichier

	// fermer le fichier image
}
