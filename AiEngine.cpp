#include	<iostream>
#include	"AIEngine.hh"

AiEngine::AiEngine(ConfigEngine *data)
  : _ID(0),
    _data(data),
    _updateTime(50),
    _reactionTime(50)
{
}

AiEngine::AiEngine(const AiEngine &other)
{
  this->setID(other.getID());
  this->setData(getData());
  this->setUpdateTime(other.getUpdateTime());
  this->setReactionTime(other.getReactionTime());
}

AiEngine & AiEngine::operator=(const AiEngine &other)
{
  this->setID(other.getID());
  this->setData(other.getData());
  this->setUpdateTime(other.getUpdateTime());
  this->setReactionTime(other.getReactionTime());
  return (*this);
}

AiEngine::~AiEngine()
{
}

void AiEngine::setID(int ID)
{
  this->_ID = ID;
}

void AiEngine::setData(ConfigEngine *D)
{
  this->_data = D;
}

void AiEngine::setUpdateTime(int T)
{
  this->_updateTime = T;
}

void AiEngine::setReactionTime(int R)
{
  this->_reactionTime = R;
}

int AiEngine::getID() const
{
  return (this->_ID);
}

int AiEngine::getUpdateTime() const
{
  return (this->_updateTime);
}

ConfigEngine* AiEngine::getData() const
{
  return (this->_data);
}

int AiEngine::getReactionTime() const
{
  return (this->_reactionTime);
}

void AiEngine::resetExplosionArea()
{
  if (!_explosionArea.empty())
    _explosionArea.erase(_explosionArea.begin(),
			 _explosionArea.end());
}

void AiEngine::resetUnitPosition()
{
  if (!_unitPosition.empty())
    _unitPosition.erase(_unitPosition.begin(),
			_unitPosition.end());
}

void AiEngine::update()
{
  int time;

  time = getUpdateTime();
  if (time >= getReactionTime())
    {
      updateExplosionArea();
      updateUnitPosition();
      setUpdateTime(0);
      updateBots();
    }
  setUpdateTime(getUpdateTime() + 1);
}

void AiEngine::updateExplosionArea()
{
  std::list<AObject*>::iterator i;

  resetExplosionArea();
  for (i = _data->listBombs.begin();
       i != _data->listBombs.end(); ++i)
    {
      calculateArea(posXY((*i)->getX()/400, (*i)->getZ()/400),
		    dynamic_cast<Model::Bomb*>(*i)->getPower());
    }
}

void AiEngine::updateUnitPosition()
{
  std::list<AObject*>::iterator i;
  posXY pos;

  resetUnitPosition();
  pos.X = _data->player1->getX()/400;
  pos.Y = _data->player1->getZ()/400;
  _unitPosition.push_back(pos);
  if (_data->getPlayers() == 2)
    {
      pos.X = _data->player2->getX()/400;
      pos.Y = _data->player2->getZ()/400;
      _unitPosition.push_back(pos);
    }
  for (i = _data->listEnemies.begin(); i != _data->listEnemies.end(); ++i)
    {
      pos.X = (*i)->getX()/400;
      pos.Y = (*i)->getZ()/400;
      _unitPosition.push_back(pos);
    }
}

void AiEngine::updateBots()
{
  std::list<AObject*>::iterator i;
  Model::Player	*bot;
  posXY pos;

  for (i = _data->listEnemies.begin(); i != _data->listEnemies.end(); ++i)
    {
      bot = dynamic_cast<Model::Player*>(*i);
      pos.X = (*i)->getX()/400;
      pos.Y = (*i)->getZ()/400;
      if (bot->brain.getAction() == _THINK
      	  && !isDifferentCase(pos, bot->brain.getDestination()))
      	{
      	  bot->setX(400 * pos.X + 200);
      	  bot->setY(400 * pos.Y + 200);
      	}
      bot->brain.setState(evalState(pos, (bot->getPower() - 1)/2));
      bot->brain.setAction(makePlan(pos, bot->brain.getState(),
				    bot->getCurrentCapacity(),
				    (bot->getPower() - 1)/2));
      bot->brain.setDestination(pos, bot->brain.getAction());
    }
}

