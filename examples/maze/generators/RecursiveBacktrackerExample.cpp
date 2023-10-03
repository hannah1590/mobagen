#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

bool RecursiveBacktrackerExample::Step(World* w) {
  Point2D current;
  int randomVal;
  std::vector<Point2D> currentNeighbors;

  if(stack.empty())
  {
    current = randomStartPoint(w); // get start of stack
    srand (time(NULL));

    stack.emplace_back(current);
  }
  else
  {
    current = Point2D(stack.back().x, stack.back().y); // get last cell in stack
    if(stack.size() > 1)
    {
      w->SetNodeColor(stack.at(stack.size() - 2), Color32(100,0,0,1)); // set color of second to last node to red
    }
  }

  visited[current.x][current.y] = true;
  w->SetNodeColor(current, Color32(0,255,0,1));
  currentNeighbors = getVisitables(w, current);

  if(!currentNeighbors.empty())
  {
    if(currentNeighbors.size() > 1)
    {
      randomVal = rand() % currentNeighbors.size();
    }
    else
      randomVal = 0;

    if(currentNeighbors[randomVal].y == current.y - 1) // if north
    {
      w->SetNorth(current, false);
    }
    else if(currentNeighbors[randomVal].x == current.x + 1) // if east
    {
      w->SetEast(current, false);
    }
    else if(currentNeighbors[randomVal].y == current.y + 1) // if south
    {
      w->SetSouth(current, false);
    }
    else if(currentNeighbors[randomVal].x  == current.x - 1) // if west
    {
      w->SetWest(current, false);
    }

    stack.emplace_back(currentNeighbors[randomVal]);
  }
  else
  {
    w->SetNodeColor(current, Color32(0,0,0,1)); // set to black if backtracking
    stack.pop_back();
  }

  return true;
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
      if (!visited[x][y])
          return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  if(!visited[p.x][p.y - 1] && p.y - 1 >= -sideOver2)
  {
    visitables.emplace_back(Point2D(p.x,p.y - 1));
  }
  if(!visited[p.x + 1][p.y] && p.x + 1 <= sideOver2)
  {
    visitables.emplace_back(Point2D(p.x + 1,p.y));
  }
  if(!visited[p.x][p.y + 1] && p.y + 1 <= sideOver2)
  {
    visitables.emplace_back(Point2D(p.x,p.y + 1));
  }
  if(!visited[p.x - 1][p.y] && p.x - 1 >= -sideOver2)
  {
    visitables.emplace_back(Point2D(p.x - 1,p.y));
  }

  return visitables;
}
