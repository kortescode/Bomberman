#ifndef	       		MENUENGINE_HH_
# define      		MENUENGINE_HH_

# include      		<string>
# include      		<map>
# include      		"Color.hpp"
# include      		"ConfigEngine.hh"
# include		"Modes.hh"

class	      		MenuEngine : virtual public ConfigEngine
{
public:
  struct       	      	Button
  {
    const std::string	text_;
    const int  	      	x_;
    const int  	        y_;
    const int		width_;
    const bool	        interactive_;
    Modes::Mode		(MenuEngine::*fct_)(int);
    int			arg_;

    Button(const std::string&, const int, const int, const int, const bool, Modes::Mode (MenuEngine::*)(int), int);
    Button(const MenuEngine::Button&);
    ~Button(void);
  };

  typedef std::pair<Modes::ModeMenu, const MenuEngine::Button>		t_menuelem;
  typedef std::multimap<Modes::ModeMenu, const MenuEngine::Button>	t_menumap;

private:
  const int	      	fontSize_;
  const gdl::Color    	fontColor_;

  Modes::ModeMenu    	currentMenu_;
  MenuEngine::t_menumap	menusContent_;

  std::string		scoreName1_;
  std::string		scoreName2_;
  std::string		mapName_;

  int			savesIterator_;
  int			mapsIterator_;

  void			switchPause(void);
  Modes::Mode      	goToMenu(int);
  Modes::Mode      	launchGame(int);
  Modes::Mode		loadGame(int);
  Modes::Mode		loadMap(int);
  Modes::Mode      	quit(int);

  Modes::Mode		creaseMusicVolume(int);
  Modes::Mode		creaseSoundVolume(int);
  Modes::Mode		creaseMapWidth(int);
  Modes::Mode		creaseMapHeight(int);
  Modes::Mode		creasePlayers(int);
  Modes::Mode		creaseEnemies(int);
  Modes::Mode		creaseBoxPercent(int);
  Modes::Mode		creaseScoreName(int);
  Modes::Mode		creaseMapName(int);
  Modes::Mode		changeDimensionMode(int);
  Modes::Mode		changeMusic(int);
  Modes::Mode		changeSound(int);
  Modes::Mode		changeUpGamer(int);
  Modes::Mode		changeDownGamer(int);
  Modes::Mode		changeRightGamer(int);
  Modes::Mode		changeLeftGamer(int);
  Modes::Mode		changeBombGamer(int);
  Modes::Mode		changeCtrlGamer(int);
  Modes::Mode		changeUpCamera(int);
  Modes::Mode		changeDownCamera(int);
  Modes::Mode		changeSavesIterator(int);
  Modes::Mode		changeMapsIterator(int);
  Modes::Mode		changePause(int);
  Modes::Mode		saveScore(int);
  Modes::Mode		saveGame(int);
  Modes::Mode		saveMap(int);

  Modes::Mode  		updateStage(void);

  void			drawConfig(void) const;
  void			drawScores(void);
  void			drawPreferences(void) const;
  void			drawEditor(void) const;
  void			drawPauseEditor(void) const;
  void			drawWin(void) const;
  void			drawLoadSaves(void) const;
  void			drawLoadMaps(void) const;

public:
  MenuEngine(void);
  ~MenuEngine(void);

  Modes::Mode      	updateMenu(void);
  void	       	       	drawMenu(void);
};

#endif	       	       	/* MENUENGINE_HH_ */
