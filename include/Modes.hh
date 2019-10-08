#ifndef		MODES_HH_
# define	MODES_HH_

namespace	Modes
{
  enum 	        Mode
    {
      Intro,
      Menu,
      Game,
      Quit
    };

  enum		ModeMenu
    {
      Main = 1,
      Scores,
      Adventure,
      Free,
      Config,
      Preferences,
      SwitchPause,
      Stage,
      LoadSaves,
      LoadMaps,
      PauseAdventure,
      PauseFree,
      PauseEditor,
      Win,
      Editor
    };

  enum		ModeGame
    {
      FreeGame,
      AdventureGame,
      NextStage,
      EditorGame
    };
}

#endif		/* MODES_HH_ */
