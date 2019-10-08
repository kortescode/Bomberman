#include	"Fire.hh"

namespace	Fire
{
  ///
  ///	Horizontal part of the explosion
  ///

  Horiz::Horiz()
    : AObject(NULL)
  {
    position_.x = 0;
    position_.z = 0;
  }

  Horiz::Horiz(ConfigEngine *A)
    : AObject(A)
  {
    position_.x = 0;
    position_.z = 0;
  }

  void		Horiz::initialize(void)
  {
    this->texture_ = gdl::Image::load("img/fire2.jpg");
  }

  void		Horiz::update(void)
  {
  }

  void		Horiz::draw(void)
  {
    this->texture_.bind();

    glBegin(GL_QUADS);
    glColor3f(255.0f, 255.0f, 255.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position_.x + 100, position_.y + 100, position_.z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position_.x + 100, position_.y + 300, position_.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position_.x + 300, position_.y + 300, position_.z);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position_.x + 300, position_.y + 100, position_.z);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position_.x + 300, position_.y + 100, position_.z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position_.x + 300, position_.y + 300, position_.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position_.x + 300, position_.y + 300, position_.z + 400);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position_.x + 300, position_.y + 100, position_.z + 400);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position_.x + 300, position_.y + 100, position_.z + 400);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position_.x + 300, position_.y + 300, position_.z + 400);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position_.x + 100, position_.y + 300, position_.z + 400);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position_.x + 100, position_.y + 100, position_.z + 400);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position_.x + 100, position_.y + 100, position_.z + 400);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position_.x + 100, position_.y + 300, position_.z + 400);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position_.x + 100, position_.y + 300, position_.z);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position_.x + 100, position_.y + 100, position_.z);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position_.x + 100, position_.y + 300, position_.z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position_.x + 300, position_.y + 300, position_.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position_.x + 300, position_.y + 300, position_.z + 400);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position_.x + 100, position_.y + 300, position_.z + 400);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position_.x + 100, position_.y + 100, position_.z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position_.x + 300, position_.y + 100, position_.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position_.x + 300, position_.y + 100, position_.z + 400);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position_.x + 100, position_.y + 100, position_.z + 400);

    glEnd();
  }

  void		Horiz::SetX(int x)
  {
    this->position_.x = x;
  }

  void		Horiz::SetZ(int z)
  {
    this->position_.z = z;
  }

  ///
  ///	Vertical part of the explosion
  ///

  Verti::Verti()
    : AObject(NULL)
  {
    position_.x = 0;
    position_.y = 100;
    position_.z = 0;
  }

  Verti::Verti(ConfigEngine *A)
    : AObject(A)
  {
    position_.x = 0;
    position_.y = 100;
    position_.z = 0;
  }

  void		Verti::initialize(void)
  {
    this->texture_ = gdl::Image::load("img/fire2.jpg");
  }

  void		Verti::update(void)
  {
  }

  void		Verti::draw(void)
  {
    this->texture_.bind();

    glBegin(GL_QUADS);
    glColor3f(255.0f, 255.0f, 255.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position_.x, position_.y + 100, position_.z + 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position_.x, position_.y + 299, position_.z + 100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position_.x, position_.y + 299, position_.z + 300);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position_.x, position_.y + 100, position_.z + 300);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position_.x, position_.y + 100, position_.z + 300);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position_.x, position_.y + 299, position_.z + 300);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position_.x + 400, position_.y + 299, position_.z + 300);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position_.x + 400, position_.y + 100, position_.z + 300);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position_.x + 400, position_.y + 100, position_.z + 300);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position_.x + 400, position_.y + 299, position_.z + 300);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position_.x + 400, position_.y + 299, position_.z + 100);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position_.x + 400, position_.y + 100, position_.z + 100);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position_.x + 400, position_.y + 100, position_.z + 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position_.x + 400, position_.y + 299, position_.z + 100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position_.x, position_.y + 299, position_.z + 100);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position_.x, position_.y + 100, position_.z + 100);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position_.x, position_.y + 299, position_.z + 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position_.x, position_.y + 299, position_.z + 300);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position_.x + 400, position_.y + 299, position_.z + 300);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position_.x + 400, position_.y + 299, position_.z + 100);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position_.x, position_.y + 100, position_.z + 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position_.x, position_.y + 100, position_.z + 300);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position_.x + 400, position_.y + 100, position_.z + 300);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position_.x + 400, position_.y + 100, position_.z + 100);

    glEnd();
  }

  void		Verti::SetX(int x)
  {
    this->position_.x = x;
  }

  void		Verti::SetZ(int z)
  {
    this->position_.z = z;
  }
}
