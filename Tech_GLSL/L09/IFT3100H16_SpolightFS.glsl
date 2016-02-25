// IFT3100H16_SpotLightFS.glsl
// Exemple d'éclairage de type lumière projecteur, évalué au niveau d'un shader de fragments.

#version 400

// position sous forme d'attribut en entrée
in vec3 surfacePosition;

// normale sous forme d'attribut en entrée
in vec3 surfaceNormal;

// structure de données de la lumière de type spotlight
struct Spotlight
{
	vec4  position;  // position de la lumière
	vec3  direction; // direction de la lumière
	vec3  intensity; // facteurs d'intensité (ambiante, diffuse, spéculaire)
	float exponent;  // facteur d'atténuation
	float cutoff;    // angle maximale
};

// instance d'une lumière de type spotlight sous forme d'attribut uniforme
uniform Spotlight spotlight;

// structure de données d'un matériau
struct Material
{
	vec3  ambient;   // réflexion ambiente du matériau
	vec3  diffuse;   // réflexion diffuse du matériau
	vec3  specular;  // réflexion spéculaire du matériau
	float shininess; // facteur de brillance spéculaire du matériau
};

// instance d'un matériau sous forme d'attribut uniforme
uniform Material material;

// couleur du fragment sous forme d'attribut en sortie
out vec4 fragmentColor;

void main()
{
	//  calculer le vecteur L (point de la surface vers lumière)
	vec3 L = normalize(vec3(spotlight.position) - surfacePosition);

	// calculer l'angle entre le point de la surface et la direction de la lumière
	float angle = acos(dot(-L, spotlight.direction));

	// restreindre l'angle de diffusion à 90 degrés de la direction (hémisphère)
	float cutoff = radians(clamp(spotlight.cutoff, 0.0, 90.0));

	// calculer la réflexion ambiante
	vec3 ambient = spotlight.intensity * material.ambient;

	// valider si le point de la surface est à l'intérieur du cone de lumière.
	if(angle < cutoff)
	{
		// calculer le facteur de puissance de la lumière
		float attenuation = pow(dot(-L, spotlight.direction), spotlight.exponent);

		// calculer le vecteur V (point de la surface vers caméra)
		vec3 V = normalize(vec3(-surfacePosition));

		// calculer le vecteur H (direction à mi-chemin entre V et L)
		vec3 H = normalize(V + L);

		// illumination de type Blinn-Phong (réflexion ambiante, diffuse (N dot L) et spéculaire(N dot H))
		color = ambient +                                                       // réflexion ambiante
		attenuation * spotlight.intensity *                                     // impact de la lumière
		(
			material.diffuse  * max(dot(surfaceNormal, L), 0.0) +               // réflexion diffuse
			material.specular * pow(max(dot(surfaceNormal, H), 0.0), shininess) // réflexion spéculaire
		);
	}
	else
	{
		// retourner seulement la réflexion ambiante, sans réflexion diffuse ni spéculaire
		color = ambient;
	}

	// déterminer la couleur du fragment
	fragmentColor = vect4(color, 1.0)
}
