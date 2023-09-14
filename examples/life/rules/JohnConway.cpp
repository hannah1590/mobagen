#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {

}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int size = world.SideSize();

  bool live = world.Get(point);
  bool up;

  if(point.y + 1 < world.SideSize())
     up = world.Get(Point2D(point.x,point.y + 1));
  else if(point.y + 1 >= world.SideSize())
  {
     up = world.Get(Point2D(point.x,point.y));
  }
}
