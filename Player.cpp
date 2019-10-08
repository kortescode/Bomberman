#include	<iostream>
#include	"Player.hh"
#include	"ConfigEngine.hh"
#include	"Bomb.hh"
#include	"Fire.hh"
#include	"Bonus.hh"

namespace	Model
{
  const t_side	tabMove[] =
    {
      {UP, &Player::goUp},
      {DOWN, &Player::goDown},
      {LEFT, &Player::goLeft},
      {RIGHT, &Player::goRight}
    };

  Player::Player(ConfigEngine *A, PlayerType type)
    : AObject(A), currentCapacity_(1), capacity_(1), power_(3), speed_(800), live_(true), score_(0), status_(Model::NONE), type_(type)
  {
    this->live_ = true;
    this->oldCase_ = this->A->map.getCase((this->getX() / 400), (this->getZ() / 400));
  }

  Player::~Player(void)
  {
    //delete this->model_;
  }

  void		Player::initialize(void)
  {
    this->model_ = gdl::Model::load("libgdl_gl/assets/marvin.fbx");
    this->modelBomb_ = gdl::Model::load("libgdl_gl/assets/bomb.fbx");
    this->model_.cut_animation(this->model_, "Take 001", 35, 55, "Running");
    if (this->type_ == PLAYER_ONE)
      this->model_.set_default_model_color(gdl::Color(0, 0, 255));
    else if (this->type_ == PLAYER_TWO)
      this->model_.set_default_model_color(gdl::Color(255, 0, 0));
    else
      this->model_.set_default_model_color(getNewColor());
  }

  void		Player::update(void)
  {
    // DEBUG
    if (A->isPressed(InputEngine::CtrlGamer1))
      A->map.aff();
    // !DEBUG

    Case	currentCase = this->A->map.getCase((this->getX() / 400),
					     (this->getZ() / 400));

    if (isAlive() == false)
      {
	if (!this->listBomb_.empty())
	  {
	    timerBomb();
	    A->map.changeStatu(getX() / 400, getZ() / 400, FLOOR);
	  }
	score_ -= 1000;
	if (score_ < 0)
	  score_ = 0;
	this->status_ = Model::LOOSE;
	return ;
      }
    if (A->getNbEnemies() == 0)
      {
	score_ += 2000;
	this->status_ = Model::WIN;
	return ;
      }

   this->model_.update(A->getClock());

    if (this->type_ == PLAYER_ONE)
      getMovePlayer1();
    else if (this->type_ == PLAYER_TWO)
      getMovePlayer2();
    else
      getBotMove();

    updateMap(currentCase);

    if (this->type_ == PLAYER_ONE)
      putBombPlayer1(currentCase);
    else if (this->type_ == PLAYER_TWO)
      putBombPlayer2(currentCase);
    else
      putBombBot(currentCase);

    timerBomb();
  }

  void		Player::draw(void)
  {
    glPushMatrix();
    glTranslatef(this->position_.x, this->position_.y, this->position_.z);

    glRotatef(this->rotation_.y, 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotation_.z, 0.0f, 0.0f, 1.0f);
    glRotatef(this->rotation_.x, 1.0f, 0.0f, 0.0f);

    this->model_.draw();
    glPopMatrix();
  }

  void		Player::updateMap(Case &currentCase)
  {
    if (currentCase != this->oldCase_)
      {
	A->map.changeStatu(this->oldCase_.getXmin() / 400, this->oldCase_.getYmin() / 400 , this->oldCase_.getType());
	A->map.changeStatu(currentCase.getXmin() / 400, currentCase.getYmin() / 400 , PLAYER);
	this->oldCase_ = currentCase;
	if (oldCase_.getType() == BONUS || oldCase_.getType() == PLAYER)
	  oldCase_.setType(FLOOR);
      }
  }

