void IFT3100H16_VertexBufferBindFixedPipeline()
{
	//préconditions:
	// - identifiant unique d'un buffer de géométrie préinitialisé
	//postconditions:
	// - un buffer de géométrie prêt à l'utilisation où chaque attribut est adéquatement configuré

	// sélectionner le buffer de géométrie comme buffer de géométrie actif
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// assigner les pointeurs vers chaque attribut de la structure de sommets du buffer de géométrie
	glVertexPointer  ( 3, GL_FLOAT,         sizeof(VertexStruct), (void *) offsetof(VertexStruct, position));
	glNormalPointer  (    GL_FLOAT,         sizeof(VertexStruct), (void *) offsetof(VertexStruct, normal));
	glTexCoordPointer( 2, GL_FLOAT,         sizeof(VertexStruct), (void *) offsetof(VertexStruct, texcoord));
	glColorPointer   ( 4, GL_UNSIGNED_BYTE, sizeof(VertexStruct), (void *) offsetof(VertexStruct, color));

	// activer les pointeurs d'attributs
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}
