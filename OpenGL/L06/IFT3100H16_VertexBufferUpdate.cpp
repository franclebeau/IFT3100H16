void IFT3100H16_VertexBufferUpdate(GLuint vbo, int count, int offset, VertexStruct * vertexArray)
{
	//préconditions:
	// - identifiant unique d'un buffer de géométrie
	// - données de sommet à mettre à jour
	//postconditions:
	// - mise à jour des valeurs des attributs d'un intervalle continu de sommets du buffer de géométrie

	// sélectionner le buffer de géométrie à mettre à jour comme buffer de géométrie actif
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// téléverser un intervalle continu de sommets de la mémoire RAM vers le buffer de géométrie en mémoire GPU
	glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(VertexStruct), count * sizeof(VertexStruct), vertexArray);
}