  void		Player::deleteBox(int x, int y)
  {
    std::list<AObject*>::iterator it;

    for (it = this->A->listBoxes.begin(); it != this->A->listBoxes.end() ; ++it)
      if((*it)->getX() == x && (*it)->getZ() == y)
	{
	  A->listBoxes.erase(it);
	  Bonus::Bonus *bonus = new Bonus::Bonus();

	  bonus->setX(x);
	  bonus->setZ(y);
	  if (bonus->getType() != Bonus::NONE)
	    {
	      bonus->initialize();
	      A->listBonus.push_back(bonus);
	      A->map.changeStatu(x / 400, y / 400, FIRE_BONUS);
	    }
	  else
	    {
	      A->map.changeStatu(x / 400, y / 400, FIRE);
	      delete bonus;
	    }
	  break;
	}
  }

  ///
  ///	BOMB FUNCTIONS
  ///

  void		Player::putBombPlayer1(Case &currentCase)
  {
    if (this->A->isPressed(InputEngine::BombGamer1) && (this->currentCapacity_ > 0))
      {
    	if (currentCase.getType() == FLOOR || currentCase.getType() == PLAYER)
    	  {
	    A->playSoundEffect("sound/pose.wav");
    	    this->useBomb();
    	    this->A->map.addBomb((this->getX() / 400), (this->getZ() / 400));
    	    Model::Bomb *bomb = new Model::Bomb((currentCase.getXmin() + 200),
						(currentCase.getYmin() + 200),
						this->power_, this->modelBomb_);
	    this->A->map.changeStatu((this->getX() / 400), (this->getZ() / 400), BOMB);
	    oldCase_.setType(BOMB);
   	    this->A->listBombs.push_back(bomb);
    	    this->listBomb_.push_back(bomb);
    	  }
      }
  }


  void		Player::putBombPlayer2(Case &currentCase)
  {
    if (this->A->isPressed(InputEngine::BombGamer2) && (this->currentCapacity_ > 0))
      {
	if (currentCase.getType() == FLOOR || currentCase.getType() == PLAYER)
	  {
	    A->playSoundEffect("sound/pose.wav");
	    this->useBomb();
	    this->A->map.addBomb((this->getX() / 400), (this->getZ() / 400));
	    Model::Bomb *bomb = new Model::Bomb((currentCase.getXmin() + 200),
						(currentCase.getYmin() + 200),
						this->power_, this->modelBomb_);
	    oldCase_.setType(BOMB);
	    this->A->listBombs.push_back(bomb);
	    this->listBomb_.push_back(bomb);
	  }
      }
  }

  void		Player::putBombBot(Case &currentCase)
  {
    if (brain.getAction() == _BOMB && (this->currentCapacity_ > 0))
      {
    	if (currentCase.getType() == FLOOR || currentCase.getType() == PLAYER)
    	  {
	    A->playSoundEffect("sound/pose.wav");
    	    this->useBomb();
    	    this->A->map.addBomb((this->getX() / 400), (this->getZ() / 400));
    	    Model::Bomb *bomb = new Model::Bomb((currentCase.getXmin() + 200),
						(currentCase.getYmin() + 200),
						this->power_, this->modelBomb_);
	    oldCase_.setType(BOMB);
    	    this->A->listBombs.push_back(bomb);
    	    this->listBomb_.push_back(bomb);
    	  }
      }
  }

  void		Player::explosion(Model::Bomb *bomb)
  {
    this->currentCapacity_ += 1;

    int		x = bomb->getX() / 400;
    int		y = bomb->getZ() / 400;
    // A->map.changeStatu(x, y, FLOOR);

    explosionUp(x, y, bomb);
    explosionDown(x, y, bomb);
    explosionLeft(x, y, bomb);
    explosionRight(x, y, bomb);
  }

 void		Player::explosionUp(int x, int y, Model::Bomb *bomb)
  {
    for (int i = 0; i <= (this->power_ - 1) / 2; ++i)
      {
	Case currentCase = A->map.getCase(x, y + i);
	if (currentCase.getType() == WALL)
	  break;
	Fire::Horiz *fireH = new Fire::Horiz();
	fireH->SetX((x) * 400);
	fireH->SetZ((y + i) * 400);
	fireH->initialize();
	bomb->fire.push_back(fireH);
	if (currentCase.getType() == PLAYER)
	  {
	    score_ += 500;
	    getPlayer((x) * 400, (y + i) * 400)->die();
	    A->map.changeStatu((x), (y + i), FLOOR);
	    break;
	  }
	if (currentCase.getType() == BONUS)
	  {
	    deleteBonus(x * 400, (y + i) * 400);
	    A->map.changeStatu(x, y + i, FIRE);
	    break;
	  }
	if (currentCase.getType() == BOX)
	  {
	    score_ += 200;
	    deleteBox(x * 400, (y + i) * 400);
	    break;
	  }
	if (currentCase.getType() == BOMB)
	  {
	    Model::Player	*tmp;
	    tmp = checkPlayer(x * 400, (y + i) * 400);
	    if (tmp != NULL)
	      tmp->die();
	  }
	A->map.changeStatu(x, y + i, FIRE);
      }
  }

