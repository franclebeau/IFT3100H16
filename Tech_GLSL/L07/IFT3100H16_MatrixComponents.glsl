// IFT3100H16_MatrixComponents.glsl
// Exemples d’accès aux composantes d’une matrice en GLSL.

// déclaration d'une variable de type matrice 4 par 4
vec4 matrix4x4;

// exemples d'accès aux composantes de la matrice :
vec4 column = matrix4x4[0];
float m00 = matrix4x4[0][0];
float m11 = matrix4x4[1][1];
float m22 = matrix4x4[2][2];
float m33 = matrix4x4[3].w;
