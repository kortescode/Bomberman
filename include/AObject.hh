#ifndef AOBJECT_H_
# define AOBJECT_H_

# include <GL/gl.h>
# include <GL/glu.h>
# include "Clock.hpp"
# include "Color.hpp"
# include "Game.hpp"
# include "GameClock.hpp"
# include "Image.hpp"
# include "Input.hpp"
# include "Window.hpp"
# include "Vector3f.hh"

class ConfigEngine;

class AObject
{
public:
  AObject(ConfigEngine *a)
    : position_(0.0f, 0.0f, 0.0f), rotation_(0.0f, 0.0f, 0.0f), A(a)
  {
  }

  virtual ~AObject()
  {
  }

  virtual void initialize(void) = 0;
  virtual void update(void) = 0;
  virtual void draw(void) = 0;

  int		getX(void) const { return this->position_.x; }
  int		getZ(void) const { return this->position_.z; }

  void		setConfig(ConfigEngine *a) { this-> A = a; }

protected:
  Vector3f position_;
  Vector3f rotation_;
  ConfigEngine	*A;
};

#endif /* !AOBJECT_H_ */
