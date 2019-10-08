#include		"IClock.hpp"
#include		"Game.hpp"
#include		"ClockEngine.hh"

ClockEngine::ClockEngine(void)
  : doUpdate_(false), doDraw_(false), loopTime_(0.01), timeClock_(0)
{
  this->gameClock_.reset();
  this->gameClock_.play();
}

ClockEngine::~ClockEngine(void)
{
}

void			ClockEngine::pauseClock(void)
{
  this->gameClock_.pause();
}

void			ClockEngine::resumeClock(void)
{
  this->gameClock_.play();
}

float			ClockEngine::getTotalTimeClock(void)
{
  return (this->gameClock_.getTotalGameTime());
}

void			ClockEngine::updateClock(void)
{
  static float		loopCurrentTime = 0;

  this->timeClock_ = this->gameClock_.getElapsedTime();
  loopCurrentTime += this->timeClock_;
  if (loopCurrentTime >= this->loopTime_)
    {
      loopCurrentTime = 0;
      this->doUpdate_ = true;
      this->doDraw_ = true;
    }
}

float			ClockEngine::getTimeClock(void)
{
  return (this->timeClock_);
}

const gdl::IClock&	ClockEngine::getClock(void) const
{
  return (this->gameClock_);
}

bool			ClockEngine::isDoUpdate(void)
{
  if (this->doUpdate_)
    {
      this->doUpdate_ = false;
      return (true);
    }
  return (false);
}

bool			ClockEngine::isDoDraw(void)
{
  if (this->doDraw_)
    {
      this->doDraw_ = false;
      return (true);
    }
  return (false);
}
