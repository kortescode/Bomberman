#ifndef		BOMB_HH_
# define	BOMB_HH_

#include "Clock.hpp"
#include "Model.hpp"
#include "AObject.hh"

namespace Model
{
  class		Bomb : public AObject
  {
  public:
    Bomb(void);
    Bomb(int, int, int, gdl::Model &);
    ~Bomb(void);
    void		initialize(void);
    void		update(void);
    void		draw(void);

    int			getPower(void) const;
    double		getTimer(void) const;
    bool		isExplosed(void) const;
    void		explose(void);

    std::list<AObject*>	fire;

  private:
    gdl::Model		model_;
    int			power_;
    bool		isExplosed_;
    double		timer_;
  };
}


#endif /* !BOMB_H_ */
