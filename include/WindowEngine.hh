#ifndef				WINDOWENGINE_HH_
# define			WINDOWENGINE_HH_

# include			<string>
# include			"Game.hpp"
# include			"Window.hpp"
# include			"Color.hpp"
# include			"Text.hpp"
# include			"Modes.hh"
# include			"Vector3f.hh"

# define			Black	gdl::Color(0, 0, 0)
# define			Grey	gdl::Color(204, 204, 204)
# define			White	gdl::Color(255, 255, 255)

class				WindowEngine : virtual public gdl::Game
{
public:
  enum				GameMode
    {
      TWOD,
      TREED
    };

private:
  Modes::Mode			currentMode_;
  WindowEngine::GameMode	gameMode_;

  int				x_;
  int				y_;
  Vector3f			position_;
  Vector3f			target_;
  Vector3f			move_;

  static const int		initWidth_ = 800;
  static const int		initHeight_ = 600;

protected:

  void				modeIntroAndMenu(void);
  void				modeGame(void);

public:
  WindowEngine(void);
  ~WindowEngine(void);

  void				initWindow(void);
  void				updateWindow(Modes::Mode);
  void				closeWindow(void);

  void				setHorizontalMove(int, int);
  void				setVerticalMove(int);

  WindowEngine::GameMode	getGameMode(void) const;
  void				setGameMode(WindowEngine::GameMode);

  void				displayText(const std::string&, const gdl::Color&, int, int, int) const;
  void				displayImage(const std::string&, int, int, float, float) const;

  float				getWidthAdapt(int) const;
  float				getHeightAdapt(int) const;
  float				getScope(void) const;

  bool				canDraw(void);
};

#endif				/* !WINDOWENGINE_HH_ */
