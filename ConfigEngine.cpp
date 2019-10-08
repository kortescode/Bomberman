#include	<vector>
#include	<iostream>
#include	<cstdlib>
#include	<ctime>
#include	"ConfigEngine.hh"
#include      	"Case.hh"
#include      	"Bomb.hh"
#include      	"Player.hh"
#include	"Skybox.hh"

ConfigEngine::ConfigEngine(void)
  : players_(DefaultPlayers), nbEnemies_(DefaultEnemies), editor_(false),
    mapWidth_(DefaultMapWidth), mapHeight_(DefaultMapHeight), boxPercent_(DefaultBoxPercent),
    stage_(1), TotalScore_(0), xml(this), player1(NULL), player2(NULL), editor(NULL), skybox(NULL)
{
  srand(time(NULL));
}

ConfigEngine::~ConfigEngine(void)
{
  this->cleanConfig();
}

void		ConfigEngine::setTexture(void)
{
  this->texture_hardBox = gdl::Image::load("img/hard.jpg");
  this->texture_Box = gdl::Image::load("img/box.jpg");
}

void		ConfigEngine::setFloor(void)
{
  Map::Floor	*floor = new Map::Floor(this);

  floor->setSizeX(this->mapWidth_ * 400);
  floor->setSizeY(this->mapHeight_ * 400);
  this->listFloors.push_back(floor);
}

void		ConfigEngine::setWall(void)
{
  Map::Wall	*wall = new Map::Wall(this);

  wall->setSizeX(this->mapWidth_ * 400);
  wall->setSizeY(this->mapHeight_ * 400);
  this->listWalls.push_back(wall);
}

void		ConfigEngine::setHardBoxes(void)
{
  int		i = 1;
  int		j = 1;
  Case		tmp;

  i = 1;
  while (i < this->mapWidth_)
    {
      j = 1;
      while (j < this->mapHeight_)
        {
	  tmp = this->map.getCase(i, j);
	  Map::HardBox	*HardBox = new Map::HardBox(this, texture_hardBox);

	  HardBox->setX(tmp.getXmin());
	  HardBox->setZ(tmp.getYmin());
	  this->listHardBoxes.push_back(HardBox);
  	  this->map.changeStatu(i, j, WALL);
	  j += 2;
        }
      i += 2;
    }
}

void		ConfigEngine::setBox(void)
{
  int           i = 0;
  int           j = 0;
  int           z = 0;
  int		BoxMax = this->mapWidth_ * this->mapHeight_ - ((players_ + nbEnemies_) * 3) - ((this->mapHeight_ / 2) * (this->mapWidth_ / 2));
  Case          tmp;
  int		percentage = CalcPercent(this->boxPercent_, this->mapWidth_, this->mapHeight_);
  Map::Box	**box = new Map::Box*[percentage];

  for (int i = 0; i < percentage; i++)
    box[i] = new Map::Box(this, texture_Box);

  while (i < percentage && i < BoxMax)
    if (this->map.addBox(random() % this->mapWidth_, random() % this->mapHeight_) == true)
      i++;

  i = 0;
  while (i < percentage)
    box[i++]->setConfig(this);

  i = 0;
  while (i < this->mapWidth_)
    {
      j = 0;
      while (j < this->mapHeight_)
        {
          tmp = this->map.getCase(i, j);
          if (tmp.getType() == BOX)
            {
	      box[z]->setX(tmp.getXmin());
              box[z]->setZ(tmp.getYmin());
	      this->listBoxes.push_back(box[z]);
  	      ++z;
            }
          j++;
        }
      i++;
    }
}

void		ConfigEngine::setSkybox(void)
{
  Skybox	*skybox = new Skybox(this);

  if (this->mapWidth_ > this->mapHeight_)
    skybox->setSize(this->mapWidth_);
  else
    skybox->setSize(this->mapHeight_);
  this->skybox = skybox;
}

void		ConfigEngine::setPlayer(void)
{
  if (this->players_ == 1 || this->players_ == 2)
    {
      Model::Player *bomberman = new Model::Player(this, Model::PLAYER_ONE);

      bomberman->setX(200);
      bomberman->setY(200);
      this->map.addPlayer(0, 0);
      this->player1 = bomberman;
    }
  if (this->players_ == 2)
    {
      Model::Player *bomberman2 = new Model::Player(this, Model::PLAYER_TWO);

      bomberman2->setX((this->mapWidth_ - 1) * 400 + 200);
      bomberman2->setY((this->mapHeight_ - 1) * 400 + 200);
      this->map.addPlayer((this->mapWidth_ - 1), (this->mapHeight_ - 1));
      this->player2 = bomberman2;
    }
}

