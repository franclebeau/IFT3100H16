void IFT3100H16_ImageImport()
{
	// préconditions :
	// - Une référence vers un fichier image existant (chemin d'accès local ou URL)
	// - ensemble des propriétés de l'image
	int imageWidth;
	int imageHeight;
	int imageComponent;
	int imagePixelCount;
	int imageSize;

	// postconditions :
	// - une texture créée à partir de l'image, chargée en mémoire vidéo (GPU), adéquatement configurée et prête à l'utilisation

	// déclarer un identifiant pour référencer la texture
	// (GLubyte est un 'unsigned int' de 32 bits)
	GLuint textureID;

	// déclarer un pointeur vers un espace mémoire qui servira à stocker les pixels de l'image
	// (GLubyte = 'unsigned byte' de 8 bits donc 256 niveaux de couleur par composante)
	GLubyte * pixels;

	// ouvrir le fichier image en mode lecture et en extraire les propriétés (largeur, hauteur, espace de couleur, nombre

	// Calculer le nombre total de pixels de l'image
	imagePixelCount = imageWidth * imageHeight;

	// calculer le nombre d'octets à allouer en mémoire pour contenir l'image
	// (largeur x hauteur x nombre de composantes de couleurs)
	imageSize = imagePixelCount * imageComponent;

	// allocation d'un espace mémoire pouvant contenir tous les pixels de l'image
	pixels = (GLubyte *) calloc(imageSize, sizeof(GLubyte));

	// lire le contenu de l'image et copier ses pixels en mémoire (RAM)

	// création d'un identifiant pour une nouvelle texture
	glGenTextures(1, &textureID);

	// sélectionner comme texture active celle à laquelle correspond l'identifiant
	glBindTexture(GL_TEXTURE_2D, textureID);

	// définir les paramètres d'enveloppement aux extrémités de la texture active
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// définir les paramètres d'interpolation des texels de la texture active entre les différents niveaux de mipmapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// copier les pixels de l'image (mémoire RAM) vers la texture active (mémoire GPU)
	glTexImage2D(
	GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
	0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	// générer les différents niveaux de mipmap de la texture
	glGenerateMipmap(GL_TEXTURE_2D);

	// la copie de l'image en mémoire RAM peut maintenant être supprimée car une copie existe maintenant en mémoire GPU
	free(pixels);
}