  void		Player::explosionDown(int x, int y, Model::Bomb *bomb)
  {
    for (int i = -1; i >= (this->power_ - 1) / -2; --i)
      {
	Case currentCase = A->map.getCase(x, y + i);
	if (currentCase.getType() == WALL)
	  break;
	Fire::Horiz *fireH = new Fire::Horiz();
	fireH->SetX((x) * 400);
	fireH->SetZ((y + i) * 400);
	fireH->initialize();
	bomb->fire.push_back(fireH);
	if (currentCase.getType() == PLAYER)
	  {
	    getPlayer((x) * 400, (y + i) * 400)->die();
	    A->map.changeStatu((x), (y + i), FLOOR);
	    break;
	  }
	if (currentCase.getType() == BONUS || currentCase.getType() == FIRE_BONUS)
	  {
	    deleteBonus(x * 400, (y + i) * 400);
	    A->map.changeStatu(x, y + i, FIRE);
	    break;
	  }
	if (currentCase.getType() == BOX)
	  {
	    deleteBox((x) * 400, (y + i) * 400);
	    break;
	  }
	if (currentCase.getType() == BOMB)
	  {
	    Model::Player	*tmp;
	    tmp = checkPlayer((x + i) * 400, (y) * 400);
	    if (tmp != NULL)
	      tmp->die();
	  }
	A->map.changeStatu(x, y + i, FIRE);
      }
  }

  void		Player::explosionLeft(int x, int y, Model::Bomb *bomb)
  {
    for (int i = 0; i <= (this->power_ - 1) / 2; ++i)
      {
	Case currentCase = A->map.getCase(x + i, y);
	if (currentCase.getType() == WALL)
	  break;
	Fire::Verti *fireH = new Fire::Verti();
	fireH->SetX((x + i) * 400);
	fireH->SetZ(y * 400);
	fireH->initialize();
	bomb->fire.push_back(fireH);
	if (currentCase.getType() == PLAYER)
	  {
	    getPlayer((x + i) * 400, (y) * 400)->die();
	    A->map.changeStatu((x + i), (y), FLOOR);
	    break;
	  }
	if (currentCase.getType() == BONUS)
	  {
	    deleteBonus((x + i) * 400, y * 400);
	    A->map.changeStatu((x + i), y, FIRE);
	    break;
	  }
	if (currentCase.getType() == BOX)
	  {
	    deleteBox((x + i) * 400, y * 400);
	    break;
	  }
	if (currentCase.getType() == BOMB)
	  {
	    Model::Player	*tmp;
	    tmp = checkPlayer((x + i) * 400, (y) * 400);
	    if (tmp != NULL)
	      tmp->die();
	  }
	A->map.changeStatu(x + i, y, FIRE);
      }
  }

  void		Player::explosionRight(int x, int y, Model::Bomb *bomb)
  {
    for (int i = -1; i >= (this->power_ - 1) / -2; --i)
      {
	Case currentCase = A->map.getCase(x + i, y);
	if (currentCase.getType() == WALL)
	  break;
	Fire::Verti *fireH = new Fire::Verti();
	fireH->SetX((x + i) * 400);
	fireH->SetZ(y * 400);
	fireH->initialize();
	bomb->fire.push_back(fireH);
	if (currentCase.getType() == PLAYER)
	  {
	    getPlayer((x + i) * 400, (y) * 400)->die();
	    A->map.changeStatu((x + i), (y), FLOOR);
	    break;
	  }
	if (currentCase.getType() == BONUS)
	  {
	    deleteBonus((x + i) * 400, y * 400);
	    A->map.changeStatu(x + i, y, FIRE);
	    break;
	  }
	if (currentCase.getType() == BOX)
	  {
	    deleteBox((x + i) * 400, y * 400);
	    break;
	  }
	if (currentCase.getType() == BOMB)
	  {
	    Model::Player	*tmp;
	    tmp = checkPlayer((x + i) * 400, (y) * 400);
	    if (tmp != NULL)
	      tmp->die();
	  }
	A->map.changeStatu(x + i, y, FIRE);
      }
  }

