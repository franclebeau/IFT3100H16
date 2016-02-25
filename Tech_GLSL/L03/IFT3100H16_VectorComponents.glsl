// IFT3100H16_VectorComponents.glsl
// Exemples d’accès aux composantes d’un vecteur en GLSL.

vec3 v = vec3(1.0, 2.0, 3.0);

float component;

component = v.x;  // component = {1.0}
component = v.y;  // component = {2.0}
component = v.z;  // component = {3.0}

component = v[0]; // component = {1.0}
component = v[1]; // component = {2.0}
component = v[2]; // component = {3.0}

vec3 result;

result = v.xyz;   // result = {1.0, 2.0, 3.0}
result = v.zyx;   // result = {3.0, 2.0, 1.0}
result = v.xzy;   // result = {1.0, 3.0, 2.0}
result = v.yxz;   // result = {2.0, 1.0, 3.0}
result = v.xxx;   // result = {1.0, 1.0, 1.0}

//# identifiants possibles pour accès aux composantes
// {x, y, z, w} si transformation
// {r, g, b, a} si couleur
// {s, t, q, r} si texture
