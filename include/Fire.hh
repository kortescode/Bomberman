#ifndef		FIRE_HH_
# define	FIRE_HH_

#include "AObject.hh"

class	ConfigEngine;

namespace	Fire
{
  class		Horiz : public AObject
  {
  public:
    Horiz();
    Horiz(ConfigEngine *A);
    void	initialize(void);
    void	update(void);
    void	draw(void);

    void	SetX(int x);
    void	SetZ(int z);

  private:
    gdl::Image	texture_;
  };

  class		Verti : public AObject
  {
  public:
    Verti();
    Verti(ConfigEngine *A);
    void	initialize(void);
    void	update(void);
    void	draw(void);

    void	SetX(int x);
    void	SetZ(int z);

  private:
    gdl::Image	texture_;
  };
}

#endif	// !FIRE_HH_
