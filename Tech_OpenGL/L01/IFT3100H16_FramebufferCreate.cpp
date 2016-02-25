void IFT3100H16_FramebufferCreate()
{
	//préconditions:
	// - une fenêtre d'affichage liée à un contexte de rendu
	// - résolution en largeur de la fenêtre d'affichage
	int viewportWidth  = 1920;
	// - résolution en hauteur de la fenêtre d'affichage
	int viewportHeight = 1080;

	//postconditions:
	// - un framebuffer prêt à l'utilisation, avec un buffer de rendu couleur et un buffer de profondeur
	// - identifiant du framebuffer
	GLuint framebuffer;
	// - identifiant du buffer de rendu
	GLuint renderbuffer;
	// - identifiant du buffer de profondeur
	GLuint depthbuffer;

	// générer un identifiant pour un nouveau framebuffer
	glGenFramebuffers(1, &framebuffer);

	// sélectionner le nouveau framebuffer comme framebuffer actif
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// générer un identifiant pour un nouveau buffer de rendu
	glGenRenderbuffers(1, &renderbuffer);

	// sélectionner le nouveau buffer de rendu comme buffer de rendu actif
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);

	// allouer l'espace mémoire du buffer de rendu
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, viewportWidth, viewportHeight);

	// attacher le buffer de rendu au framebuffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer);

	// générer un identifiant pour un nouveau buffer de profondeur
	glGenRenderbuffers(1, &depthbuffer);

	// sélectionner le nouveau buffer de profondeur comme buffer de rendu actif
	glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);

	// allouer l'espace mémoire du buffer de profondeur
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, viewportWidth, viewportHeight);

	// attacher le buffer de profondeur au framebuffer
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);
}
