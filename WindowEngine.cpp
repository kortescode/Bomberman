#include		<iostream>
#include		<GL/gl.h>
#include		<GL/glu.h>
#include		<string>
#include		"Text.hpp"
#include		"Image.hpp"
#include		"Window.hpp"
#include		"WindowEngine.hh"
#include		"Modes.hh"
#include	       	"Vector3f.hh"

WindowEngine::WindowEngine(void)
  : currentMode_(Modes::Intro), gameMode_(WindowEngine::TWOD),
    x_(0), y_(0), position_(0, 0, 0), target_(0, 0, 0), move_(0, 0, 0)
{
}

WindowEngine::~WindowEngine(void)
{
}

void			WindowEngine::setHorizontalMove(int x, int z)
{
  this->move_.x = x * -1;
  this->move_.z = z * -1;
}

void			WindowEngine::setVerticalMove(int y)
{
  if (this->position_.y + y >= 1000 && this->position_.y + y <= 10000)
    this->position_.y += y;
}

void			WindowEngine::modeGame(void)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0f, 800.0f/600.0f, 1.0f, 200000000.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  this->position_.x = 0;
  if (this->gameMode_ == WindowEngine::TWOD)
    {
      this->position_.y = 4000;
      this->position_.z = -1;
    }
  else if (this->gameMode_ == WindowEngine::TREED)
    {
      this->position_.y = 2100;
      this->position_.z = -1800;
    }
  this->target_.x = 0;
  this->target_.y = -1;
  this->target_.z = 0;
}

void			WindowEngine::modeIntroAndMenu(void)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, 800.0f, 0.0f, 600.0f, 0.0f, 0.0f);
  gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void			WindowEngine::initWindow(void)
{
  this->window_.setTitle("Bomberman");
  this->window_.create();
  this->modeIntroAndMenu();
}

void			WindowEngine::updateWindow(Modes::Mode newMode)
{
  if (newMode != this->currentMode_)
    {
      if (newMode == Modes::Intro || newMode == Modes::Menu)
	this->modeIntroAndMenu();
      else if (newMode == Modes::Game)
	this->modeGame();
      this->currentMode_ = newMode;
    }
  if (this->currentMode_ == Modes::Game)
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClearDepth(1.0f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(this->position_.x, this->position_.y, this->position_.z,
		this->target_.x, this->target_.y, this->target_.z,
		0.0f, 1.0f, 0.0f);
      glTranslatef(this->move_.x, this->move_.y, this->move_.z);
    }
}

void			WindowEngine::closeWindow(void)
{
  if (this->window_.isOpened())
    this->window_.close();
}

WindowEngine::GameMode	WindowEngine::getGameMode(void) const
{
  return (this->gameMode_);
}

void			WindowEngine::setGameMode(WindowEngine::GameMode mode)
{
  this->gameMode_ = mode;
}

void			WindowEngine::displayText(const std::string& text, const gdl::Color& color,
						  int size, int posx, int posy) const
{
  gdl::Text		textToDisplay;

  textToDisplay.setText(text);
  textToDisplay.setColor(color);
  textToDisplay.setSize(size);
  textToDisplay.setPosition(posx, posy);
  textToDisplay.draw();
}

void			WindowEngine::displayImage(const std::string& path, int x, int y, float width, float height) const
{
  gdl::Image		imgToDisplay = gdl::Image::load(path);

  imgToDisplay.bind();
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(x, y);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(x, height + y);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(width + x, height + y);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(width + x, y);
  glEnd();
}

float			WindowEngine::getWidthAdapt(int width) const
{
  float			indice = (float)this->window_.getWidth() / (float)this->initWidth_;

  return (width * indice);
}

float			WindowEngine::getHeightAdapt(int height) const
{
  float			indice = (float)this->window_.getHeight() / (float)this->initHeight_;

  return (height * indice);
}

float			WindowEngine::getScope(void) const
{
  return (this->position_.y);
}

bool			WindowEngine::canDraw(void)
{
  return (this->window_.isOpened());
}
