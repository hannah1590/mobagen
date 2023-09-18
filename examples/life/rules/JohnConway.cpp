#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {

}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int size = world.SideSize();

  bool live = world.Get(point);

  int count;

  // currently done copying programming assignment where the map
  // started at the top left and increasing a number would move
  // the point right/down

  // cells directly next to each other
  if (point.y + 1 < size && world.Get(Point2D(point.y + 1,point.x)))
    count++;
  if (point.y - 1 >= 0 && world.Get(Point2D(point.y - 1, point.x)))
    count++;
  if (point.x + 1 < size && world.Get(Point2D(point.y, point.x + 1)))
    count++;
  if (point.x - 1 >= 0 && world.Get(Point2D(point.y, point.x - 1)))
    count++;

  // cells diagonal from each other
  if (point.y + 1 < size && point.x + 1 < size && world.Get(Point2D(point.y + 1, point.x + 1)))
    count++;
  if (point.y + 1 < size && point.x - 1 >= 0 && world.Get(Point2D(point.y + 1, point.x - 1)))
    count++;
  if (point.y - 1 >= 0 && point.x + 1 < size && world.Get(Point2D(point.y - 1, point.x + 1)))
    count++;
  if (point.y - 1 >= 0 && point.x - 1 >= 0 && world.Get(Point2D(point.y - 1, point.x - 1)))
    count++;

  // cells next to each other with the continuous map
  if (point.x + 1 >= size && world.Get(Point2D(point.y, 0)))
    count++;
  if (point.x - 1 < 0 && world.Get(Point2D(point.y, size - 1)))
    count++;
  if (point.y + 1 >= size && world.Get(Point2D(0, point.x)))
    count++;
  if (point.y - 1 < 0 && world.Get(Point2D(size - 1, point.x)))
    count++;

  // diagonally with continuous map off right/bottom
  if (point.x + 1 >= size && point.y + 1 < size && world.Get(Point2D(point.y + 1, 0)))
    count++;
  if (point.x + 1 >= size && point.y - 1 >= 0 && world.Get(Point2D(point.y - 1, 0)))
    count++;
  if (point.y + 1 >= size && point.x + 1 < size && world.Get(Point2D(0, point.x + 1)))
    count++;
  if (point.y + 1 >= size && point.x - 1 >= 0 && world.Get(Point2D(0, point.x - 1)))
    count++;

  // diagonally with continuous map off left/top
  if (point.x - 1 < 0 && point.y + 1 < size && world.Get(Point2D(point.y + 1, size - 1)))
    count++;
  if (point.x - 1 < 0 && point.y - 1 >= 0 && world.Get(Point2D(point.y - 1, size - 1)))
    count++;
  if (point.y - 1 < 0 && point.x + 1 < size && world.Get(Point2D(size - 1, point.x + 1)))
    count++;
  if (point.y - 1 < 0 && point.x - 1 >= 0 && world.Get(Point2D(size - 1, point.x - 1)))
    count++;

  // diagonally with continuous map off diagonals
  if (point.x + 1 >= size && point.y + 1 >= size && world.Get(Point2D(0, 0)))
    count++;
  if (point.x + 1 >= size && point.y - 1 < 0 && world.Get(Point2D(size - 1, 0)))
    count++;
  if (point.x - 1 < 0 && point.y + 1 >= size && world.Get(Point2D(0, size - 1)))
    count++;
  if (point.x - 1 < 0 && point.y - 1 < 0 && world.Get(Point2D(size - 1, size - 1)))
    count++;

  return count;
}
