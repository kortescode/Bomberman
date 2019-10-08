#include	"Bomb.hh"

namespace	Model
{
  Bomb::Bomb(void)
    : AObject(NULL)
  {
  }

  Bomb::Bomb(int x, int z, int power, gdl::Model &modelBomb)
    : AObject(NULL), power_(power)
  {
    this->isExplosed_ = false;
    this->timer_ = 0;
    this->position_.x = x;
    this->position_.z = z;
    this->position_.y = 200;
    this->model_ = modelBomb;
  }

  Bomb::~Bomb(void)
  {
    std::list<AObject*>::iterator	it;

    for (it = this->fire.begin(); it != this->fire.end(); ++it)
      delete *it;
    this->fire.clear();
  }

  void		Bomb::initialize(void)
  {
    std::list<AObject*>::iterator	it;

    for (it = this->fire.begin(); it != this->fire.end(); ++it)
      (*it)->initialize();
  }

  void		Bomb::update(void)
  {
    std::list<AObject*>::iterator	it;

    for (it = this->fire.begin(); it != this->fire.end(); ++it)
      (*it)->update();

    this->timer_ += 0.01;
  }

  void		Bomb::draw(void)
  {
    std::list<AObject*>::iterator	it;

    glPushMatrix();
    glTranslatef(position_.x, position_.y, position_.z);

    glRotatef(this->rotation_.y, 0.0f, 1.0f, 0.0f);
    glRotatef(this->rotation_.z, 0.0f, 0.0f, 1.0f);
    glRotatef(this->rotation_.x, 1.0f, 0.0f, 0.0f);

    this->model_.draw();
    glPopMatrix();

    for (it = this->fire.begin(); it != this->fire.end(); ++it)
      (*it)->draw();
  }

  int		Bomb::getPower(void) const
  {
    return (this->power_);
  }

  double	Bomb::getTimer(void) const
  {
    return (this->timer_);
  }

  bool		Bomb::isExplosed(void) const
  {
    return (this->isExplosed_);
  }

  void		Bomb::explose(void)
  {
    this->isExplosed_ = true;
  }
}
