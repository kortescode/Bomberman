#include	"Map.hh"
#include	"Image.hpp"

namespace	Map
{
  Wall::Wall(ConfigEngine *A)
    :AObject(A), sizeX_(0), sizeY_(0)
  {
  }

  void		Wall::initialize(void)
  {
    if (this->A->ModeGame == Modes::FreeGame || this->A->ModeGame == Modes::EditorGame)
      this->texture_ = gdl::Image::load("img/wall2.jpg");
    else if (this->A->ModeGame == Modes::AdventureGame)
      {
	if (this->A->getStage() == 1)
	  this->texture_ = gdl::Image::load("img/waly1.jpg");
	else if (this->A->getStage() == 2)
	  this->texture_ = gdl::Image::load("img/waly2.jpg");
	else if (this->A->getStage() == 3)
	  this->texture_ = gdl::Image::load("img/waly.jpg");
	else if (this->A->getStage() == 4)
	  this->texture_ = gdl::Image::load("img/wa.jpg");
      }
  }

  void		Wall::update(void)
  {
  }

  void		Wall::draw(void)
  {
    this->texture_.bind();

    glBegin(GL_QUADS);

    glColor3f(255.0f, 255.0f, 255.0f);

    drawWall(-200, 0, 0, 0, 400, sizeY_);
    drawWall(sizeX_, 0, 0, sizeX_ + 200, 400, sizeY_);
    drawWall(-200, 0, -200, sizeX_ + 200, 400, 0);
    drawWall(-200, 0, sizeY_ + 200, sizeX_ + 200, 400, sizeY_);

    glEnd();
  }

 void		Wall::setSizeX(double x)
  {
    this->sizeX_ = x;
  }

  void		Wall::setSizeY(double y)
  {
    this->sizeY_ = y;
  }

  void		Wall::drawWall(int xMin, int yMin, int zMin,
			       int xMax, int yMax, int zMax)
  {
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(xMin, yMin, zMin);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(xMin, yMax, zMin);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(xMin, yMax, zMax);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(xMin, yMin, zMax);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(xMin, yMin, zMax);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(xMin, yMax, zMax);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(xMax, yMax, zMax);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(xMax, yMin, zMax);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(xMax, yMin, zMax);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(xMax, yMax, zMax);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(xMax, yMax, zMin);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(xMax, yMin, zMin);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(xMax, yMin, zMin);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(xMax, yMax, zMin);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(xMin, yMax, zMin);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(xMin, yMin, zMin);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(xMin, yMax, zMin);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(xMin, yMax, zMax);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(xMax, yMax, zMax);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(xMax, yMax, zMin);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(xMin, yMin, zMin);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(xMin, yMin, zMax);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(xMax, yMin, zMax);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(xMax, yMin, zMin);
  }
}
