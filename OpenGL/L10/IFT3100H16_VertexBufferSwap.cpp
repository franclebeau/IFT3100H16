void IFT3100H16_VertexBufferSwap(GLuint vboUpdate, GLuint vboDraw, GLuint vboAlpha, GLuint vboBeta)
{
	//préconditions:
	// - deux buffers de géométrie indépendants avec une structure identique mais des données distinctes
	//postconditions:
	// - alterne les buffers utilisés pour la mise à jour et l'affichage afin d'éviter de bloquer le pipeline de rendu

	if(IsReadyToSwap)
	{
		if(isInOrder)
		{
			vboUpdate = vboAlpha;
			vboDraw   = vboBeta;

			isInOrder = false;
		}
		else
		{
			vboUpdate = vboBeta;
			vboDraw   = vboAlpha;

			isInOrder = true;
		}

		IsReadyToSwap = false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboUpdate);

	// mise à jour du buffer de géométrie
	// ...

	glBindBuffer(GL_ARRAY_BUFFER, vboDraw);

	// rendre le contenu du buffer de géométrie
	// ...

	// inverser les buffers de géométrie lors du prochain frame
	IsReadyToSwap = true;
}
