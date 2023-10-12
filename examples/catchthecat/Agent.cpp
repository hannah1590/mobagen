#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;
vector<pair<Point2D,string>> getValidNeighbors(Point2D pos, World* world)
{
  vector<Point2D> neighbors = world->neighbors(pos);
  vector<pair<Point2D,string>> validNeighbors;

  for(int i = 0; i < neighbors.size(); i++)
  {
    if(!world->getContent(neighbors[i])) // checks if current neighbor is a free space
    {
      // adds the neighbor to the valid neighbors vector with a string providing the best directions to go in
      if(world->NE(pos) == neighbors[i])
        validNeighbors.emplace_back(neighbors[i], "NE");
      if(world->NW(pos) == neighbors[i])
        validNeighbors.emplace_back(neighbors[i], "NW");
      if(world->E(pos) == neighbors[i])
          validNeighbors.emplace_back(neighbors[i], "EE");
      if(world->W(pos) == neighbors[i])
          validNeighbors.emplace_back(neighbors[i], "WW");
      if(world->SE(pos) == neighbors[i])
        validNeighbors.emplace_back(neighbors[i], "SE");
      if(world->SW(pos) == neighbors[i])
        validNeighbors.emplace_back(neighbors[i], "SW");
    }
  }
}

std::vector<std::pair<int, char>> getCosts(Point2D current, World* w)
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

std::vector<Point2D> Agent::generatePath(World* w){
  unordered_map<Point2D, Point2D> cameFrom; // to build the flowfield and build the path
  queue<Point2D> frontier; // to store next ones to visit
  unordered_set<Point2D> frontierSet; // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited; // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE; // if at the end of the loop we dont find a border, we have to return random points

  visited.at(catPos) = true;
  vector<Point2D> path;

  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop

    Point2D current = frontier.front();
    frontier.pop();

    if(w->catWinsOnSpace(current))
      break;

    vector<pair<Point2D,string>> neighbors = getValidNeighbors(current, w);

    for(int i = 0; i < neighbors.size(); i++)
    {
      if(!visited.at(neighbors[i].first))
      {
        frontier.push(current);
        frontierSet.insert(current);
        visited.at(current) = true;
      }
    }
  }
    //Point2D current = frontier.front();
    //frontierSet.erase(current);
    //frontier.pop();
    //visited.emplace(current, true);

    //vector<Point2D> neighbors = w->neighbors(current);
    //for(int i = 0; i < neighbors.size(); i++)
    //{
   //   if(!w->getContent(neighbors[i]) && neighbors[i] != catPos && !frontierSet.contains(neighbors[i]))
    //  {
    //    cameFrom[neighbors[i]] = current;
    //    frontier.push(neighbors[i]);
   //     frontierSet.insert(neighbors[i]);
   //   }
   // }

    //if(!w->isValidPosition(current))
    //{
    //  while(!frontier.empty()) {
    //    frontier.pop();
    //    current = frontier.front();
    //    path.push_back(cameFrom.at(current));
    //  }
    //}
return path;
  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
}
