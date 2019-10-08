#ifndef			INTROENGINE_HH_
# define		INTROENGINE_HH_

# include		"ConfigEngine.hh"
# include		"Modes.hh"

class			IntroEngine : virtual public ConfigEngine
{
public:
  IntroEngine(void);
  ~IntroEngine(void);

  void			drawIntro(void);
  Modes::Mode      	updateIntro(void);
};

#endif			/* !INTROENGINE_HH_ */
