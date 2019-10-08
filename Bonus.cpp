#include	<cstdlib>
#include	"Bonus.hh"

namespace	Bonus
{
  Bonus::Bonus()
    : AObject(NULL)
  {
    this->position_.x = 0.0f;
    this->position_.y = 100.0f;
    this->position_.z = 0.0f;
    this->power_ = 0;
    this->capacity_ = 0;
    this->speed_ = 0;
    this->size_ = 150.0f;
    this->grown_ = true;
    RandomType();
  }

  Bonus::Bonus(ConfigEngine *A)
    : AObject(A)
  {
    this->position_.x = 0.0f;
    this->position_.y = 100.0f;
    this->position_.z = 0.0f;
    this->power_ = 0;
    this->capacity_ = 0;
    this->speed_ = 0;
    this->size_ = 150.0f;
    this->grown_ = true;
    RandomType();
  }

  void		Bonus::initialize(void)
  {
    if (this->type_ == FIRE)
      this->texture_ = gdl::Image::load("img/flam.jpg");
    else if (this->type_ == SPEED)
      this->texture_ = gdl::Image::load("img/roller.jpg");
    else if (this->type_ == BOMB)
      this->texture_ = gdl::Image::load("img/bomb.png");
    else if (this->type_ == LESSFIRE)
      this->texture_ = gdl::Image::load("img/lessflam.jpg");
    else if (this->type_ == LESSBOMB)
      this->texture_ = gdl::Image::load("img/lessbomb.png");
    else if (this->type_ == LESSSPEED)
      this->texture_ = gdl::Image::load("img/lessroller.jpg");
}

  void		Bonus::update(void)
  {
    if (this->grown_ == true)
      {
	++this->size_;
	if (this->size_ >= 250)
	  this->grown_ = false;
      }
    else
      {
	--this->size_;
	if (this->size_ <= 150)
	  this->grown_ = true;
      }
  }

  void		Bonus::draw(void)
  {
    this->texture_.bind();

    glPushMatrix();
    glBegin(GL_QUADS);

    glColor3f(255.0f, 255.0f, 255.0f);

    // Face 1
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(this->position_.x + 100, this->size_, this->position_.z + 100 + this->size_);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->position_.x + this->size_ + 100, this->size_, this->position_.z + 100 + this->size_);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->position_.x + this->size_ + 100, 0, this->position_.z + 100 + this->size_);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->position_.x + 100, 0, this->position_.z + 100 + this->size_);

    // Face 2
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(this->position_.x + 100, 0, this->position_.z + 100 + this->size_);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->position_.x + this->size_ + 100, 0, this->position_.z + 100 + this->size_);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->position_.x + this->size_ + 100, 0, this->position_.z + 100);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->position_.x + 100, 0, this->position_.z + 100);

    // Face 3
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(this->position_.x + 100, this->size_, this->position_.z + 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->position_.x + 100, this->size_, this->position_.z + 100 + this->size_);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->position_.x + 100, 0, this->position_.z + 100 + this->size_);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->position_.x + 100, 0, this->position_.z + 100);

    // Face 4
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(this->position_.x + this->size_ + 100, this->size_, this->position_.z + 100 + this->size_);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->position_.x + this->size_ + 100, this->size_, this->position_.z + 100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->position_.x + this->size_ + 100, 0, this->position_.z + 100);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->position_.x + this->size_ + 100, 0, this->position_.z + 100 + this->size_);

    // Face 5
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(this->position_.x + 100, this->size_, this->position_.z + 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->position_.x + this->size_ + 100, this->size_, this->position_.z + 100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->position_.x + this->size_ + 100, 0, this->position_.z + 100);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->position_.x + 100, 0, this->position_.z + 100);

    // Face 6
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(this->position_.x + 100, this->size_, this->position_.z + 100 + this->size_);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->position_.x + this->size_ + 100, this->size_, this->position_.z + 100 + this->size_);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->position_.x + this->size_ + 100, this->size_, this->position_.z + 100);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->position_.x + 100, this->size_, this->position_.z + 100);

    glEnd();
    glPopMatrix();
  }

  void		Bonus::setX(double x)
  {
    this->position_.x = x;
  }

  void		Bonus::setY(double y)
  {
    this->position_.y = y;
  }

  void		Bonus::setZ(double z)
  {
    this->position_.z = z;
  }

  BonusType	Bonus::getType() const
  {
    return (this->type_);
  }

  void		Bonus::modifPlayer(int *power, int *capacity, int *speed)
  {
    *power += this->power_;
    *speed += this->speed_;
    *capacity += this->capacity_;

    if (*power < 3)
      *power = 3;
    if (*speed < 400)
      *speed = 400;
    if (*capacity < 1)
      *capacity = 1;
  }

  void		Bonus::RandomType()
  {
    int	i = random() % 100;

    if (i > 0 && i <= 15)
      {
	this->power_ = 2;
	this->type_ = FIRE;
      }
    else if (i > 15 && i <= 30)
      {
	this->capacity_ = 1;
	this->type_ = BOMB;
      }
    else if (i > 30 && i <= 45)
      {
	this->speed_ = 400;
	this->type_ = SPEED;
      }
    else if (i > 45 && i <= 55)
      {
	this->power_ = -2;
	this->type_ = LESSFIRE;
      }
    else if (i > 55 && i <= 65)
      {
	this->capacity_ = -1;
	this->type_ = LESSBOMB;
      }
    else if (i > 65 && i <= 75)
      {
	this->speed_ = -200;
	this->type_ = LESSSPEED;
      }
    else
      this->type_ = NONE;
  }
}

