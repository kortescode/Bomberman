#include	<iostream>
#include	"Case.hh"
#include	"InputEngine.hh"
#include	"ConfigEngine.hh"

const Editor::t_side tabMove[] =
  {
    {UP, &Editor::goUp},
    {DOWN, &Editor::goDown},
    {LEFT, &Editor::goLeft},
    {RIGHT, &Editor::goRight}
  };

Editor::Editor(ConfigEngine* A)
  : AObject(A)
{

}

Editor::~Editor(void)
{
}

void		Editor::initialize(void)
{
  this->position_.x = 200;
  this->position_.y = 200;
  this->position_.z = 200;
  this->texture_ = gdl::Image::load("img/work.jpg");
}

void		Editor::update(void)
{
  int		x = this->getX() / 400;
  int		z = this->getZ() / 400;
  int		width = A->getMapWidth() - 1;
  int		height = A->getMapHeight() - 1;
  Case	currentCase = this->A->map.getCase(x, z);

  if (A->isPressed(InputEngine::UpGamer1))
    {
      this->rotation_.y = DOWN;
      this->position_.z = doMove();
    }
  else if (A->isPressed(InputEngine::DownGamer1))
    {
      this->rotation_.y = UP;
      this->position_.z = doMove();
    }
  else if (A->isPressed(InputEngine::LeftGamer1))
    {
      this->rotation_.y = RIGHT;
      this->position_.x = doMove();
    }
  else if (A->isPressed(InputEngine::RightGamer1))
    {
      this->rotation_.y = LEFT;
      this->position_.x = doMove();
    }
  else if (A->isPressed(InputEngine::BombGamer1) && currentCase.getType() == FLOOR)
    {
      if (!((x == 0 && z == 0) || (x == 0 && z == 1) || (x == 1 && z == 0) ||
	    (x == width && z == 0) || (x == width && z == 1) || (x == width - 1 && z == 0) ||
	    (x == 0 && z == height) || (x == 1 && z == height) || (x == 0 && z == height - 1) ||
	    (x == width && z == height) || (x == width - 1 && z == height) || (x == width && z == height - 1)))
	{
	  Map::Box *box = new Map::Box(A, A->texture_Box);
	  box->setX(currentCase.getXmin());
	  box->setZ(currentCase.getYmin());
	  box->initialize();
	  A->listBoxes.push_back(box);
	  A->map.addBox(x, z);
	}
    }
  else if (A->isPressed(InputEngine::CtrlGamer1) && currentCase.getType() == BOX)
    {
      std::list<AObject*>::iterator it = A->listBoxes.begin();
      while (!((*it)->getX() / 400 == x && (*it)->getZ() / 400 == z) && it != A->listBoxes.end())
	++it;
      if (it != A->listBoxes.end())
	{
	  delete *it;
	  A->listBoxes.erase(it);
	}
      A->map.changeStatu(x, z, FLOOR);
    }
  A->setHorizontalMove(this->position_.x, this->position_.z);
}

void		Editor::draw(void)
{
  glPushMatrix();
  // glLoadIdentity();
  glTranslatef(this->position_.x, this->position_.y, this->position_.z);

  this->texture_.bind();

  glBegin(GL_QUADS);
  glColor3f(255.0f, 255.0f, 255.0f);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-size, size, size);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-size, -size, size);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(size, -size, size);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(size, size, size);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-size, size, -size);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-size, -size, -size);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-size, -size, size);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-size, size, size);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(size, size, -size);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(size, -size, -size);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-size, -size, -size);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-size, size, -size);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(size, size, size);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(size, -size, size);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(size, -size, -size);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(size, size, -size);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-size, size, -size);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-size, size, size);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(size, size, size);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(size, size, -size);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-size, -size, -size);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-size, -size, size);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(size, -size, size);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(size, -size, -size);
  glEnd();
  glPopMatrix();
}

float		Editor::doMove(void)
{
  const int	RADIUS = 200;
  float		move = 100;
  Case		currentCase = A->map.getCase(static_cast<int>(this->position_.x / 400),
					   static_cast<int>(this->position_.z / 400));
  int		it = 0;

  while (tabMove[it].side != this->rotation_.y && it < 4)
    ++it;
  return (this->*tabMove[it].fct)(currentCase, move, RADIUS);
}

bool		Editor::canGo(CaseType type)
{
  if (type == FLOOR || type == BOX)
    return true;
  return false;
}

float		Editor::goRight(Case &currentCase, float move, int radius)
{
  Case	caseRight = A->map.getCase(static_cast<int>(this->position_.x / 400) + 1,
				   static_cast<int>(this->position_.z / 400));

  if ((position_.x + move) > (currentCase.getXmax() - radius)
      && canGo(caseRight.getType()) == false)
    return (currentCase.getXmax() - radius);
  else
    return (this->position_.x + move);
}

float		Editor::goLeft(Case &currentCase, float move, int radius)
{
  Case	caseLeft = A->map.getCase(static_cast<int>(this->position_.x / 400) - 1,
				  static_cast<int>(this->position_.z / 400));

  if ((position_.x - move) < (currentCase.getXmin() + radius)
      && canGo(caseLeft.getType()) == false)
    return (currentCase.getXmin() + radius);
  else
    return (this->position_.x - move);
}

float		Editor::goUp(Case &currentCase, float move, int radius)
{
  Case	caseUp = A->map.getCase(static_cast<int>(this->position_.x / 400),
				static_cast<int>(this->position_.z / 400) - 1);

  if ((position_.z - move) < (currentCase.getYmin() + radius)
      && canGo(caseUp.getType()) == false)
    return (currentCase.getYmin() + radius);
  else
    return (this->position_.z - move);
}

float		Editor::goDown(Case &currentCase, float move, int radius)
{
  Case	caseDown = A->map.getCase(static_cast<int>(this->position_.x / 400),
				  static_cast<int>(this->position_.z / 400) + 1);

  if ((position_.z + move) > (currentCase.getYmax() - radius)
      && canGo(caseDown.getType()) == false)
    return (currentCase.getYmax() - radius);
  else
    return (this->position_.z + move);
}
