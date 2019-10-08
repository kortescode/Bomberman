#ifndef		BONUS_H_
# define	BONUS_H_

# include	"AObject.hh"

namespace	Bonus
{
  enum		BonusType
    {
      NONE,
      FIRE,
      SPEED,
      BOMB,
      LESSFIRE,
      LESSSPEED,
      LESSBOMB
    };

  class			Bonus : public AObject
  {
  public:
    Bonus();
    Bonus(ConfigEngine *A);
    void		initialize(void);
    void		update(void);
    void		draw(void);

    void		setX(double);
    void		setY(double);
    void		setZ(double);
    BonusType		getType() const;
    void		modifPlayer(int *, int *, int *);

  private:
    void		RandomType();

    BonusType		type_;
    int			power_;
    int			capacity_;
    int			speed_;
    gdl::Image		texture_;

    float		size_;
    bool		grown_;
  };
}


#endif /* !BONUS_H_ */
