#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

bool RecursiveBacktrackerExample::Step(World* w) {
  int random[] = {72, 99,  56,  34, 43, 62,31, 4, 70, 22,
                  6, 65, 96, 71, 29, 9,98, 41, 90, 7,
                  30,3,  97, 49, 63, 88,47, 82, 91, 54,
                  74,2,  86, 14, 58, 35,89, 11, 10, 60,
                  28,21, 52, 50, 55, 69,76, 94, 23, 66,
                  15,57, 44, 18, 67, 5, 24, 33, 77, 53,
                  51,59, 20, 42, 80, 61, 1, 0, 38, 64,
                  45,92, 46, 79, 93, 95, 37, 40, 83, 13,
                  12,78, 75, 73, 84, 81, 8, 32, 27, 19,
                  87,85, 16, 25, 17, 68, 26, 39, 48, 36};

  Point2D current = randomStartPoint(w);
  Node node = w->GetNode(current);
  int index = 0;
  int randomVal;
  std::vector<Point2D> currentNeighbors;

  stack.emplace_back(current);
  visited[current.x][current.y] = true;

  while(!stack.empty())
  {
    current = Point2D(stack.back().x, stack.back().y);
    //std::cout << current.x << " " << current.y << " " << visited[current.x][current.y] << "\n";
    currentNeighbors = getVisitables(w, current);
    //std::cout << currentNeighbors.size() << "\n";
    //for(int i = 0; i < currentNeighbors.size(); i++)
    //{
    //  std::cout << currentNeighbors[i].x << " " << currentNeighbors[i].y << "\n";
    //}
    //std::cout << "\n";

    if(currentNeighbors.size() >= 1)
    {
      if(currentNeighbors.size() > 1)
      {
        randomVal = random[index];
        index++;
        if(index > 99)
        {
          index = 0;
        }

        randomVal = randomVal % currentNeighbors.size();
      }
      else
        randomVal = 0;

      if(currentNeighbors[randomVal].y - 1 == current.y)
      {
        node.SetNorth(true);
        visited[current.x][current.y - 1] = true;
        w->SetNodeColor(current, Color32(1,1,1,1));
      }
      else if(currentNeighbors[randomVal].x + 1 == current.x)
      {
        node.SetEast(true);
        visited[current.x + 1][current.y] = true;
        w->SetNodeColor(current, Color32(1,1,1,1));
      }
      else if(currentNeighbors[randomVal].y + 1 == current.y)
      {
        node.SetSouth(true);
        visited[current.x][current.y + 1] = true;
        w->SetNodeColor(current, Color32(1,1,1,1));
      }
      else if(currentNeighbors[randomVal].x - 1 == current.x)
      {
        node.SetWest(true);
        visited[current.x - 1][current.y] = true;
        w->SetNodeColor(current, Color32(1,1,1,1));
      }
      stack.emplace_back(currentNeighbors[randomVal]);
    }
    else
    {
      stack.pop_back();
    }

    currentNeighbors.clear();
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
  //Node node = w->GetNode(p);

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

/*
  if(p.y - 1 >= 0 && !node.GetWest())
  {
    visitables.emplace_back(Point2D(p.x,p.y - 1));
  }
  if(p.x + 1 < sideOver2 && !node.GetSouth())
  {
    visitables.emplace_back(Point2D(p.x + 1,p.y));
  }
  if(p.y + 1 < sideOver2 && !node.GetEast())
  {
    visitables.emplace_back(Point2D(p.x,p.y + 1));
  }
  if(p.x - 1 >= 0 && !node.GetNorth())
  {
    visitables.emplace_back(Point2D(p.x - 1,p.y));
  }
*/
  return visitables;
}
