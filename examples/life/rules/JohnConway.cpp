#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  int size = world.SideSize();

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      Point2D point = Point2D(j, i);
      bool live = world.Get(point);
      int neighbors = CountNeighbors(world, point);

      if (neighbors < 2 || neighbors > 3)
        world.SetNext(point, false);
      else if (neighbors == 3 || (neighbors == 2 && live))
        world.SetNext(point, true);
      else
        world.SetNext(point, live);
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int size = world.SideSize();
  int count = 0;

  // next to each other
  if (point.y + 1 < size && world.Get(Point2D(point.x, point.y + 1)))
    count++;
  if (point.y - 1 >= 0 && world.Get(Point2D( point.x, point.y - 1)))
    count++;
  if (point.x + 1 < size && world.Get(Point2D( point.x + 1, point.y)))
    count++;
  if (point.x - 1 >= 0 && world.Get(Point2D(point.x - 1, point.y)))
    count++;

  // cells diagonal from each other
  if (point.y + 1 < size && point.x + 1 < size && world.Get(Point2D(point.x + 1, point.y + 1)))
    count++;
  if (point.y + 1 < size && point.x - 1 >= 0 && world.Get(Point2D(point.x - 1, point.y + 1)))
    count++;
  if (point.y - 1 >= 0 && point.x + 1 < size && world.Get(Point2D(point.x + 1, point.y - 1)))
    count++;
  if (point.y - 1 >= 0 && point.x - 1 >= 0 && world.Get(Point2D(point.x - 1, point.y - 1)))
    count++;

  // cells next to each other with the continuous map
  if (point.x + 1 >= size && world.Get(Point2D(0, point.y)))
    count++;
  if (point.x - 1 < 0 && world.Get(Point2D(size - 1, point.y)))
    count++;
  if (point.y + 1 >= size && world.Get(Point2D(point.x, 0)))
    count++;
  if (point.y - 1 < 0 && world.Get(Point2D(point.x, size - 1)))
    count++;

  // diagonally with continuous map off right/bottom
  if (point.x + 1 >= size && point.y + 1 < size && world.Get(Point2D(0, point.y + 1)))
    count++;
  if (point.x + 1 >= size && point.y - 1 >= 0 && world.Get(Point2D(0, point.y - 1)))
    count++;
  if (point.y + 1 >= size && point.x + 1 < size && world.Get(Point2D(point.x + 1, 0)))
    count++;
  if (point.y + 1 >= size && point.x - 1 >= 0 && world.Get(Point2D(point.x - 1, 0)))
    count++;

  // diagonally with continuous map off left/top
  if (point.x - 1 < 0 && point.y + 1 < size && world.Get(Point2D(size - 1, point.y + 1)))
    count++;
  if (point.x - 1 < 0 && point.y - 1 >= 0 && world.Get(Point2D(size - 1, point.y - 1)))
    count++;
  if (point.y - 1 < 0 && point.x + 1 < size && world.Get(Point2D(point.x + 1, size - 1)))
    count++;
  if (point.y - 1 < 0 && point.x - 1 >= 0 && world.Get(Point2D(point.x - 1, size - 1)))
    count++;

  // diagonally with continuous map off diagonals
  if (point.x + 1 >= size && point.y + 1 >= size && world.Get(Point2D(0, 0)))
    count++;
  if (point.x + 1 >= size && point.y - 1 < 0 && world.Get(Point2D(0, size - 1)))
    count++;
  if (point.x - 1 < 0 && point.y + 1 >= size && world.Get(Point2D(size - 1, 0)))
    count++;
  if (point.x - 1 < 0 && point.y - 1 < 0 && world.Get(Point2D(size - 1, size - 1)))
    count++;

  return count;
}