  std::list<AObject*>::iterator		Player::getItBomb(int x, int y)
  {
    std::list<AObject*>::iterator	it;

    for (it = this->A->listBombs.begin(); it != this->A->listBombs.end() ; ++it)
      {
	if ((*it)->getX() == x && (*it)->getZ() == y)
	  return it;
      }
    return it;
  }

  void		Player::timerBomb()
  {
    const float				TIME_EXPLOSION = 2.0;
    const float				TIMELIFE = 2.5;
    std::list<AObject*>::iterator	it;
    std::list<AObject*>::iterator	tmp;

    for (it = this->listBomb_.begin(); it != this->listBomb_.end() ; ++it)
      {
	tmp = getItBomb((*it)->getX(), (*it)->getZ());
	if (dynamic_cast<Model::Bomb *>(*it)->getTimer() > TIME_EXPLOSION &&
	    dynamic_cast<Model::Bomb *>(*it)->isExplosed() == false)
	  {
	    // A->playSoundEffect("sound/bomb.wav");
	    // dynamic_cast<Model::Bomb *>(*it)->model_.play("Take 001");
	    explosion(dynamic_cast<Model::Bomb *>(*tmp));
	    dynamic_cast<Model::Bomb *>(*it)->explose();
	  }
	if (dynamic_cast<Model::Bomb *>(*it)->getTimer() > TIMELIFE)
	  {
	    deleteBombe(dynamic_cast<Model::Bomb *>(*tmp));
	    delete (*it);
	    A->listBombs.erase(tmp);
	    listBomb_.erase(it);
	    break;
	  }
      }
  }

  void		Player::deleteBombe(Model::Bomb *bomb)
  {
    std::list<AObject*>::iterator itb;

    for (itb = bomb->fire.begin(); itb != bomb->fire.end() ; ++itb)
      {
	Case currentCase = A->map.getCase((*itb)->getX() / 400, (*itb)->getZ() / 400);
	if (currentCase.getType() == FIRE)
	  A->map.changeStatu((*itb)->getX() / 400, (*itb)->getZ() / 400, FLOOR);
	else if (currentCase.getType() == FIRE_BONUS)
	  A->map.changeStatu((*itb)->getX() / 400, (*itb)->getZ() / 400, BONUS);
      }
    A->map.changeStatu(bomb->getX() / 400, bomb->getZ() / 400, FLOOR);
  }

  ///
  ///	MOVE FUNCTIONS
  ///

  void		Player::getMovePlayer1(void)
  {
    if (A->isPressed(InputEngine::UpGamer1))
      {
	this->rotation_.y = DOWN;
	this->model_.play("Running");
	this->position_.z = doMove();
      }
    if (A->isPressed(InputEngine::DownGamer1))
      {
	this->rotation_.y = UP;
	this->model_.play("Running");
	this->position_.z = doMove();
      }
    if (A->isPressed(InputEngine::LeftGamer1))
      {
	this->rotation_.y = RIGHT;
	this->model_.play("Running");
	this->position_.x = doMove();
      }
    if (A->isPressed(InputEngine::RightGamer1))
      {
	this->rotation_.y = LEFT;
	this->model_.play("Running");
	this->position_.x = doMove();
      }
    A->setHorizontalMove(this->position_.x, this->position_.z);
  }

