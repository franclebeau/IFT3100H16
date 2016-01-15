// IFT3100H16_HelloTriangle
// Dessiner un triangle par seconde à des positions aléatoires dans la fenêtre d'affichage.

float vertex1_X; 
float vertex1_Y; 
float vertex2_X;
float vertex2_Y;
float vertex3_X;
float vertex3_Y;

float pointRadius;

// fonction invoquée à l'initialisation de l'application
void setup()
{
  size(512, 512);
  frameRate(1);
  noStroke();
  
  pointRadius = 16;
}

// fonction invoquée lors d'une mise à jour de la logique de l'application
void update()
{
  vertex1_X = random(0, width); 
  vertex1_Y = random(0, height); 
  vertex2_X = random(0, width);
  vertex2_Y = random(0, height);
  vertex3_X = random(0, width);
  vertex3_Y = random(0, height);
}

// fonction invoquée lors d'une mise à jour du rendu de la fenêtre de l'application
void draw()
{
  update();
  
  background(191);

  fill(255);

  triangle(
    vertex1_X, vertex1_Y,
    vertex2_X, vertex2_Y,
    vertex3_X, vertex3_Y);
  
  fill(0);
  
  ellipse(vertex1_X, vertex1_Y, pointRadius, pointRadius);
  ellipse(vertex2_X, vertex2_Y, pointRadius, pointRadius);
  ellipse(vertex3_X, vertex3_Y, pointRadius, pointRadius);
}