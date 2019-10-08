#ifndef			CLOCKENGINE_HH_
# define		CLOCKENGINE_HH_

# include		"IClock.hpp"
# include		"Game.hpp"

class			ClockEngine : virtual public gdl::Game
{
  bool			doUpdate_;
  bool			doDraw_;

  float			loopTime_;
  float			timeClock_;

protected:
  void			pauseClock(void);
  void			resumeClock(void);

  float			getTotalTimeClock(void);

public:
  ClockEngine(void);
  ~ClockEngine(void);

  void			updateClock(void);
  float			getTimeClock(void);

  const gdl::IClock&	getClock(void) const;

  bool			isDoUpdate(void);
  bool			isDoDraw(void);
};

#endif			/* !CLOCKENGINE_HH_ */
