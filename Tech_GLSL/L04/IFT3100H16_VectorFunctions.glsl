// IFT3100H16_VectorFunctions.glsl
// Exemples de fonctions applicables aux variables de type vecteur en GLSL.

vec3 normal; // normale du sommet transformée dans l'espace de la vue
vec3 light;  // vecteur normalisé en direction d'une lumière
vec3 view;   // vecteur normalisé en direction de la caméra

float specularColor; // couleur en ton de gris
float specularPower; // facteur de puissance spéculaire

float ndotl = dot(normal, light);
float rdotv = dot(view, (2.0 * normal) * ndotl - light);
float specular = specularColor * pow(rdotv, specularPower);
