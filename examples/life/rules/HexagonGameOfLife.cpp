//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"

void HexagonGameOfLife::Step(World& world) {
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
int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  int size = world.SideSize();
  int count = 0;

  // right/left
  if(point.x + 1 < size && world.Get(Point2D(point.x + 1, point.y))) // right
    count++;
  if(point.x - 1 >= 0 && world.Get(Point2D(point.x - 1, point.y))) // left
    count++;

  // upright
  if(point.y - 1 >= 0 && point.y % 2 == 0 && world.Get(Point2D(point.x, point.y - 1)))
    count++;
  else if(point.x + 1 < size && point.y - 1 >= 0 && point.y % 2 == 1 && world.Get(Point2D(point.x + 1, point.y - 1)))
    count++;

  // upleft
  if(point.x - 1 >= 0 && point.y >= 0 && point.y % 2 == 0 && world.Get(Point2D(point.x - 1, point.y - 1)))
    count++;
  else if(point.y - 1 >= 0 && point.y % 2 == 1 && world.Get(Point2D(point.x, point.y - 1)))
    count++;

  // downright
  if(point.y + 1 < size && point.y % 2 == 0 && world.Get(Point2D(point.x, point.y + 1)))
    count++;
  else if(point.x + 1 < size && point.y + 1 < size && point.y % 2 == 1 && world.Get(Point2D(point.x + 1, point.y + 1)))
    count++;

  // downleft
  if(point.x - 1 >= 0 && point.y + 1 < size && point.y % 2 == 0 && world.Get(Point2D(point.x - 1, point.y + 1)))
    count++;
  else if(point.y + 1 < size && point.y % 2 == 1 && world.Get(Point2D(point.x, point.y + 1)))
    count++;

  // on same row in continuous world
  if (point.x + 1 >= size && world.Get(Point2D(0, point.y))) // right
    count++;
  if (point.x - 1 < 0 && world.Get(Point2D(size - 1, point.y))) // left
    count++;

  // upright continuous
  if(point.x + 1 >= size && point.y - 1 >= 0 && world.Get(Point2D(0, point.y - 1)))
    count++;
  else if(point.x + 1 < size && point.y - 1 < 0 && world.Get(Point2D(point.x + 1, size - 1)))
    count++;
  else if(point.x + 1 >= size && point.y  - 1 < 0 && world.Get(Point2D(0, size - 1)))
    count++;

  // upleft continuous
  if(point.x - 1 < 0 && point.y - 1 >= 0 && world.Get(Point2D(size - 1, point.y - 1)))
    count++;
  else if(point.x - 1 >= 0 && point.y - 1 < 0 && world.Get(Point2D(point.x - 1, size - 1)))
    count++;
  else if(point.x - 1 < 0 && point.y - 1 < 0 && world.Get(Point2D(size - 1, size - 1)))
    count++;

  // downright continuous
  if(point.x + 1 >= size && point.y + 1 < size && world.Get(Point2D(0, point.y + 1)))
    count++;
  else if(point.x + 1 < size && point.y + 1 >= size && world.Get(Point2D(point.x + 1, 0)))
    count++;
  else if(point.x + 1 >= size && point.y + 1 >= size && world.Get(Point2D(0, 0)))
    count++;

  // downleft continuous
  if(point.x - 1 < 0 && point.y + 1 < size && world.Get(Point2D(size - 1, point.y + 1)))
    count++;
  else if(point.x - 1 >= 0 && point.y + 1 >= size && world.Get(Point2D(point.x - 1, 0)))
    count++;
  else if(point.x - 1 < 0 && point.y + 1 >= size && world.Get(Point2D(size - 1, 0)))
    count++;

  return count;
}