posXY AiEngine::getSafeCase(int X, int Y)
{
  if ((Y - 1 >= 0) && isSafeCase(X, Y - 1))
    return posXY(X, Y - 1);
  if ((X - 1 >= 0) && isSafeCase(X - 1, Y))
    return posXY(X - 1, Y);
  if ((Y + 1 < _data->getMapHeight()) && isSafeCase(X, Y + 1))
    return posXY(X, Y + 1);
  if (X + 1 < _data->getMapWidth() && isSafeCase(X + 1, Y))  
    return posXY(X + 1, Y);
  return posXY(-1,-1);
}

posXY AiEngine::getCase(int X, int Y)
{
  if ((Y - 1 >= 0) && isFreeCase(X, Y - 1))
    return posXY(X, Y - 1);
  if ((X - 1 >= 0) && isFreeCase(X - 1, Y))
    return posXY(X - 1, Y);
  if ((Y + 1 < _data->getMapHeight()) && isFreeCase(X, Y + 1))
    return posXY(X, Y + 1);
  if (X + 1 < _data->getMapWidth() && isFreeCase(X + 1, Y))  
    return posXY(X + 1, Y);
  return posXY(-1, -1);
}

posXY AiEngine::getLeaveCase(int X, int Y)
{
  posXY		check;

  if ((Y - 1 >= 0) && isFreeCase(X, Y - 1))
    {
      check = getSafeCase(X, Y - 1);
      if (check.X != -1)
	return posXY(X, Y -1);
    }
  if ((X - 1 >= 0) && isFreeCase(X - 1, Y))
    {
      check = getSafeCase(X - 1, Y);
      if (check.X != -1)
	return posXY(X - 1, Y);
    }
  if ((Y + 1 < _data->getMapHeight()) && isFreeCase(X, Y + 1))
    {
      check = getSafeCase(X, Y + 1);
      if (check.X != -1)
	return posXY(X, Y + 1);
    }
  if (X + 1 < _data->getMapWidth() && isFreeCase(X + 1, Y))
    {
      check = getSafeCase(X + 1, Y);
      if (check.X != -1)
	return posXY(X + 1, Y);
    }
  return posXY(-1,-1);
}

bool AiEngine::isDangerousCase(int X, int Y)
{
  std::list<posXY>::iterator i;

  for (i = _explosionArea.begin(); i != _explosionArea.end(); ++i)
    if (i->X == X && i->Y == Y)
      return (true);
  return (false);
}

bool AiEngine::thereIsNoDanger(int X, int Y)
{
  std::list<posXY>::iterator i;

  for (i = _explosionArea.begin(); i != _explosionArea.end(); ++i)
    {
      if (((i->X == X) && (i->Y == Y - 1 || i->Y == Y + 1))
	  || (((i->Y == Y) && (i->X == X - 1 || i->X == X + 1))))
	return (false);
    }
  return (true);
}

bool AiEngine::thereIsBonusClose(int X, int Y)
{
  std::list<AObject*>::iterator i;

  for (i = _data->listBonus.begin();
       i != _data->listBonus.end(); ++i)
    {
      if (((*i)->getX()/400 == X && ((*i)->getZ()/400 == Y - 1
				     || (*i)->getZ()/400 == Y + 1))
	  || ((*i)->getZ()/400 == Y && ((*i)->getX()/400 == X - 1
					|| (*i)->getX()/400 == X + 1)))
	return (true);
    }
  return (false);
}

bool AiEngine::thereIsBoxClose(int X, int Y)
{
  std::list<AObject*>::iterator i;

  for (i = _data->listBoxes.begin();
       i != _data->listBoxes.end(); ++i)
    {
      if (((*i)->getX()/400 == X && ((*i)->getZ()/400 == Y - 1
				     || (*i)->getZ()/400 == Y + 1))
	  || ((*i)->getZ()/400 == Y && ((*i)->getX()/400 == X - 1
					|| (*i)->getX()/400 == X + 1)))
	return (true);
    }
  return (false);
}

