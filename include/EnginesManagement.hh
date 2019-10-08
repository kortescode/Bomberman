#ifndef				ENGINESMANAGEMENT_HH_
# define			ENGINESMANAGEMENT_HH_

# include			"IntroEngine.hh"
# include			"MenuEngine.hh"
# include			"GameEngine.hh"
# include			"Modes.hh"

class				EnginesManagement : public IntroEngine, public MenuEngine, public GameEngine
{
  Modes::Mode			currentMode_;

public:
  EnginesManagement(void);
  ~EnginesManagement(void);

  void				initialize(void);
  void				update(void);
  void				draw(void);
  void				unload(void);
};

#endif				/* !ENGINESMANAGEMENT_HH_ */
