#include		"IntroEngine.hh"
#include		"Modes.hh"

IntroEngine::IntroEngine(void)
{
}

IntroEngine::~IntroEngine(void)
{
}

void			IntroEngine::drawIntro(void)
{
  static int	       	y = 600;
  static int	       	step = 0;

  if (step < 50)
    {
      this->displayImage("img/spot.jpg", 0, 0, 800.0f, 600.0f);
      if ((y > 250 && (y -= 5)) || ++step)
	this->displayImage("img/bomber.jpg", 275, y, 250.0f, 350.0f);
    }
  else if ((step < 100 || (step > 150 && step < 200)) && ++step)
    this->displayImage("img/fight.jpg", 0, 0, 800.0f, 600.0f);
  else if ((step < 150 || step < 250) && ++step)
    this->displayImage("img/fight_rev.jpg", 0, 0, 800.0f, 600.0f);
  else if (step < 300 && ++step)
    this->displayImage("img/boom.jpg", 0, 0, 800.0f, 600.0f);
  else
    {
      if (++step % 5 == 0)
  	this->displayImage("img/start_click.jpg", 0, 0, 800.0f, 600.0f);
      else
  	this->displayImage("img/start.jpg", 0, 0, 800.0f, 600.0f);
    }
  this->displayText("", White, 0, 0, 0);
}

Modes::Mode    		IntroEngine::updateIntro(void)
{
  if (this->isClicked(0, 800, 0, 600))
    return (Modes::Menu);
  return (Modes::Intro);
}
