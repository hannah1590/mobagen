#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

vector<pair<Point2D,string>> getValidNeighbors(Point2D pos, World* world, vector<pair<int, char>>& distances)
{
  vector<Point2D> neighbors = world->neighbors(pos);
  vector<pair<Point2D,string>> validNeighbors;

  for(int i = 0; i < neighbors.size(); i++)
  {
    if(!world->getContent(neighbors[i]) && neighbors[i] != pos) // checks if current neighbor is a free space
    {
      // adds the neighbor to the valid neighbors vector with a string providing the best directions to go in
      if(world->NE(pos) == neighbors[i])
        validNeighbors.emplace_back(neighbors[i], "NE");
      if(world->NW(pos) == neighbors[i])
        validNeighbors.emplace_back(neighbors[i], "NW");
      if(world->E(pos) == neighbors[i])
      {
        if(distances['N'] > distances['S'] && (!world->getContent(world->SE(pos)) || !world->getContent(world->SW(pos))))
          validNeighbors.emplace_back(neighbors[i], "ES");
        else
          validNeighbors.emplace_back(neighbors[i], "EN");
      }
      if(world->W(pos) == neighbors[i])
      {
        if(distances['N'] > distances['S'] && (!world->getContent(world->SE(pos)) || !world->getContent(world->SW(pos))))
          validNeighbors.emplace_back(neighbors[i], "WS");
        else
          validNeighbors.emplace_back(neighbors[i], "WN");
      }
        validNeighbors.emplace_back(neighbors[i], "SE");
      if(world->SW(pos) == neighbors[i])
        validNeighbors.emplace_back(neighbors[i], "SW");
    }
  }

  return validNeighbors;
}

std::vector<std::pair<int, char>> getDistances(Point2D current, World* w)
{
  int size = w->getWorldSideSize() / 2;
  std::vector<std::pair<int, char>> distances;
  distances.emplace_back(size + current.y, 'N'); // distance from north
  distances.emplace_back(size - current.y, 'S'); // distance from south
  distances.emplace_back(size - current.x, 'E'); // distance from east
  distances.emplace_back(size + current.x, 'W'); // distance from west
  // sort vector from smallest to biggest

  std::pair<int,char> holder;
  for(int i = 0; i < distances.size(); i++)
  {
    for(int j = i + 1; j < distances.size(); j++)
    {
      if(distances[i].first > distances[j].first)
      {
        holder = distances[i];
        distances[i] = distances[j];
        distances[j] = holder;
      }
    }
  }

  return distances;
}

// used to hold cell data
struct Node
{
  Point2D pos;
  int cost;
  int costToBorder;

  bool operator>(const Node& other) const
  {
    // used to order the priority queue by lowest cost
    return cost + costToBorder > other.cost + other.costToBorder;
  }
};

vector<Point2D> Agent::generatePath(World* w) {

  auto catPos = w->getCat();
  Point2D borderExit = Point2D::INFINITE;

  priority_queue<Node, vector<Node>, greater<Node>> frontier; // puts nodes in a queue from low cost to high cost
  unordered_set<Point2D> frontierSet;
  unordered_map<Point2D, Point2D> cameFrom;

  std::vector<std::pair<int, char>> initialDistance = getDistances(catPos,w);
  Node origin(catPos, 0,initialDistance[0].first);
  frontier.push(origin);
  cameFrom[catPos] = catPos;

  while (!frontier.empty())
  {
    Node current = frontier.top();
    frontier.pop();

    frontierSet.insert(current.pos);

    if (w->catWinsOnSpace(current.pos))
    {
      borderExit = current.pos;
      break;
    }

    std::vector<std::pair<int, char>> distances = getDistances(current.pos,w);
    vector<pair<Point2D,string>> neighbors = getValidNeighbors(current.pos,w,distances);

    for (auto it : neighbors)
    {
      if (frontierSet.find(it.first) == frontierSet.end()) // checks if neighbor is in frontierSet
      {
        int newCost = current.cost + 1; // costs 1 to move to next space

        int costToBorder;
        if(distances[it.second[0]].first > distances[it.second[1]].first) // check which direction of the neighbor is shortest
        {
          costToBorder = distances[it.second[0]].first; // gets shortest distance of neighbor from border
        }
        else
        {
          costToBorder = distances[it.second[1]].first;
        }

        // checks if neighbor is already in cameFrom and if the new cost is less than the current cost
        if (cameFrom.find(it.first) == cameFrom.end() || newCost + costToBorder < current.cost + current.costToBorder)
        {
          Node newPath(it.first, newCost, costToBorder);
          frontier.push(newPath);
          cameFrom[it.first] = current.pos;
        }
      }
    }
  }

  // no path was found
  if (borderExit == Point2D::INFINITE)
  {
    return vector<Point2D>();
  }

  // gets path from cameFrom
  vector<Point2D> path;
  Point2D current = borderExit;
  while (current != catPos)
  {
    path.push_back(current);
    current = cameFrom[current];
  }
  path.push_back(catPos);

  return path;
}