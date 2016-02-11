void IFT3100H16_Mesh()
{
	//préconditions:
	// - structures de sommet et de triangle
	// - données pour initialiser le maillage triangulaire
	//postconditions:
	// - une classe qui contient des triangles qui indexent des sommets

	// déclarer la structure interne des sommets du buffer
	typedef struct
	{
		GLfloat position[3]; //3 * 4 = 12 octets
		GLfloat normal  [3]; //3 * 4 = 12 octets
		GLfloat texcoord[2]; //2 * 4 = 8  octets
		GLubyte color   [4]; //4 * 1 = 4  octets
	}   VertexStruct;        //      = 36 octets

	// structure d'un sommet
	struct Vertex
	{
		// structure interne d'un sommet
		VertexStruct vs;
	};

	// structure d'un triangle
	struct Triangle
	{
		// pour stocker les indices des 3 sommets
		int vertexIndex[3];
	};

	// classe d'un maillage géométrique
	class Mesh
	{
		// tableau de sommets
		int countVertex;
		Vertex * arrayVertex;

		// tableau de triangles
		int countTriangle;
		Triangle * listTriangle;

		Mesh()
		{
			// allocation du tableau de sommets
			arrayVertex = (Vertex *) calloc(countVertex, sizeof(Vertex));

			// allocation du tableau de triangles
			arrayTriangle = (Triangle *) calloc(countTriangle, sizeof(Tirangle));

			// initialisation des données
			// ...
		}
	};
}
