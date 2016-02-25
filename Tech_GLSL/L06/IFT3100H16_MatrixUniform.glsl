// IFT3100H16_MatrixUniform.glsl
// Exemples de déclaration de matrices sous forme d’attributs uniformes en GLSL.

// déclaration de matrices sous forme d'attributs uniformes
uniform mat4 matrixModel;
uniform mat4 matrixView;
uniform mat4 matrixProjection;
uniform mat4 matrixModelView;
uniform mat4 matrixViewProjection;
uniform mat4 matrixModelViewProjection;
uniform mat3 matrixNormal;
uniform mat3 matrixTexgen;

// différentes configurations des bloc d'attributs uniformes
layout(shared, column_major) uniform; // défaut
layout(shared, row_major)    uniform;
layout(packed, column_major) uniform;
layout(packed, row_major)    uniform;

// déclaration de matrices encapsulées dans un bloc d'attributs uniformes
uniform TransformBlock
{
	matrixModel;
	matrixView;
	matrixProjection;
};
