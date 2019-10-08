#include	<iostream>
#include	"Brain.hh"

Brain::Brain()
  : _state(_SURVIVE),
    _action(_THINK)
{
  _destination.X = -1;
  _destination.Y = -1;
}

Brain::Brain(const Brain &other)
{
  this->setState(other.getState());
  this->setAction(other.getAction());
  this->setDestination(other.getDestination());
}

Brain & Brain::operator=(const Brain &other)
{
  this->setState(other.getState());
  this->setAction(other.getAction());
  this->setDestination(other.getDestination());
  return (*this);
}

Brain::~Brain()
{
}

void Brain::setState(State S)
{
  _state = S;
}

void Brain::setAction(Action A)
{
  _action = A;
}

void Brain::setDestination(posXY P, Action A)
{
  switch (A)
    {
    case _UP :
      _destination.X = P.X;
      _destination.Y = P.Y + 1;
      break;
    case _RIGHT :
      _destination.X = P.X - 1;
      _destination.Y = P.Y;
      break;
    case _LEFT :
      _destination.X = P.X + 1;
      _destination.Y = P.Y; 
      break;
    case _DOWN :
      _destination.X = P.X;
      _destination.Y = P.Y - 1;
      break;
    case _THINK :
      break;
    case _BOMB:
      break;
    }
}

void Brain::setDestination(posXY P)
{
  _destination.X = P.X;
  _destination.Y = P.Y;
}

State Brain::getState() const
{
  return (_state);
}
Action Brain::getAction() const
{
  return (_action);
}

posXY Brain::getDestination() const
{
  return (_destination);
}
