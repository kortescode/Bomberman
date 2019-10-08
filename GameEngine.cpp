#include	<iostream>
#include       	<list>
#include       	"AObject.hh"
#include       	"GameEngine.hh"
#include	"AIEngine.hh"
#include	"Modes.hh"

GameEngine::GameEngine(void)
{
}

GameEngine::~GameEngine(void)
{
}

Modes::Mode			GameEngine::updateFreeGame(void)
{
  if ((this->getPlayers() == 1 && this->player1->getStatus() != Model::NONE) ||
      (this->getPlayers() == 2 && this->player1->getStatus() != Model::NONE &&
       this->player2->getStatus() != Model::NONE))
    return (Modes::Menu);
  return (Modes::Game);
}

Modes::Mode			GameEngine::updateAdventureGame(void)
{
  if (this->player1->getStatus() != Model::NONE)
    {
      if (this->getStage() != 4 && this->player1->getStatus() == Model::WIN)
	{
	  this->setTotalScore(this->getTotalScore() + this->player1->getScore());
	  this->nextStage();
	  this->setAdventureConfig();
	  this->setConfig();
	  this->ModeGame = Modes::NextStage;
	}
      return (Modes::Menu);
    }
  /* Pour la soutenance */
  if (this->isPressed(InputEngine::CtrlGamer1))
    {
      this->player1->setStatus(Model::WIN);
      if (this->player1->getStatus() != Model::NONE)
	{
	  if (this->getStage() != 4 && this->player1->getStatus() == Model::WIN)
	    {
	      this->setTotalScore(this->getTotalScore() + this->player1->getScore());
	      this->nextStage();
	      this->setAdventureConfig();
	      this->setConfig();
	      this->ModeGame = Modes::NextStage;
	    }
	  return (Modes::Menu);
	}
    }
  return (Modes::Game);
}

Modes::Mode	GameEngine::updateGame(void)
{
  std::list<AObject*>::iterator it;
  if (this->isPressed(InputEngine::Pause))
    return (Modes::Menu);
  if (this->isPressed(InputEngine::UpCamera))
    this->setVerticalMove(-20);
  if (this->isPressed(InputEngine::DownCamera))
    this->setVerticalMove(20);

  if (this->ModeGame == Modes::AdventureGame)
    {
      if (this->updateAdventureGame() == Modes::Menu)
	return (Modes::Menu);
    }
  else if (this->ModeGame == Modes::FreeGame)
    {
      if (this->updateFreeGame() == Modes::Menu)
	return (Modes::Menu);
    }

  for (it = this->listBoxes.begin(); it != this->listBoxes.end(); ++it)
    (*it)->update();
  for (it = this->listBombs.begin(); it != this->listBombs.end(); ++it)
    (*it)->update();
  for (it = this->listFloors.begin(); it != this->listFloors.end(); ++it)
    (*it)->update();
  for (it = this->listWalls.begin(); it != this->listWalls.end(); ++it)
    (*it)->update();
  for (it = this->listHardBoxes.begin(); it != this->listHardBoxes.end(); ++it)
    (*it)->update();
  for (it = this->listBonus.begin(); it != this->listBonus.end(); ++it)
    (*it)->update();
  this->skybox->update();
  if (this->ModeGame == Modes::EditorGame)
    this->editor->update();
  else
    {
      this->player1->update();
      if (this->getPlayers() == 2)
	this->player2->update();
      AI->update();
      for (it = this->listEnemies.begin(); it != this->listEnemies.end(); ++it)
	(*it)->update();
    }

  return (Modes::Game);
}

bool			GameEngine::isInScope(int x, int y) const
{
  if (this->getGameMode() == TWOD)
    {
      if (this->getPlayers() != 0 &&
	  x >= (this->player1->getX() - this->getScope() - 400) &&
	  x <= (this->player1->getX() + this->getScope()) &&
	  y >= (this->player1->getZ() - this->getScope() - 400) &&
	  y <= (this->player1->getZ() + this->getScope()))
	return (true);
      else if (this->getEditor() &&
	       x >= (this->editor->getX() - this->getScope() - 400) &&
	       x <= (this->editor->getX() + this->getScope()) &&
	       y >= (this->editor->getZ() - this->getScope() - 400) &&
	       y <= (this->editor->getZ() + this->getScope()))
	return (true);
    }
    else if (this->getGameMode() == TREED)
      {
	if (this->getPlayers() != 0 &&
	    x >= (this->player1->getX() - (2.5 * this->getScope())) &&
	    x <= (this->player1->getX() + (2.5 * this->getScope())) &&
	    y >= (this->player1->getZ() - (2.5 * this->getScope())) &&
	    y <= (this->player1->getZ() + (2.5 * this->getScope())))
	  return (true);
	else if (this->getEditor() &&
		 x >= (this->editor->getX() - (2.5 * this->getScope())) &&
		 x <= (this->editor->getX() + (2.5 * this->getScope())) &&
		 y >= (this->editor->getZ() - (2.5 * this->getScope())) &&
		 y <= (this->editor->getZ() + (2.5 * this->getScope())))
	  return (true);
      }
  return (false);
}

void			GameEngine::drawGame(void)
{
  std::list<AObject*>::iterator it;

  for (it = this->listBoxes.begin(); it != this->listBoxes.end(); ++it)
    if (isInScope((*it)->getX(), (*it)->getZ()))
      (*it)->draw();
  for (it = this->listBombs.begin(); it != this->listBombs.end(); ++it)
    if (isInScope((*it)->getX(), (*it)->getZ()))
      (*it)->draw();
  for (it = this->listWalls.begin(); it != this->listWalls.end(); ++it)
    (*it)->draw();
  for (it = this->listFloors.begin(); it != this->listFloors.end(); ++it)
    (*it)->draw();
  for (it = this->listHardBoxes.begin(); it != this->listHardBoxes.end(); ++it)
    if (isInScope((*it)->getX(), (*it)->getZ()))
      (*it)->draw();
  for (it = this->listBonus.begin(); it != this->listBonus.end(); ++it)
    if (isInScope((*it)->getX(), (*it)->getZ()))
      (*it)->draw();

  this->skybox->draw();

  if (this->ModeGame == Modes::EditorGame)
    this->editor->draw();
  else
    {
      if (player1->isAlive() == true)
	this->player1->draw();
      if (this->getPlayers() == 2 && player2->isAlive() == true)
	this->player2->draw();
      for (it = this->listEnemies.begin(); it != this->listEnemies.end(); ++it)
	{
	  if (dynamic_cast<Model::Player *>(*it)->isAlive() == true)
	    if (isInScope((*it)->getX(), (*it)->getZ()))
	      (*it)->draw();
	}
    }
}
