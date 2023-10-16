#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  std::vector<Point2D> path = generatePath(world);
  if(path.empty())
  {
    return world->getCat();
  }
  else
  {
    return path.front();
  }
}
