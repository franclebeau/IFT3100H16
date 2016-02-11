void IFT3100H16_VertexBufferDraw(GLuint vbo, int start, int count, void * indices)
{
	//préconditions:
	// - identifiant unique d'un buffer de géométrie préinitialisé
	//postconditions:
	// - rendu graphique du contenu du buffer de géométrie

	// sélectionner le buffer de géométrie comme buffer de géométrie actif
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// voici différentes techniques pour rendre un buffer de géométrie:

	// 1. dessiner un ensemble de points (point sprite)
	glDrawArrays(GL_POINTS, start, count);

	// 2. dessiner un quad à partir de deux triangles connexes
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// 3. dessiner une série de triangles connexes
	glDrawArrays(GL_TRIANGLE_STRIP, start, count);

	// 4. dessiner un élément à partir d'un buffer d'indices
	glDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_SHORT, indices);
}
