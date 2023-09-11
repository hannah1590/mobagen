#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;
  //
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  //    if (!neighborhood.empty()) {
  //        Vector2f position = boid->transform.position;
  //        int countCloseFlockmates = 0;
  //        // todo: find and apply force only on the closest mates
  //    }
  float separationRadius = boid->getDetectionRadius();

  if(!neighborhood.empty())
  {
    Vector2f position = boid->transform.position;
    int count = 0;

    Vector2f temp;
    float tempSqrt;

    for(auto &iteration : neighborhood)
    {
      temp = position - iteration->getPosition();
      temp.x = pow(temp.x,2.0f);
      temp.y = pow(temp.y,2.0f);
      tempSqrt = sqrt(temp.x + temp.y);

      if(0 < tempSqrt && tempSqrt <= separationRadius)
      {
        separatingForce += ((position - iteration->getPosition()) / tempSqrt) / tempSqrt;
      }
    }

    tempSqrt = sqrt(pow(separatingForce.x,2.0f) + pow(separatingForce.y,2.0f));

    if(tempSqrt <= desiredMinimalDistance){}
    else
    {
        separatingForce = (separatingForce / tempSqrt) * desiredMinimalDistance;
    }
  }

  separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
