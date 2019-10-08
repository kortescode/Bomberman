#include	"Map.hh"

namespace	Map
{
  Floor::Floor(ConfigEngine *A)
    : AObject(A), sizeX_(0), sizeY_(0)
  {
  }

  void		Floor::initialize(void)
  {
    if (this->A->ModeGame == Modes::FreeGame || this->A->ModeGame == Modes::EditorGame)
      this->texture_ = gdl::Image::load("img/herbe.jpg");
    else if (this->A->ModeGame == Modes::AdventureGame)
      {
	if (this->A->getStage() == 1)
	  this->texture_ = gdl::Image::load("img/FloorStage1.jpg");
	else if (this->A->getStage() == 2)
	  this->texture_ = gdl::Image::load("img/FloorStage2.jpg");
	else if (this->A->getStage() == 3)
	  this->texture_ = gdl::Image::load("img/floor3.jpg");
	else if (this->A->getStage() == 4)
	  this->texture_ = gdl::Image::load("img/floor.jpg");
      }
  }

  void		Floor::update(void)
  {
  }

  void		Floor::draw(void)
  {
    this->texture_.bind();

    glBegin(GL_QUADS);
    glColor3f(255.0f, 255.0f, 255.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 0, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0, 0, this->sizeY_);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(this->sizeX_, 0, this->sizeY_);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(this->sizeX_, 0, 0);
    glEnd();
  }

  void		Floor::setSizeX(double x)
  {
    this->sizeX_ = x;
  }

  void		Floor::setSizeY(double y)
  {
    this->sizeY_ = y;
  }
}
