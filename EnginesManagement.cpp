#include	<iostream>
#include	"IntroEngine.hh"
#include	"GameEngine.hh"
#include	"MenuEngine.hh"
#include	"EnginesManagement.hh"

EnginesManagement::EnginesManagement(void)
  : currentMode_(Modes::Intro)
{
}

EnginesManagement::~EnginesManagement(void)
{
}

void		EnginesManagement::initialize(void)
{
  this->initWindow();
}

void		EnginesManagement::update(void)
{
  this->updateClock();
  if (this->isDoUpdate())
    {
      this->updateKeyTab();
      if (this->currentMode_ == Modes::Intro)
	this->currentMode_ = this->updateIntro();
      else if (this->currentMode_ == Modes::Menu)
	this->currentMode_ = this->updateMenu();
      else if (this->currentMode_ == Modes::Game)
	this->currentMode_ = this->updateGame();
      else if (this->currentMode_ == Modes::Quit)
	this->unload();
      this->updateWindow(this->currentMode_);
      this->updateMusic(this->currentMode_);
    }
}

void		EnginesManagement::draw(void)
{
  if (this->canDraw() && this->isDoDraw())
  {
    if (this->currentMode_ == Modes::Intro)
      this->drawIntro();
    else if (this->currentMode_ == Modes::Menu)
      this->drawMenu();
    else if (this->currentMode_ == Modes::Game)
      this->drawGame();
    else if (this->currentMode_ == Modes::Quit)
      this->unload();
    }
}

void		EnginesManagement::unload(void)
{
  this->closeWindow();
}
