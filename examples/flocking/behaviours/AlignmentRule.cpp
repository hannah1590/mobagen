#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood

  Vector2f vel = boid->getVelocity();
  float alignmentRad = boid->getDetectionRadius();
  int count = 0;

  for(auto &iterator : neighborhood)
  {
    Vector2f temp = boid->getPosition() - iterator->getPosition();
    temp.x = pow(temp.x,2.0f);
    temp.y = pow(temp.y,2.0f);
    float tempSqrt = sqrt(temp.x + temp.y);

    if(tempSqrt <= alignmentRad)
    {
      averageVelocity += iterator->getVelocity();
      count++;
    }
  }

  averageVelocity += vel;

  averageVelocity /= count + 1;

  Vector2f temp = averageVelocity - vel;
  temp.x = pow(temp.x,2.0f);
  temp.y = pow(temp.y,2.0f);
  float tempSqrt = sqrt(temp.x + temp.y);

  if(tempSqrt != 0)
  {
    averageVelocity = (averageVelocity / tempSqrt) * tempSqrt;
  }
  else
  {
    averageVelocity.zero();
  }

  averageVelocity = Vector2f::normalized(averageVelocity);

  return averageVelocity;
}