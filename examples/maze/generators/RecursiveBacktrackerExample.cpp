#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <stack>
bool RecursiveBacktrackerExample::Step(World* w) {
  Point2D current = Point2D(0,0);
  int amount = 0;

  stack.emplace_back(current);

  while(!stack.empty())
  {
    current = Point2D(stack.cbegin()->x, stack.cbegin()->y);

    if(!w->GetNorth(current))
      amount++;
    if(!w->GetEast(current))
      amount++;
    if(!w->GetSouth(current))
      amount++;
    if(!w->GetWest(current))
      amount++;

    if(amount > 1)
    {

    }
  }
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}
Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  return visitables;
}