  void		Player::getMovePlayer2(void)
  {
    if (A->isPressed(InputEngine::UpGamer2))
      {
	this->rotation_.y = DOWN;
	this->model_.play("Running");
	this->position_.z = doMove();
      }
    if (A->isPressed(InputEngine::DownGamer2))
      {
	this->rotation_.y = UP;
	this->model_.play("Running");
	this->position_.z = doMove();
      }
    if (A->isPressed(InputEngine::LeftGamer2))
      {
	this->rotation_.y = RIGHT;
	this->model_.play("Running");
	this->position_.x = doMove();
      }
    if (A->isPressed(InputEngine::RightGamer2))
      {
	this->rotation_.y = LEFT;
	this->model_.play("Running");
	this->position_.x = doMove();
      }
    if (A->player1->isAlive() == false)
      A->setHorizontalMove(this->position_.x, this->position_.z);
  }

  void		Player::getBotMove(void)
  {
    if (brain.getAction() == _UP)
      {
	this->rotation_.y = DOWN;
	this->model_.play("Running");
	this->position_.z = doMove();
      }
    if (brain.getAction() == _DOWN)
      {
	this->rotation_.y = UP;
	this->model_.play("Running");
	this->position_.z = doMove();
      }
    if (brain.getAction() == _LEFT)
      {
	this->rotation_.y = RIGHT;
	this->model_.play("Running");
	this->position_.x = doMove();
      }
    if (brain.getAction() == _RIGHT)
      {
	this->rotation_.y = LEFT;
	this->model_.play("Running");
	this->position_.x = doMove();
      }
  }

  void		Player::deleteBonus(int x, int y)
  {
    std::list<AObject*>::iterator it;

    for (it = this->A->listBonus.begin(); it != this->A->listBonus.end() ; ++it)
      if((*it)->getX() ==  x && (*it)->getZ() == y)
	{
	  delete (*it);
	  this->A->listBonus.erase(it);
	  break;
	}
  }

  Bonus::Bonus	*Player::getBonus(int x, int y)
  {
    std::list<AObject*>::iterator it;

    for (it = this->A->listBonus.begin(); it != this->A->listBonus.end() ; ++it)
      if((*it)->getX() == x && (*it)->getZ() == y)
	return (dynamic_cast<Bonus::Bonus *>(*it));
    return (dynamic_cast<Bonus::Bonus *>(*it) - 1);
  }

  Model::Player	*Player::getPlayer(int x, int y)
  {
    std::list<AObject*>::iterator it;

    if((A->player1->getX()  / 400) * 400 == x && (A->player1->getZ() / 400) * 400 == y)
	return (A->player1);
    if(A->getPlayers() == 2 && (A->player2->getX() / 400) * 400 == x && (A->player2->getZ() / 400) * 400 == y)
	return (A->player2);
    for (it = this->A->listEnemies.begin(); it != this->A->listEnemies.end() ; ++it)
      {
	if(((*it)->getX() / 400) * 400 == x && ((*it)->getZ() / 400) * 400 == y)
	  return (dynamic_cast<Model::Player *>(*it));
      }
    return (this);
  }

  Model::Player	*Player::checkPlayer(int x, int y)
  {
    std::list<AObject*>::iterator it;

    if((A->player1->getX()  / 400) * 400 == x && (A->player1->getZ() / 400) * 400 == y)
	return (A->player1);
    if(A->getPlayers() == 2 && (A->player2->getX() / 400) * 400 == x && (A->player2->getZ() / 400) * 400 == y)
	return (A->player2);
    for (it = this->A->listEnemies.begin(); it != this->A->listEnemies.end() ; ++it)
      {
	if(((*it)->getX() / 400) * 400 == x && ((*it)->getZ() / 400) * 400 == y)
	  return (dynamic_cast<Model::Player *>(*it));
      }
    return (NULL);
  }

  void		Player::checkCase(Case &checkCase)
  {
    Bonus::Bonus	*tmp;

    if (checkCase.getType() == BONUS)
      {
	A->playSoundEffect("sound/bonus.wav");
	tmp = getBonus(checkCase.getXmin(), checkCase.getYmin());
	tmp->modifPlayer(&power_, &currentCapacity_, &speed_);
	A->map.changeStatu(checkCase.getXmin() / 400, checkCase.getYmin() / 400, FLOOR);
	deleteBonus(tmp->getX(), tmp->getZ());
	score_ += 250;
      }
    if (checkCase.getType() == FIRE || checkCase.getType() == FIRE_BONUS)
      {
	A->playSoundEffect("sound/death.wav");
	die();
      }
  }

