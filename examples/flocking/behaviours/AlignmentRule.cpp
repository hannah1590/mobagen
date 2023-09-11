#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood

  Vector2f vel = boid->getVelocity();
  float alignmentRad = boid->getDetectionRadius();
  float size = neighborhood.size();

  for(auto &iterator : neighborhood)
  {
    averageVelocity += iterator->getVelocity();
  }

  averageVelocity /= size;

  boid.

  Vector2f temp = vel - averageVelocity;
  temp.x = pow(temp.x,2.0f);
  temp.y = pow(temp.y,2.0f);
  float tempSqrt = sqrt(temp.x + temp.y);

  if(alignmentRad != 0)
  {
    averageVelocity = (averageVelocity / tempSqrt) * tempSqrt;
  }
  else
  {
    averageVelocity.zero();
  }

  return Vector2f::normalized(averageVelocity);
}