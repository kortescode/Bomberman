#include <iostream>
#include <map>
#include "Map.hh"

namespace Map
{
  void	Map::add(std::pair<int, int> P, Case C)
  {
    _stock.insert( std::pair<std::pair<int, int>,Case>(P,C) );
  }

  void Map::addBomb(int x, int y)
  {
    std::map<std::pair<int, int>,Case>::iterator it;

    for (it= _stock.begin() ; it != _stock.end(); it++)
      {
    	if ((*it).first.first == x && (*it).first.second == y)
	  (*it).second.setType(BOMB);
      }
  }

  void Map::addPlayer(int x, int y)
  {
    std::map<std::pair<int, int>,Case>::iterator it;

    for (it= _stock.begin() ; it != _stock.end(); it++)
      {
    	if ((*it).first.first == x && (*it).first.second == y)
	  (*it).second.setType(PLAYER);
      }
  }

  void	Map::aff()
  {
    std::map<std::pair<int, int>,Case>::iterator it;
    int		i = -1;

    std::cout << "Stock contains:\n";
    for ( it= _stock.begin() ; it != _stock.end(); )
      {
	std::cout << (*it).second.getType() << " ";
	++it;
	if ((*it).first.first != i)
	  {
	    i++;
	    std::cout << std::endl;
	  }
      }
  }

  bool	Map::checkBoxPlayer(int x, int y)
  {
    if (getCase(x + 1, y).getType() == PLAYER)
      return false;
    if (getCase(x - 1, y).getType() == PLAYER)
      return false;
    if (getCase(x, y - 1).getType() == PLAYER)
      return false;
    if (getCase(x, y + 1).getType() == PLAYER)
      return false;
    return true;
  }

  bool	Map::addBox(int x, int y)
  {
    std::map<std::pair<int, int>,Case>::iterator it;

    if (checkBoxPlayer(x, y) == false)
      return false;
    for ( it= _stock.begin() ; it != _stock.end(); it++ )
      {
    	if ((*it).first.first == x && (*it).first.second == y)
	  {
	    if ((*it).second.getType() != FLOOR)
	      return false;
	    (*it).second.setType(BOX);
	  }
      }
    return true;
  }

  void	Map::changeStatu(int x, int y, CaseType t)
  {
    std::map<std::pair<int, int>,Case>::iterator it;

    for (it= _stock.begin() ; it != _stock.end(); it++)
      {
    	if ((*it).first.first == x && (*it).first.second == y)
	  (*it).second.setType(t);
      }
  }

  Case	&Map::getCase(int x, int y)
  {
    std::map<std::pair<int, int>,Case>::iterator it;

    for ( it= _stock.begin() ; it != _stock.end(); it++ )
      if ((*it).first.first == x && (*it).first.second == y)
	{
	  return (*it).second;
	}
    return (*it).second;
  }

  void	Map::clean()
  {
    _stock.clear();
  }
}
