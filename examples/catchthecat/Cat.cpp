#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  auto pos = world->getCat();
  int size = world->getWorldSideSize() / 2;
  std::vector<std::pair<int, char>> distances;
  distances.emplace_back(size + pos.y, 'N'); // distance from north
  distances.emplace_back(size - pos.y, 'S'); // distance from south
  distances.emplace_back(size - pos.x, 'E'); // distance from east
  distances.emplace_back(size + pos.x, 'W'); // distance from west
  std::pair<int,char> holder;

  // sort vector from smallest to biggest
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

  std::vector<Point2D> neighbors = world->neighbors(pos);
  std::vector<std::pair<Point2D,std::string>> validNeighbors;

  for(int i = 0; i < neighbors.size(); i++)
  {
    if(!world->getContent(neighbors[i]))
    {
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
      if(world->SE(pos) == neighbors[i])
        validNeighbors.emplace_back(neighbors[i], "SE");
      if(world->SW(pos) == neighbors[i])
        validNeighbors.emplace_back(neighbors[i], "SW");
    }
  }

  if(validNeighbors.size() == 1)
  {
    return validNeighbors.front().first;
  }
  else if(validNeighbors.empty())
    return pos;

  std::vector<std::pair<Point2D,std::string>> holderVector = validNeighbors;

  int index = 0;
  int rand;
  while(true)
  {
    if(index >= distances.size())
      return pos; // check

    if (!holderVector.empty()) {
      if(holderVector.size() > 1)
        rand = Random::Range(0, holderVector.size() - 1);
      else
        rand = 0;

      if(rand >= holderVector.size())
        rand = 0; // check

      if (distances[index].second == holderVector[rand].second[0] || distances[index].second == holderVector[rand].second[1]) {
        if(world->catCanMoveToPosition(holderVector[rand].first))
          return holderVector[rand].first;
      }
      else {
        std::swap(holderVector[rand], holderVector.back());
        holderVector.pop_back();
      }
    }
    else {
      holderVector = validNeighbors;
      index++;
    }
  }


/*
  auto pos = world->getCat();

  while(true) {
    auto rand = Random::Range(0,5);
    switch (rand) {
      case 0:
        if(!world->getContent(World::NE(pos))) return World::NE(pos);
      case 1:
        if(!world->getContent(World::NW(pos))) return World::NW(pos);
      case 2:
        if(!world->getContent(World::E(pos))) return World::E(pos);
      case 3:
        if(!world->getContent(World::W(pos))) return World::W(pos);
      case 4:
        if(!world->getContent(World::SE(pos))) return World::SE(pos);
      case 5:
        if(!world->getContent(World::SW(pos))) return World::SW(pos);
      default:
        throw "random out of range";
    }
  }
  */
}