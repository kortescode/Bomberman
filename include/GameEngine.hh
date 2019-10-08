#ifndef		       	GAMEENGINE_HH_
# define	       	GAMEENGINE_HH_

# include	       	"ConfigEngine.hh"
# include		"AIEngine.hh"
# include		"Modes.hh"

class	       		GameEngine : virtual public ConfigEngine
{
  Modes::Mode  		updateFreeGame(void);
  Modes::Mode  		updateAdventureGame(void);

  bool			isInScope(int, int) const;

public:
  GameEngine(void);
  ~GameEngine(void);

  Modes::Mode		updateGame(void);
  void		       	drawGame(void);
};

#endif		       	/* GAMEENGINE_HH_ */