void		ConfigEngine::setEditor(void)
{
  if (this->editor_)
    this->editor = new Editor(this);;
}

void		ConfigEngine::setEnemies(void)
{
  Case          tmp;
  int	x = this->mapWidth_ - 1;
  int	y = 0;
  int	i = 0;
  int	max = 3;
  if (this->players_ == 2)
    max = 2;

  for (i = 0; i < max && i < nbEnemies_;)
    {
      Model::Player *enemy = new Model::Player(this, Model::BOT);
      enemy->setX((x * 400) + 200);
      enemy->setY((y * 400) + 200);
      this->map.addPlayer(x , y);
      this->listEnemies.push_back(enemy);
      i++;
      if (i == 1)
  	y = this->mapHeight_ - 1;
      x = 0;
      if (i == 2)
  	x = this->mapWidth_ - 1;
    }
  for ( ; i < nbEnemies_; i++)
    {
      y = random() % this->mapHeight_ - 1;
      x = random() % this->mapWidth_ - 1;
      tmp = this->map.getCase(x, y);
      Model::Player *enemy = new Model::Player(this, Model::BOT);
      enemy->setX((x * 400) + 200);
      enemy->setY((y * 400) + 200);
      this->map.addPlayer(x , y);
      this->listEnemies.push_back(enemy);
    }
}

void		ConfigEngine::setMap(void)
{
  int           i = -1;
  int           j = -1;
  int           x = -400;
  int           y = -400;
  int           z = 0;
  Case		*cases = new Case[(this->mapWidth_ + 2) * (this->mapHeight_ + 2)];

  while (i <= this->mapWidth_)
    {
      j = -1;
      y = -400;
      while (j <= this->mapHeight_)
        {
          cases[z].setXmin(x);
          cases[z].setXmax(x + 400);
          cases[z].setYmin(y);
          cases[z].setYmax(y + 400);
	  if (i == -1 || j == -1 || j ==  this->mapHeight_ || i == this->mapWidth_)
	    cases[z].setType(WALL);
          this->map.add(std::pair<int,int>(i,j), cases[z]);
          j++;
          y += 400;
          z++;
        }
      i++;
      x += 400;
    }
}

void		ConfigEngine::cleanConfig(void)
{
  std::list<AObject*>::iterator it;

  this->map.clean();

  for (it = this->listBoxes.begin(); it != this->listBoxes.end(); ++it)
    delete *it;
  this->listBoxes.clear();

  for (it = this->listBombs.begin(); it != this->listBombs.end(); ++it)
    delete *it;
  this->listBombs.clear();

  for (it = this->listFloors.begin() ; it != this->listFloors.end(); ++it)
    delete *it;
  this->listFloors.clear();

  for (it = this->listWalls.begin() ; it != this->listWalls.end(); ++it)
    delete *it;
  this->listWalls.clear();

  for (it = this->listHardBoxes.begin() ; it != this->listHardBoxes.end(); ++it)
    delete *it;
  this->listHardBoxes.clear();

  for (it = this->listBonus.begin() ; it != this->listBonus.end(); ++it)
    delete *it;
  this->listBonus.clear();

  if (this->skybox)
    {
      delete this->skybox;
      this->skybox = NULL;
    }

  if (this->player1)
    {
      delete this->player1;
      this->player1 = NULL;
    }
  if (this->player2)
    {
      delete this->player2;
      this->player2 = NULL;
    }

  if (this->editor)
    {
      delete this->editor;
      this->editor = NULL;
    }

  for (it = this->listEnemies.begin() ; it != this->listEnemies.end(); ++it)
    delete *it;
  this->listEnemies.clear();
}

int		ConfigEngine::getNbEnemies()
{
  std::list<AObject*>::iterator it;
  int				res = 0;

  for (it = this->listEnemies.begin() ; it != this->listEnemies.end(); ++it)
    if (dynamic_cast<Model::Player *>(*it)->isAlive() == true)
      res++;
  return (res);
}

int	       	ConfigEngine::getPlayers(void) const
{
  return (this->players_);
}

int    		ConfigEngine::getEnemies(void) const
{
  return (this->nbEnemies_);
}

int    		ConfigEngine::getMapWidth(void) const
{
  return (this->mapWidth_);
}

int    		ConfigEngine::getMapHeight(void) const
{
  return (this->mapHeight_);
}