bool AiEngine::thereIsBombAt(int X, int Y)
{
  std::list<AObject*>::iterator i;

  for (i = _data->listBombs.begin();
       i != _data->listBombs.end(); ++i)
    {
      if ((*i)->getX()/400 == X && (*i)->getZ()/400 == Y)
	return (true);
    }
  return (false);
}

bool AiEngine::thereIsUnit(int X, int Y)
{
  std::list<posXY>::iterator i;

  for (i = _unitPosition.begin(); i != _unitPosition.end(); ++i)
    {
      if (i->X == X && i->Y == Y)
	return (true);
    }
  return (false);
}

bool AiEngine::isTouch(int posX, int posY, int cmpX, int cmpY)
{
  if ((posX == cmpX && (posY == cmpY - 1 || posY == cmpY + 1))
      || ((posY == cmpY) && (posX == cmpX - 1 || posX == cmpX + 1)))
    return (true);
  return (false);
}

bool AiEngine::isTouch(posXY pos, posXY cmp)
{
  if ((pos.X == cmp.X && (pos.Y == cmp.Y - 1 || pos.Y == cmp.Y + 1))
      || ((pos.Y == cmp.Y) && (pos.X == cmp.X - 1 || pos.X == cmp.X + 1)))
    return (true);
  return (false);
}

bool AiEngine::isBox(int X, int Y)
{
  std::map<std::pair<int, int>, Case>::iterator i;

  for (i = _data->map._stock.begin();
       i != _data->map._stock.end(); ++i)
    if (i->first.first == X && i->first.second == Y)
      return i->second.getType() == BOX;
  return (false);
}

bool AiEngine::isSafeCase(int X, int Y)
{
  return isFreeCase(X, Y) && !isDangerousCase(X, Y);
}

bool AiEngine::thereIsEnemieClose(int X, int Y)
{
  std::list<posXY>::iterator i;
  
  for (i = _unitPosition.begin(); i != _unitPosition.end(); ++i)
    if (((i->X == X) && (i->Y == Y - 1 || i->Y == Y + 1))
	|| ((i->Y == Y) && (i->X == X - 1 || i->X == X + 1)))
      return (true);
  return (false);
}

bool AiEngine::isDifferentCase(posXY first, posXY second)
{
  if (first.X != second.X || first.Y != second.Y)
    return (true);
  return (false);
}

bool AiEngine::checkLongLine(posXY from, posXY to)
{
  posXY		tmp;

  tmp.X = from.X;
  tmp.Y = from.Y;
  if (tmp.Y > to.Y)
    {
      while (tmp.Y != to.Y)
	{
	  if (isDifferentCase(tmp, from) && isBox(tmp.X, tmp.Y))
	    return (false);
	  --tmp.Y;
	}
    }
  else
    {
      while (tmp.Y != to.Y)
	{
	  if (isDifferentCase(tmp, from) && isBox(tmp.X, tmp.Y))
	    return (false);
	  ++tmp.Y;
	}
    }
  return (true);
} 

bool AiEngine::checkLargLine(posXY from, posXY to)
{
  posXY		tmp;

  tmp.X = from.X;
  tmp.Y = from.Y;
  if (tmp.X > to.X)
    {
      while (tmp.X != to.X)
	{
	  if (isDifferentCase(tmp, from) && isBox(tmp.X, tmp.Y))
	    return (false);
	  --tmp.X;
	}
    }
  if (tmp.X < to.X)
    {
      while (tmp.X != to.X)
	{
	  if (isDifferentCase(tmp, from) && isBox(tmp.X, tmp.Y))
	    return (false);
	  ++tmp.X;
	}
    }
  return (true);
} 

bool AiEngine::thereIsNoBoxBetween(posXY pos, posXY enemiePos)
{
  Action dir;

  dir = calcDirection(pos, enemiePos);
  if (dir == _UP || dir == _DOWN)
    return (checkLongLine(pos, enemiePos));
  else if (dir == _LEFT || dir == _RIGHT)
    return (checkLargLine(pos, enemiePos));
  else
    return (true);
}

