#include "Cat.h"
#include "World.h"

Point2D Cat::Move(World* world) {
  std::vector<Point2D> path = generatePath(world);
  if(path.empty())
  {
    return world->getCat();
  }
  else
  {
    return path[path.size() - 2];
  }
}