int    		ConfigEngine::getBoxPercent(void) const
{
  return (this->boxPercent_);
}

int		ConfigEngine::getStage(void) const
{
  return (this->stage_);
}

bool		ConfigEngine::getEditor(void) const
{
  return (this->editor_);
}

void   		ConfigEngine::setPlayers(int players)
{
  this->players_ = players;
}

void   		ConfigEngine::setEnemies(int enemies)
{
  this->nbEnemies_ = enemies;
}

void   		ConfigEngine::setMapWidth(int mapWidth)
{
  this->mapWidth_ = mapWidth;
}

void   		ConfigEngine::setMapHeight(int mapHeight)
{
  this->mapHeight_ = mapHeight;
}

void   		ConfigEngine::setBoxPercent(int boxPercent)
{
  this->boxPercent_ = boxPercent;
}

void		ConfigEngine::initStage(void)
{
  this->stage_ = 1;
}

void		ConfigEngine::setStage(int stage)
{
  this->stage_ = stage;
}

void		ConfigEngine::nextStage(void)
{
  ++this->stage_;
  this->player1->updateScore();
  if (this->players_ == 2)
    this->player2->updateScore();
}

void		ConfigEngine::setDefaultConfig(void)
{
  this->editor_ = false;
  this->players_ = ConfigEngine::DefaultPlayers;
  this->nbEnemies_ = ConfigEngine::DefaultEnemies;
  this->mapWidth_ = ConfigEngine::DefaultMapWidth;
  this->mapHeight_ = ConfigEngine::DefaultMapHeight;
  this->boxPercent_ = ConfigEngine::DefaultBoxPercent;
}

void		ConfigEngine::setRandomConfig(void)
{
  this->editor_ = false;
  this->players_ = 1;
  this->nbEnemies_ = rand() % 15;
  if (this->nbEnemies_ == 0)
    this->nbEnemies_ = 1;
  if ((this->mapWidth_ = rand() % 40) % 2 == 0)
    ++this->mapWidth_;
  if ((this->mapHeight_ = rand() % 40) % 2 == 0)
    ++this->mapHeight_;
  this->boxPercent_ = rand() % 50;
}

void		ConfigEngine::setAdventureConfig(void)
{
  this->editor_ = false;
  this->players_ = 1;
  this->nbEnemies_ = 3 * this->stage_;
  this->mapWidth_ = 15;
  this->mapWidth_ = 15;
  this->boxPercent_ = 15 + (this->stage_ * 5);
}

void		ConfigEngine::setEditorConfig(void)
{
  this->editor_ = true;
  this->players_ = 0;
  this->nbEnemies_ = 0;
  this->boxPercent_ = 0;
}

void		ConfigEngine::setLoadMapConfig(int width, int height)
{
  this->editor_ = false;
  this->mapWidth_ = width;
  this->mapHeight_ = height;
  this->boxPercent_ = 0;
}

void		ConfigEngine::setConfig(void)
{
  this->cleanConfig();

  this->setTexture();
  this->setMap();
  this->setEnemies();
  this->setPlayer();
  this->setEditor();
  this->setHardBoxes();
  this->setBox();
  this->setWall();
  this->setFloor();
  this->setSkybox();

  std::list<AObject*>::iterator it;

  for (it = this->listHardBoxes.begin() ; it != this->listHardBoxes.end(); ++it)
    (*it)->initialize();
  for (it = this->listBoxes.begin() ; it != this->listBoxes.end(); ++it)
    (*it)->initialize();
  for (it = this->listBombs.begin() ; it != this->listBombs.end(); ++it)
    (*it)->initialize();
  for (it = this->listFloors.begin() ; it != this->listFloors.end(); ++it)
    (*it)->initialize();
  for (it = this->listWalls.begin() ; it != this->listWalls.end(); ++it)
    (*it)->initialize();
  for (it = this->listBonus.begin() ; it != this->listBonus.end(); ++it)
    (*it)->initialize();

  this->skybox->initialize();
  if (this->ModeGame == Modes::EditorGame)
    this->editor->initialize();
  else
    {
      this->player1->initialize();
      if (this->players_ == 2)
	this->player2->initialize();
    }
  this->AI = new AiEngine(this);

  for (it = this->listEnemies.begin(); it != this->listEnemies.end(); ++it)
    (*it)->initialize();
}

void		ConfigEngine::setTotalScore(int sc)
{
  this->TotalScore_ = sc;
}

int		ConfigEngine::getTotalScore() const
{
  return this->TotalScore_;
}
