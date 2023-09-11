#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass

  Vector2f pCM; // position of center mass
  Vector2f pos = boid->getPosition();
  float cohesionRadius = boid->getDetectionRadius();
  float size = neighborhood.size();

  for(auto &iteration : neighborhood)
  {
    pCM += iteration->getPosition();
  }

  pCM /= size;

  Vector2f temp = pCM - pos;
  temp.x = pow(temp.x, 2.0f);
  temp.y = pow(temp.y, 2.0f);
  float tempSqrt = sqrt(temp.x + temp.y);

  if(tempSqrt <= cohesionRadius)
  {
    cohesionForce = (pCM - pos);// / cohesionRadius;
  }
  else
  {
    cohesionForce.zero();
  }

  return cohesionForce;
}