bool AiEngine::enemieInRange(int X, int Y, int R)
{
  std::list<posXY>::iterator i;
  posXY from, to;
  int it;
  
  from.X = X;
  from.Y = Y;
  for (i = _unitPosition.begin(); i != _unitPosition.end(); ++i)
    {
      it = R;
      if (it <= 0)
	it = 1;
      while (it != 0)
	{
	  if (((i->X == X) && (i->Y == Y - it || i->Y == Y + it))
	      || ((i->Y == Y) && (i->X == X - it || i->X == X + it)))
	    {
	      to.X = i->X;
	      to.Y = i->Y;
	      if (thereIsNoBoxBetween(from, to))
		return (true);
	    }
	  --it;
	}
    }
  return (false);
}

void AiEngine::doDownCalc(posXY pos, int power)
{
  int i = power;

  while (i != 0)
    {
      if ((pos.Y - 1) >= 0)
	{
	  --pos.Y;
	  _explosionArea.push_back(pos);
	}
      --i;
    }
}

void AiEngine::doLeftCalc(posXY pos, int power)
{
  int i = power;

  while (i != 0)
    {
      if ((pos.X + 1) < _data->getMapWidth())
	{
	  ++pos.X;
	  _explosionArea.push_back(pos);
	}
      --i;
    }
}

void AiEngine::doUpCalc(posXY pos, int power)
{
  int i = power;

  while (i != 0)
    {
      if ((pos.Y + 1) < _data->getMapHeight())
	{
	  ++pos.Y;
	  _explosionArea.push_back(pos);
	}
      --i;
    }
}

void AiEngine::doRightCalc(posXY pos, int power)
{
  int i = power;

  while (i != 0)
    {
      if ((pos.X - 1) >= 0)
	{
	  --pos.X;
	  _explosionArea.push_back(pos);
	}
      --i;
    }
}

void AiEngine::calculateArea(posXY pos, int power)
{
  int P = (power - 1)/2;
  
  _explosionArea.push_back(pos);
  doUpCalc(pos, P);
  doLeftCalc(pos, P);
  doRightCalc(pos, P);
  doDownCalc(pos, P);
}

void AiEngine::affExplosionArea()
{
  std::list<posXY>::iterator i;

  std::cout << "==========\nEXPLOSION AREA:" << std::endl;
  for (i = _explosionArea.begin();
       i != _explosionArea.end(); ++i)
    std::cout << "--> X[" << i->X << "] Y[" << i->Y << "]." << std::endl;
  std::cout << "==========" << std::endl;
}

void AiEngine::affUnitPosition()
{
  std::list<posXY>::iterator i;

  std::cout << "==========\nUNIT POSITION:" << std::endl;
  for (i = _unitPosition.begin();
       i != _unitPosition.end(); ++i)
    std::cout << "--> X[" << i->X << "] Y[" << i->Y << "]." << std::endl;
  std::cout << "==========" << std::endl;
}

void AiEngine::affPos(posXY pos)
{
  std::cout << "X[" << pos.X << "]Y[" << pos.Y << "]." << std::endl;
}

void AiEngine::affPos(int X, int Y)
{
  std::cout << "X[" << X << "]Y[" << Y << "]." << std::endl;
}

void AiEngine::affState(State S)
{
  switch (S)
    {
    case (_ATTACK):
      std::cout << "_ATTACK" << std::endl;
      break;
    case (_SURVIVE):
      std::cout << "_SURVIVE" << std::endl;
      break;
    case (_EXPLORE):
      std::cout << "_EXPLORE" << std::endl;
      break;
    case (_COLLECT):
      std::cout << "_COLLECT" << std::endl;
      break;
    }
}

bool AiEngine::isFreeCase(int X, int Y)
{
  std::map<std::pair<int, int>, Case>::iterator i;
  CaseType type;

  for (i = _data->map._stock.begin();
       i != _data->map._stock.end(); ++i)
    {
      if (i->first.first == X && i->first.second == Y)
	{
	  type = i->second.getType();
	  if ((type == FLOOR || type == BONUS || type == FIRE_BONUS)
	      && !thereIsUnit(i->first.first, i->first.second))
	    return (true);
	  return (false);
	}
    }
  return (false);
}


