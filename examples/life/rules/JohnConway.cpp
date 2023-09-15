#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {

}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int size = world.SideSize();

  bool live = world.Get(point);
  bool up;
  bool down;
  bool right;
  bool left;
  bool upRight;
  bool upLeft;
  bool downRight;
  bool downLeft;

  // currently done copying programming assignment where the map
  // started at the top left and increasing a number would move
  // the point right/down

  // up
  if(point.y + 1 < size)
     up = world.Get(Point2D(point.x,point.y + 1));
  else if(point.y + 1 >= size)
     up = world.Get(Point2D(0,point.y));

  // down
  if(point.y - 1 >= 0)
     down = world.Get(Point2D(point.x,point.y - 1));
  else if(point.y - 1 < 0)
     down = world.Get(Point2D(world.SideSize() - 1,point.y));

  // right
  if(point.x + 1 < size)
     right = world.Get(Point2D(point.x + 1,point.y));
  else if(point.x - 1 >= size)
     right = world.Get(Point2D(point.x, 0));

  // left
  if(point.x - 1 >= 0)
     left = world.Get(Point2D(point.x - 1,point.y));
  else if(point.x - 1 < 0)
     left = world.Get(Point2D(point.x,size - 1));

  // upRight
  if(point.x + 1 < size && point.y - 1 >= 0)
     upRight = world.Get(Point2D(point.x + 1,point.y - 1));

  // upLeft
  if(point.x - 1 >= 0 && point.y - 1 >= 0)
     upRight = world.Get(Point2D(point.x - 1,point.y - 1));

  // downRight
  if(point.x + 1 < size && point.y + 1 < size)
     upRight = world.Get(Point2D(point.x + 1,point.y + 1));

  // downLeft
  if(point.x - 1 >= 0 && point.y + 1 < size)
     upRight = world.Get(Point2D(point.x - 1,point.y + 1));
}
