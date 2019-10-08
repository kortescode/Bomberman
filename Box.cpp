#include	"Map.hh"

namespace	Map
{
  Box::Box()
    : AObject(NULL)
  {
    this->position_.x = 0.0f;
    this->position_.y = 0.0f;
    this->position_.z = 0.0f;
  }

  Box::Box(ConfigEngine *A, gdl::Image text)
    : AObject(A), texture_(text)
  {
    this->position_.x = 0.0f;
    this->position_.y = 0.0f;
    this->position_.z = 0.0f;
  }

  void		Box::initialize(void)
  {
    // this->texture_ = gdl::Image::load("img/box.jpg");
  }

  void		Box::update(void)
  {
  }

  void		Box::draw(void)
  {
    this->texture_.bind();

    glBegin(GL_QUADS);
    glColor3f(255.0f, 255.0f, 255.0f);

    // Face 1
    glTexCoord2f(0.0f, 1.0f);

    glVertex3f(this->position_.x, SIZE, this->position_.z + SIZE);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->position_.x + SIZE, SIZE, this->position_.z + SIZE);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->position_.x + SIZE, 0, this->position_.z + SIZE);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->position_.x, 0, this->position_.z + SIZE);

    // Face 2
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(this->position_.x, 0, this->position_.z + SIZE);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->position_.x + SIZE, 0, this->position_.z + SIZE);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->position_.x + SIZE, 0, this->position_.z);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->position_.x, 0, this->position_.z);

    // Face 3
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(this->position_.x, SIZE, this->position_.z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->position_.x, SIZE, this->position_.z + SIZE);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->position_.x, 0, this->position_.z + SIZE);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->position_.x, 0, this->position_.z);

    // Face 4
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(this->position_.x + SIZE, SIZE, this->position_.z + SIZE);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->position_.x + SIZE, SIZE, this->position_.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->position_.x + SIZE, 0, this->position_.z);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->position_.x + SIZE, 0, this->position_.z + SIZE);

    // Face 5
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(this->position_.x, SIZE, this->position_.z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->position_.x + SIZE, SIZE, this->position_.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->position_.x + SIZE, 0, this->position_.z);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->position_.x, 0, this->position_.z);

    // Face 6
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(this->position_.x, SIZE, this->position_.z + SIZE);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(this->position_.x + SIZE, SIZE, this->position_.z + SIZE);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->position_.x + SIZE, SIZE, this->position_.z);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->position_.x, SIZE, this->position_.z);

    glEnd();
  }

  void		Box::setX(double x)
  {
    this->position_.x = x;
  }

  void		Box::setY(double y)
  {
    this->position_.y = y;
  }

  void		Box::setZ(double z)
  {
    this->position_.z = z;
  }
}