State AiEngine::evalState(posXY pos, int attackRange)
{
  if (isDangerousCase(pos.X, pos.Y)
      || !thereIsNoDanger(pos.X, pos.Y))
    return (_SURVIVE);
  if (enemieInRange(pos.X, pos.Y, attackRange))
    return (_ATTACK);
  if (thereIsBonusClose(pos.X, pos.Y))
    return (_COLLECT);
  return (_EXPLORE);
}

Action AiEngine::makePlan(posXY actPos, State State,
			  bool haveBomb, int power)
{
  switch (State)
    {
    case (_SURVIVE):
      return (survive(actPos));
    case (_ATTACK):
      return (attack(actPos, haveBomb, power));
    case (_COLLECT):
      return (collectBonus(actPos));
    case (_EXPLORE):
      return (explore(actPos, haveBomb));
    }
   return (_THINK);
}

Action AiEngine::survive(posXY actPos)
{
  posXY newPos;

  if (isDangerousCase(actPos.X, actPos.Y))
    {
      newPos = getSafeCase(actPos.X, actPos.Y);
      if (newPos.X == -1 && newPos.Y == -1)
	{
	  if (!isDangerousCase(actPos.X , actPos.Y))
	    return (_THINK);
	  else
	    {
	      newPos = getLeaveCase(actPos.X, actPos.Y);
	      if (newPos.X == -1)
		return (_THINK);
	      return (calcDirection(actPos, newPos));
	    }
	}
      return (calcDirection(actPos, newPos));
    }
  else
    return (_THINK);
}

Action AiEngine::attack(posXY actPos, bool haveBomb, int power)
{
  posXY newPos;

  if (haveBomb && enemieInRange(actPos.X, actPos.Y, power)
      && !thereIsBombAt(actPos.X, actPos.Y) && newPos.X != -1)
    return (_BOMB);
  newPos = getSafeCase(actPos.X, actPos.Y);
  if (newPos.X != -1)
    return (calcDirection(actPos, newPos));
  return (_THINK);
}

Action	AiEngine::collectBonus(posXY playerPos)
{
  std::list<AObject*>::iterator i;
  posXY bonusPos;

  for (i = _data->listBonus.begin(); i != _data->listBonus.end(); ++i)
    {
      bonusPos.X = (*i)->getX()/400;
      bonusPos.Y = (*i)->getZ()/400;
      if (isTouch(playerPos, bonusPos)
	  && isFreeCase(bonusPos.X, bonusPos.Y))
	return (calcDirection(playerPos, bonusPos));
    }
  return (_THINK);
}

Action AiEngine::explore(posXY actPos, bool haveBomb)
{
  posXY newPos;

  if (thereIsNoDanger(actPos.X, actPos.Y))
    {
      newPos = getCase(actPos.X, actPos.Y);
      if (haveBomb && thereIsBoxClose(actPos.X, actPos.Y)
	  && newPos.X != -1)
	return (_BOMB);
      else if (thereIsBonusClose(actPos.X, actPos.Y))
	return (collectBonus(actPos));
      else
	return (getRandMove());
    }
  else
    return (_THINK);
}

Action  AiEngine::getRandMove()
{
  int result = random() % 4;
  switch (result)
    {
    case 0:
      return (_UP);
    case 1:
      return (_RIGHT);
    case 2:
      return (_DOWN);
    case 3:
      return (_LEFT);
    }
  return (_THINK);
}

Action AiEngine::calcDirection(posXY actPos, posXY newPos)
{
  if (actPos.X == newPos.X && actPos.Y - 1 == newPos.Y)
      return (_DOWN);
  if (actPos.X == newPos.X && actPos.Y + 1 ==  newPos.Y)
      return (_UP);
  if (actPos.X - 1 == newPos.X && actPos.Y == newPos.Y)
      return (_RIGHT);
  if (actPos.X + 1 == newPos.X && actPos.Y == newPos.Y)
      return (_LEFT);
  return (_THINK);
}