  float		Player::doMove(void)
  {
    const int	RADIUS = 200;
    float	move = speed_ * A->getTimeClock();
    Case	caseBomby = A->map.getCase(static_cast<int>(this->position_.x / 400),
					    static_cast<int>(this->position_.z / 400));
    int		it = 0;

    while (tabMove[it].side != this->rotation_.y && it < 4)
      ++it;
    return (this->*tabMove[it].fct)(caseBomby, move, RADIUS);
  }

  bool		Player::canGo(CaseType type)
  {
    if (type == FLOOR || type == BONUS || type == FIRE || type == FIRE_BONUS)
      return true;
    return false;
  }

  float		Player::goRight(Case &caseBomby, float move, int radius)
  {
    Case	caseRight = A->map.getCase(static_cast<int>(this->position_.x / 400) + 1,
					    static_cast<int>(this->position_.z / 400));

    if ((position_.x + move) > (caseBomby.getXmax() - radius)
	&& canGo(caseRight.getType()) == false)
      return (caseBomby.getXmax() - radius);
    else
      {
        checkCase(caseBomby);
	return (this->position_.x + move);
      }
  }

  float		Player::goLeft(Case &caseBomby, float move, int radius)
  {
    Case	caseLeft = A->map.getCase(static_cast<int>(this->position_.x / 400) - 1,
					   static_cast<int>(this->position_.z / 400));

    if ((position_.x - move) < (caseBomby.getXmin() + radius)
	&& canGo(caseLeft.getType()) == false)
      return (caseBomby.getXmin() + radius);
    else
      {
	checkCase(caseBomby);
  	return (this->position_.x - move);
      }
  }

  float		Player::goUp(Case &caseBomby, float move, int radius)
  {
    Case	caseUp = A->map.getCase(static_cast<int>(this->position_.x / 400),
					 static_cast<int>(this->position_.z / 400) - 1);

    if ((position_.z - move) < (caseBomby.getYmin() + radius)
	&& canGo(caseUp.getType()) == false)
      return (caseBomby.getYmin() + radius);
    else
      {
	checkCase(caseBomby);
	return (this->position_.z - move);
      }
  }

  float		Player::goDown(Case &caseBomby, float move, int radius)
  {
    Case	caseDown = A->map.getCase(static_cast<int>(this->position_.x / 400),
					   static_cast<int>(this->position_.z / 400) + 1);

    if ((position_.z + move) > (caseBomby.getYmax() - radius)
	&& canGo(caseDown.getType()) == false)
      return (caseBomby.getYmax() - radius);
    else
      {
	checkCase(caseBomby);
	return (this->position_.z + move);
      }
  }

  void		Player::setX(int x)
  {
    this->position_.x = x;
  }

  void		Player::setY(int y)
  {
    this->position_.z = y;
  }

  void		Player::setScore(int score)
  {
    this->score_ = score;
  }

  void		Player::updateScore(void)
  {
    this->score_ += this->scoreStage_;
    this->scoreStage_ = 0;
  }

  gdl::Color	Player::getNewColor(void)
  {
    int		red = random() % 255;
    int		green = random() % 255;
    int		blue = random() % 255;

    return (gdl::Color(red, green, blue));
  }

  int		Player::getSpeed() const
  {
    return (this->speed_);
  }

  int		Player::getCurrentCapacity() const
  {
    return (this->currentCapacity_);
  }

  int		Player::getPower() const
  {
    return (this->power_);
  }

  void		Player::die()
  {
    this->live_ = false;
  }

  bool		Player::isAlive() const
  {
    return (this->live_);
  }

  void		Player::useBomb()
  {
    this->currentCapacity_--;
  }

  int		Player::getScore() const
  {
    return (this->score_);
  }

  int		Player::getStatus() const
  {
    return (this->status_);
  }

  PlayerType	Player::getType() const
  {
    return (this->type_);
  }

  void		Player::setStatus(Model::Status st)
  {
    this->status_ = st;
  }
}
