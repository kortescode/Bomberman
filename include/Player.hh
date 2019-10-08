#ifndef		BOMBERMAN_HH_
# define	BOMBERMAN_HH_

# include	"AObject.hh"
# include	"Clock.hpp"
# include	"Model.hpp"
# include	"InputEngine.hh"
# include	"Case.hh"
# include	"Bomb.hh"
# include	"Brain.hh"
# include	"Bonus.hh"

enum	Side
  {
    UP = 180,
    DOWN = 0,
    LEFT = -90,
    RIGHT = 90
  };

namespace	Model
{
  enum	Status
    {
      NONE,
      WIN,
      LOOSE
    };

  enum	PlayerType
    {
      PLAYER_ONE,
      PLAYER_TWO,
      BOT
    };

  class		Player : public AObject
  {
  public:
    Player(ConfigEngine *, PlayerType);
    ~Player(void);

    void		initialize(void);
    void		update(void);
    void		draw(void);

    void		setX(int);
    void		setY(int);
    void		die(void);
    void		useBomb(void);
    void		setScore(int);
    void		updateScore(void);
    int			getSpeed(void) const;
    int			getPower(void) const;
    int			getScore(void) const;
    int			getStatus(void) const;
    int			getCurrentCapacity(void) const;
    PlayerType		getType(void) const;
    bool		isAlive(void) const;
    float		goRight(Case &, float, int);
    float		goLeft(Case &, float, int);
    float		goUp(Case &, float, int);
    float		goDown(Case &, float, int);
    void		setStatus(Model::Status);

  public:
    Brain		brain;

  private:
    gdl::Color		getNewColor(void);

    void		updateMap(Case &);
    Bonus::Bonus	*getBonus(int, int);
    void		deleteBox(int, int);
    void		deleteBombe(Model::Bomb *);
    void		deleteBonus(int, int);

    void		rmPlayer(int x, int y);
    void		putBombPlayer1(Case &);
    void		putBombPlayer2(Case &);
    void		putBombBot(Case &);
    void		explosion(Model::Bomb *);
    void		explosionUp(int, int, Model::Bomb *);
    void		explosionDown(int, int, Model::Bomb *);
    void		explosionLeft(int, int, Model::Bomb *);
    void		explosionRight(int, int, Model::Bomb *);
    void		timerBomb(void);
    std::list<AObject*>::iterator      getItBomb(int, int);
    Model::Player       *checkPlayer(int x, int y);
    void		getMovePlayer1(void);
    void		getMovePlayer2(void);
    void		getBotMove(void);
    float		doMove(void);
    void		checkCase(Case &);
    bool		canGo(CaseType);

  private:
    gdl::Model		modelBomb_;
    gdl::Model		model_;
    std::list<AObject*>	listBomb_;

    int			currentCapacity_;
    int			capacity_;
    int			power_;
    int			speed_;
    bool		live_;
    int			score_;
    int			scoreStage_;
    Status		status_;
    Case		oldCase_;
    PlayerType		type_;
    int			nbPlayer_;

  public:
    Model::Player		*getPlayer(int x, int y);
  };

  typedef struct	s_side
  {
    Side		side;
    float		(Player::*fct)(Case &, float, int);
  }			t_side;
}

#endif /* !BOMBERMAN_H_ */
