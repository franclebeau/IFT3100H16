void IFT3100H16_VertexBufferCreate(int count)
{
	//préconditions:
	// - une structure de sommet avec une taille fixe pour chaque attribut
	// - nombre de sommets à stocker dans le buffer de géométrie
	// - données pour initialiser les sommets du buffer de géométrie
	//postconditions:
	// - un buffer de géométrie préinitialisé en mémoire GPU

	// calculer la taille de la structure commune à tous les sommets en nombre d'octets
	int vertexBufferStride = sizeof(VertexStruct);

	// calculer la taille du buffer à partir du nombre de sommets et de la taille de la structure de sommets
	int vertexBufferSize = count * vertexBufferStride;

	// déclarer un pointeur sur un espace mémoire du même type que la structure de sommets
	VertexStruct * vertexArray;

	// allouer un espace mémoire de taille suffisante pour contenir les données des attributs de tous les sommets
	vertexArray = (VertexStruct *) calloc(vertexBufferSize, vertexBufferStride);

	// assigner les données de chaque attribut pour chaque sommet
	for (int index = 0; index < count; index++)
	{
		vertexArray[index].position[0] = /* assigner données du maillage triangulaire */
		vertexArray[index].position[1] = /* assigner données du maillage triangulaire */
		vertexArray[index].position[2] = /* assigner données du maillage triangulaire */
		vertexArray[index].normal  [0] = /* assigner données du maillage triangulaire */
		vertexArray[index].normal  [1] = /* assigner données du maillage triangulaire */
		vertexArray[index].normal  [2] = /* assigner données du maillage triangulaire */
		vertexArray[index].texcoord[0] = /* assigner données du maillage triangulaire */
		vertexArray[index].texcoord[1] = /* assigner données du maillage triangulaire */
		vertexArray[index].color   [0] = /* assigner données du maillage triangulaire */
		vertexArray[index].color   [1] = /* assigner données du maillage triangulaire */
		vertexArray[index].color   [2] = /* assigner données du maillage triangulaire */
		vertexArray[index].color   [3] = /* assigner données du maillage triangulaire */
	}

	// déclarer un identifiant pour référencer un nouveau buffer de géométrie
	GLuint vertexBufferID;

	// création d'un nouveau buffer de géométrie dont l'identifiant unique sera retourné par OpenGL
	glGenBuffers(1, &vertexBufferID);

	// sélectionner le nouveau buffer de géométrie comme buffer de géométrie actif
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	// transférer le contenu du buffer de géométrie de la mémoire RAM vers la mémoire du GPU
	glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, vertexArray, GL_STATIC_DRAW);

	// déselectionner le buffer de géométrie actif
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// les données en mémoire RAM peuvent être supprimées si le buffer de géométrie est statique
	free(vertexArray);
}
