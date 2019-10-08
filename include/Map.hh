#ifndef		MAP_HH_
# define	MAP_HH_

#include	<map>
#include	"Image.hpp"
#include	"Case.hh"
#include	"AObject.hh"

class	Case;
class	ConfigEngine;

namespace	Map
{
  class		Map
  {
  public:
    std::map<std::pair<int, int>, Case>	_stock;

    void	add(std::pair<int, int>, Case);
    void	aff();
    bool	addBox(int, int);
    Case	&getCase(int, int);
    void	addBomb(int, int);
    void	addPlayer(int, int);
    void	changeStatu(int, int, CaseType);
    int		countBonus();
    void	clean();
    bool	checkBoxPlayer(int x, int y);
  };

  class		Floor : public AObject
  {
  public:
    Floor(ConfigEngine *A);
    void	initialize(void);
    void	update(void);
    void	draw(void);

    void	setSizeX(double);
    void	setSizeY(double);

  private:
    double	sizeX_;
    double	sizeY_;
    gdl::Image	texture_;
  };

  class		HardBox : public AObject
  {
  public:
    HardBox();
    HardBox(ConfigEngine *A,  gdl::Image text);
    void	initialize(void);
    void	update(void);
    void	draw(void);

    void	setX(double);
    void	setY(double);
    void	setZ(double);

  private:
    gdl::Image	texture_;

    static const float	SIZE = 400.0f;
  };

  class			Box : public AObject
  {
  public:
    Box();
    Box(ConfigEngine *A, gdl::Image text);
    void		initialize(void);
    void		update(void);
    void		draw(void);

    void		setX(double);
    void		setY(double);
    void		setZ(double);

  private:
    gdl::Image		texture_;

    static const float	SIZE = 400.0f;
  };

  class			Wall : public AObject
  {
  public:
    Wall(ConfigEngine *A);
    void		initialize(void);
    void		update(void);
    void		draw(void);

    void		setSizeX(double);
    void		setSizeY(double);

  private:
    void		drawWall(int, int, int, int, int, int);

    gdl::Image		texture_;
    double		sizeX_;
    double		sizeY_;
    static const float	SIZE = 400.0f;
  };
}

#include	"ConfigEngine.hh"

#endif /* !MAP_H_ */
