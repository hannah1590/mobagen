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
  std::string direction;
  auto holder = distances[0];

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
  
  direction = distances[0].second; // have cat go lowest distance direction
  for(int i = 1; i < distances.size(); i++)
  {
    if(distances[0].first == distances[i].first) // add directions that are equal to lowest distance direction
      direction += distances[i].second;
  }

  while(true) {
    auto rand = Random::Range(0, 5);
    switch (rand) {
      case 0:
        // only moves
        if (!world->getContent(World::NE(pos)) && (direction.contains('N') || (!direction.contains('E') && direction.contains('N')))) {
          if(world->catCanMoveToPosition(World::NE(pos)))
            return World::NE(pos);
          direction += "SW";
        }
        break;
      case 1:
        if (!world->getContent(World::NW(pos)) && (direction.contains('N') || (!direction.contains('W') && direction.contains('N')))) {
          if(world->catCanMoveToPosition(World::NW(pos)))
            return World::NW(pos);
          direction += "SE";
        }
        break;
      case 2:
        if (!world->getContent(World::E(pos)) && direction.contains('E')) {
          if(world->catCanMoveToPosition(World::E(pos)))
            return World::E(pos);
          direction += "NSW";
        }
        break;
      case 3:
        if (!world->getContent(World::W(pos)) && direction.contains('W')) {
          if(world->catCanMoveToPosition(World::W(pos)))
            return World::W(pos);
          direction += "NSE";
        }
        break;
      case 4:
        if (!world->getContent(World::SW(pos)) && (direction.contains('S') || (!direction.contains('W') && direction.contains('S')))) {
          if(world->catCanMoveToPosition(World::SW(pos)))
            return World::SW(pos);
          direction += "NE";
        }
        break;
      case 5:
        if (!world->getContent(World::SE(pos)) && (direction.contains('S') || (!direction.contains('E') && direction.contains('S')))) {
          if(world->catCanMoveToPosition(World::SE(pos)))
            return World::SE(pos);
          direction += "NW";
        }
        break;
      default:
        throw "random out of range";
    }
  }
}