#ifndef			CONFIGENGINE_HH_
# define		CONFIGENGINE_HH_

# include	       	<list>
# include	       	"AObject.hh"
# include		"InputEngine.hh"
# include		"WindowEngine.hh"
# include		"ClockEngine.hh"
# include		"AudioEngine.hh"
# include		"Map.hh"
# include		"Player.hh"
# include		"Skybox.hh"
# include		"XmlEngine.hh"
# include		"Modes.hh"
# include		"AIEngine.hh"
# include		"Editor.hh"

# define		CalcPercent(p, x, y)	((p) * ((x) * (y)) / 100)

/*****************************
***** ConfigEngine class *****
*****************************/
class	AiEngine;
class			ConfigEngine : public InputEngine, public WindowEngine,
				       public ClockEngine, public AudioEngine
{
  int			players_;
  int			nbEnemies_;
  bool			editor_;

  int			mapWidth_;
  int			mapHeight_;
  int			boxPercent_;
  int			stage_;
  int			TotalScore_;

  void			setFloor(void);
  void			setWall(void);
  void			setBox(void);
  void			setSkybox(void);
  void			setPlayer(void);
  void			setEditor(void);
  void			setMap(void);
  void			setHardBoxes(void);
  void			setEnemies(void);
  void			setTexture(void);
  void			cleanConfig(void);

protected:
  XmlEngine		xml;

public:
  ConfigEngine(void);
  ~ConfigEngine(void);

  int			getTotalScore(void) const;
  int			getPlayers(void) const;
  int			getEnemies(void) const;
  int			getMapWidth(void) const;
  int			getMapHeight(void) const;
  int			getBoxPercent(void) const;
  int			getStage(void) const;
  bool			getEditor(void) const;
  int			getNbEnemies();

  void			setPlayers(int);
  void			setEnemies(int);
  void			setMapWidth(int);
  void			setMapHeight(int);
  void			setBoxPercent(int);
  void			initStage(void);
  void			nextStage(void);
  void			setStage(int);
  void			setDefaultConfig(void);
  void			setRandomConfig(void);
  void			setAdventureConfig(void);
  void			setEditorConfig(void);
  void			setLoadMapConfig(int, int);
  void			setTotalScore(int);
  void			setConfig(void);

  AiEngine		*AI;
  Modes::ModeGame	ModeGame;

  Map::Map		map;
  std::list<AObject*>	listWalls;
  std::list<AObject*>	listFloors;
  std::list<AObject*>	listHardBoxes;
  std::list<AObject*>	listBoxes;
  std::list<AObject*>	listBombs;
  std::list<AObject*>   listBonus;

  Model::Player		*player1;
  Model::Player		*player2;
  Editor		*editor;
  Skybox		*skybox;
  std::list<AObject*>	listEnemies;

  gdl::Image		texture_hardBox;
  gdl::Image		texture_Box;
  // gdl::Image		texture_hardBox;
  // gdl::Image		texture_hardBox;
  // gdl::Image		texture_hardBox;
  // gdl::Image		texture_hardBox;


  static const int	DefaultPlayers = 1;
  static const int     	DefaultEnemies = 3;
  static const int     	DefaultMapWidth	= 11;
  static const int     	DefaultMapHeight = 11;
  static const int     	DefaultBoxPercent = 20;

  static const int     	MinPlayers = 1;
  static const int     	MinEnemies = 1;
  static const int     	MinMapWidth = 1;
  static const int      MinMapHeight = 1;
  static const int     	MinBoxPercent = 0;

  static const int     	MaxPlayers = 2;
  static const int     	MaxBoxPercent = 100;
};

#endif			/* CONFIGENGINE_HH_ */
