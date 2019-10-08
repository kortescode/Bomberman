#include		<iostream>
#include		<string.h>
#include		<map>
#include		<sstream>
#include		"MenuEngine.hh"
#include		"WindowEngine.hh"
#include		"Common.hh"
#include		"Modes.hh"
#include		"Player.hh"

MenuEngine::MenuEngine(void)
  : fontSize_(18), fontColor_(White), currentMenu_(Modes::Main),
    scoreName1_("A A A"), scoreName2_("A A A"), mapName_("A A A A A"),
    savesIterator_(0), mapsIterator_(0)
{
  /* Main Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Main, MenuEngine::Button("-- MENU --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Main, MenuEngine::Button("Adventure Game", 40, 160, 100, true, &MenuEngine::goToMenu, Modes::Adventure)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Main, MenuEngine::Button("Free Game", 40, 200, 150, true, &MenuEngine::goToMenu, Modes::Free)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Main, MenuEngine::Button("Map Editor", 40, 240, 150, true, &MenuEngine::goToMenu, Modes::Editor)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Main, MenuEngine::Button("Scores", 40, 280, 100, true, &MenuEngine::goToMenu, Modes::Scores)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Main, MenuEngine::Button("Preferences", 40, 320, 130, true, &MenuEngine::goToMenu, Modes::Preferences)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Main, MenuEngine::Button("Quit", 40, 360, 60, true, &MenuEngine::quit, 0)));
  /* Scores Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Scores, MenuEngine::Button("-- SCORES --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Scores, MenuEngine::Button("Adventure Game", 40, 140, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Scores, MenuEngine::Button("1st", 70, 180, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Scores, MenuEngine::Button("2sd", 70, 210, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Scores, MenuEngine::Button("3rd", 70, 240, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Scores, MenuEngine::Button("Free Game", 40, 280, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Scores, MenuEngine::Button("1st", 70, 320, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Scores, MenuEngine::Button("2sd", 70, 350, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Scores, MenuEngine::Button("3rd", 70, 380, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Scores, MenuEngine::Button("Return", 40, 420, 100, true, &MenuEngine::goToMenu, Modes::Main)));
  /* Adventure Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Adventure, MenuEngine::Button("-- ADVENTURE GAME --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Adventure, MenuEngine::Button("New game", 40, 140, 130, true, &MenuEngine::launchGame, 4)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Adventure, MenuEngine::Button("Load game", 40, 180, 150, true, &MenuEngine::goToMenu, Modes::LoadSaves)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Adventure, MenuEngine::Button("Return", 40, 220, 100, true, &MenuEngine::goToMenu, Modes::Main)));
  /* LoadSaves Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("-- LOAD GAME --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("Date", 70, 140, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("Stage", 300, 140, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("Score", 380, 140, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("[<]", 30, 270, 20, true, &MenuEngine::changeSavesIterator, -8)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("[>]", 570, 270, 20, true, &MenuEngine::changeSavesIterator, 8)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("        ", 480, 180, 70, true, &MenuEngine::loadGame, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("        ", 480, 210, 70, true, &MenuEngine::loadGame, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("        ", 480, 240, 70, true, &MenuEngine::loadGame, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("        ", 480, 270, 70, true, &MenuEngine::loadGame, 3)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("        ", 480, 300, 70, true, &MenuEngine::loadGame, 4)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("        ", 480, 330, 70, true, &MenuEngine::loadGame, 5)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("        ", 480, 360, 70, true, &MenuEngine::loadGame, 6)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("        ", 480, 390, 70, true, &MenuEngine::loadGame, 7)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadSaves, MenuEngine::Button("Return", 40, 430, 100, true, &MenuEngine::goToMenu, Modes::Adventure)));
  /* LoadMaps Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("-- LOAD MAP --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("Gamers", 40, 140, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("[-]", 200, 140, 20, true, &MenuEngine::creasePlayers, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("[+]", 270, 140, 20, true, &MenuEngine::creasePlayers, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("Enemies", 40, 170, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("[-]", 200, 170, 20, true, &MenuEngine::creaseEnemies, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("[+]", 270, 170, 20, true, &MenuEngine::creaseEnemies, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("Map", 40, 200, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("Name", 70, 230, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("Width", 200, 230, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("Height", 280, 230, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("[<]", 30, 345, 20, true, &MenuEngine::changeMapsIterator, -6)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("[>]", 470, 345, 20, true, &MenuEngine::changeMapsIterator, 6)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("        ", 380, 270, 70, true, &MenuEngine::loadMap, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("        ", 380, 300, 70, true, &MenuEngine::loadMap, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("        ", 380, 330, 70, true, &MenuEngine::loadMap, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("        ", 380, 360, 70, true, &MenuEngine::loadMap, 3)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("        ", 380, 390, 70, true, &MenuEngine::loadMap, 4)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("        ", 380, 420, 70, true, &MenuEngine::loadMap, 5)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::LoadMaps, MenuEngine::Button("Return", 40, 460, 100, true, &MenuEngine::goToMenu, Modes::Free)));
  /* Free Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Free, MenuEngine::Button("-- FREE GAME --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Free, MenuEngine::Button("Default game", 40, 140, 100, true, &MenuEngine::launchGame, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Free, MenuEngine::Button("Configurable game", 40, 180, 150, true, &MenuEngine::goToMenu, Modes::Config)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Free, MenuEngine::Button("Random game", 40, 220, 120, true, &MenuEngine::launchGame, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Free, MenuEngine::Button("Load map", 40, 260, 100, true, &MenuEngine::goToMenu, Modes::LoadMaps)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Free, MenuEngine::Button("Return", 40, 300, 100, true, &MenuEngine::goToMenu, Modes::Main)));
  /* Editor Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Editor, MenuEngine::Button("-- MAP EDITOR --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Editor, MenuEngine::Button("Map width", 40, 140, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Editor, MenuEngine::Button("[-]", 200, 140, 20, true, &MenuEngine::creaseMapWidth, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Editor, MenuEngine::Button("[+]", 270, 140, 20, true, &MenuEngine::creaseMapWidth, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Editor, MenuEngine::Button("Map height", 40, 180, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Editor, MenuEngine::Button("[-]", 200, 180, 20, true, &MenuEngine::creaseMapHeight, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Editor, MenuEngine::Button("[+]", 270, 180, 20, true, &MenuEngine::creaseMapHeight, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Editor, MenuEngine::Button("Launch editor", 40, 220, 100, true, &MenuEngine::launchGame, 5)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Editor, MenuEngine::Button("Return", 40, 260, 100, true, &MenuEngine::goToMenu, Modes::Main)));
  /* Config Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("-- CONFIGURABLE GAME --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("Map width", 40, 140, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("[-]", 200, 140, 20, true, &MenuEngine::creaseMapWidth, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("[+]", 270, 140, 20, true, &MenuEngine::creaseMapWidth, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("Map height", 40, 170, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("[-]", 200, 170, 20, true, &MenuEngine::creaseMapHeight, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("[+]", 270, 170, 20, true, &MenuEngine::creaseMapHeight, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("Gamers", 40, 210, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("[-]", 200, 210, 20, true, &MenuEngine::creasePlayers, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("[+]", 270, 210, 20, true, &MenuEngine::creasePlayers, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("Enemies", 40, 240, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("[-]", 200, 240, 20, true, &MenuEngine::creaseEnemies, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("[+]", 270, 240, 20, true, &MenuEngine::creaseEnemies, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("Box percent", 40, 280, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("[-]", 200, 280, 20, true, &MenuEngine::creaseBoxPercent, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("[+]", 270, 280, 20, true, &MenuEngine::creaseBoxPercent, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("Launch game", 40, 320, 100, true, &MenuEngine::launchGame, 3)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Config, MenuEngine::Button("Return", 40, 360, 100, true, &MenuEngine::goToMenu, Modes::Free)));
  /* Preferences Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("-- PREFERENCES --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Game", 40, 140, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Video mode", 60, 170, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("2D", 180, 170, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[ ]", 210, 170, 20, true, &MenuEngine::changeDimensionMode, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("3D", 250, 170, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[ ]", 280, 170, 20, true, &MenuEngine::changeDimensionMode, 3)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Music", 60, 200, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("On", 180, 200, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[ ]", 210, 200, 20, true, &MenuEngine::changeMusic, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Off", 250, 200, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[ ]", 280, 200, 20, true, &MenuEngine::changeMusic, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Volume", 320, 200, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[-]", 390, 200, 20, true, &MenuEngine::creaseMusicVolume, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[+]", 450, 200, 20, true, &MenuEngine::creaseMusicVolume, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Sound", 60, 230, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("On", 180, 230, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[ ]", 210, 230, 20, true, &MenuEngine::changeSound, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Off", 250, 230, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[ ]", 280, 230, 20, true, &MenuEngine::changeSound, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Volume", 320, 230, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[-]", 390, 230, 20, true, &MenuEngine::creaseSoundVolume, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[+]", 450, 230, 20, true, &MenuEngine::creaseSoundVolume, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Control", 40, 270, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("General", 60, 300, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Pause", 180, 300, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 250, 300, 100, true, &MenuEngine::changePause, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Camera", 60, 330, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Up", 180, 330, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 250, 330, 100, true, &MenuEngine::changeUpCamera, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Down", 360, 330, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 430, 330, 100, true, &MenuEngine::changeDownCamera, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Gamer 1", 60, 360, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Up", 180, 360, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 250, 360, 100, true, &MenuEngine::changeUpGamer, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Left", 360, 360, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 430, 360, 100, true, &MenuEngine::changeLeftGamer, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Bomb", 540, 360, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 610, 360, 100, true, &MenuEngine::changeBombGamer, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Down", 180, 390, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 250, 390, 100, true, &MenuEngine::changeDownGamer, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Right", 360, 390, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 430, 390, 100, true, &MenuEngine::changeRightGamer, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Ctrl", 540, 390, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 610, 390, 100, true, &MenuEngine::changeCtrlGamer, 1)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Gamer 2", 60, 420, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Up", 180, 420, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 250, 420, 100, true, &MenuEngine::changeUpGamer, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Left", 360, 420, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 430, 420, 100, true, &MenuEngine::changeLeftGamer, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Bomb", 540, 420, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 610, 420, 100, true, &MenuEngine::changeBombGamer, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Down", 180, 450, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 250, 450, 100, true, &MenuEngine::changeDownGamer, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Right", 360, 450, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 430, 450, 100, true, &MenuEngine::changeRightGamer, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Ctrl", 540, 450, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("[                ]", 610, 450, 100, true, &MenuEngine::changeCtrlGamer, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Preferences, MenuEngine::Button("Return", 40, 480, 70, true, &MenuEngine::goToMenu, Modes::Main)));
  /* PauseAdventure Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseAdventure, MenuEngine::Button("-- PAUSE --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseAdventure, MenuEngine::Button("Save game", 40, 140, 100, true, &MenuEngine::saveGame, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseAdventure, MenuEngine::Button("Resume game", 40, 180, 150, true, &MenuEngine::launchGame, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseAdventure, MenuEngine::Button("Quit game", 40, 220, 120, true, &MenuEngine::goToMenu, Modes::Main)));
  /* PauseEditor Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseEditor, MenuEngine::Button("-- PAUSE --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseEditor, MenuEngine::Button("Save map", 40, 140, 85, true, &MenuEngine::saveMap, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseEditor, MenuEngine::Button("as", 140, 140, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseEditor, MenuEngine::Button(" ", 180, 140, 15, true, &MenuEngine::creaseMapName, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseEditor, MenuEngine::Button(" ", 197, 140, 15, true, &MenuEngine::creaseMapName, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseEditor, MenuEngine::Button(" ", 214, 140, 15, true, &MenuEngine::creaseMapName, 4)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseEditor, MenuEngine::Button(" ", 231, 140, 15, true, &MenuEngine::creaseMapName, 6)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseEditor, MenuEngine::Button(" ", 248, 140, 15, true, &MenuEngine::creaseMapName, 8)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseEditor, MenuEngine::Button("Resume editor", 40, 180, 150, true, &MenuEngine::launchGame, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseEditor, MenuEngine::Button("Quit editor", 40, 220, 120, true, &MenuEngine::goToMenu, Modes::Main)));
  /* PauseFree Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseFree, MenuEngine::Button("-- PAUSE --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseFree, MenuEngine::Button("Resume game", 40, 140, 150, true, &MenuEngine::launchGame, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::PauseFree, MenuEngine::Button("Quit game", 40, 180, 120, true, &MenuEngine::goToMenu, Modes::Main)));
  /* Win Menu */
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Win, MenuEngine::Button("-- GAME OVER --", 40, 70, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Win, MenuEngine::Button("Score", 70, 180, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Win, MenuEngine::Button("Name", 70, 220, 0, false, &MenuEngine::goToMenu, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Win, MenuEngine::Button(" ", 150, 220, 15, true, &MenuEngine::creaseScoreName, 0)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Win, MenuEngine::Button(" ", 167, 220, 15, true, &MenuEngine::creaseScoreName, 2)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Win, MenuEngine::Button(" ", 183, 220, 15, true, &MenuEngine::creaseScoreName, 4)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Win, MenuEngine::Button(" ", 150, 340, 15, true, &MenuEngine::creaseScoreName, 5)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Win, MenuEngine::Button(" ", 167, 340, 15, true, &MenuEngine::creaseScoreName, 7)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Win, MenuEngine::Button(" ", 183, 340, 15, true, &MenuEngine::creaseScoreName, 9)));
  this->menusContent_.insert(MenuEngine::t_menuelem(Modes::Win, MenuEngine::Button("Save", 40, 380, 80, true, &MenuEngine::saveScore, 0)));
}

MenuEngine::~MenuEngine(void)
{
  this->menusContent_.clear();
}

MenuEngine::Button::Button(const std::string& text, const int x, const int y, const int width,
			   const bool interactive, Modes::Mode (MenuEngine::*fct)(int), int arg)
  : text_(text), x_(x), y_(y), width_(width), interactive_(interactive), fct_(fct), arg_(arg)
{
}

MenuEngine::Button::Button(const MenuEngine::Button& other)
  : text_(other.text_), x_(other.x_), y_(other.y_), width_(other.width_),
    interactive_(other.interactive_), fct_(other.fct_), arg_(other.arg_)
{
}

MenuEngine::Button::~Button(void)
{
}

/**************************
***** Menu navigation *****
**************************/

void			MenuEngine::switchPause(void)
{
  if (this->ModeGame == Modes::NextStage)
    this->currentMenu_ = Modes::Stage;
  else if (this->ModeGame == Modes::EditorGame)
    this->currentMenu_ = Modes::PauseEditor;
  else
    {
      if ((this->player1->getStatus() == Model::NONE && this->getPlayers() == 1) ||
	  (this->player1->getStatus() == Model::NONE && this->player2->getStatus() == Model::NONE && this->getPlayers() == 2))
	this->currentMenu_ = (this->ModeGame == Modes::FreeGame) ? Modes::PauseFree : Modes::PauseAdventure;
      else
	this->currentMenu_ = Modes::Win;
    }
}

Modes::Mode		MenuEngine::goToMenu(int menu)
{
  if (menu == Modes::Config || menu == Modes::LoadMaps || menu == Modes::Editor)
    this->setDefaultConfig();
  if (menu != 0)
    this->currentMenu_ = static_cast<Modes::ModeMenu>(menu);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::launchGame(int game)
{
  if (game == 1)
    {
      this->setDefaultConfig();
      this->ModeGame = Modes::FreeGame;
    }
  else if (game == 2)
    {
      this->setRandomConfig();
      this->ModeGame = Modes::FreeGame;
    }
  else if (game == 3)
    this->ModeGame = Modes::FreeGame;
  else if (game == 4)
    {
      this->setTotalScore(0);
      this->initStage();
      this->setAdventureConfig();
      this->ModeGame = Modes::AdventureGame;
    }
  else if (game == 5)
    {
      this->setEditorConfig();
      this->ModeGame = Modes::EditorGame;
    }
  if (game != 0)
    this->setConfig();
  this->currentMenu_ = Modes::SwitchPause;
  return (Modes::Game);
}

Modes::Mode		MenuEngine::loadGame(int nbr)
{
  const std::multimap<time_t, const XmlEngine::Save>& saves = this->xml.getSaves();
  std::multimap<time_t, const XmlEngine::Save>::const_reverse_iterator it = saves.rbegin();

  for (int count = 0; count < this->savesIterator_ + nbr && it != saves.rend(); count++)
    ++it;
  if (it != saves.rend())
    {
      this->setStage(it->second.stage);
      this->setAdventureConfig();
      this->ModeGame = Modes::AdventureGame;
      this->setConfig();
      this->setTotalScore(it->second.score);
      this->currentMenu_ = Modes::SwitchPause;
      return (Modes::Game);
    }
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::loadMap(int nbr)
{
  const std::multimap<const std::string, const XmlEngine::Map>& maps = this->xml.getMaps();
  std::multimap<const std::string, const XmlEngine::Map>::const_iterator it = maps.begin();

  for (int count = 0; count < this->mapsIterator_ + nbr && it != maps.end(); count++)
    ++it;
  if (it != maps.end())
    {
      this->setLoadMapConfig(it->second.width, it->second.height);
      this->ModeGame = Modes::FreeGame;
      this->setConfig();
      // a revoir car gamer peuvent apparaitre sur box (normal car set box d'en-dessous est apres this->setConfig())
      for (unsigned int i = 0; i < it->second.boxes.size(); i++)
	{
	  Map::Box *box = new Map::Box(this, this->texture_Box);
	  Case currentCase = this->map.getCase(it->second.boxes[i].x, it->second.boxes[i].z);
	  box->setX(currentCase.getXmin());
	  box->setZ(currentCase.getYmin());
	  box->initialize();
	  this->listBoxes.push_back(box);
	  this->map.addBox(it->second.boxes[i].x, it->second.boxes[i].z);
	}
      this->currentMenu_ = Modes::SwitchPause;
      return (Modes::Game);
    }
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::quit(int)
{
  return (Modes::Quit);
}

/***************************
***** Var modification *****
***************************/

Modes::Mode		MenuEngine::creaseMusicVolume(int mode)
{
  int			volume = this->getMusicVolume();

  volume += (mode == 1) ? 1 : -1;
  if ((mode == 1 && volume <= AudioEngine::MaxVolume) ||
      (mode == 2 && volume >= AudioEngine::MinVolume))
    this->setMusicVolume(volume);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::creaseSoundVolume(int mode)
{
  int			volume = this->getSoundVolume();

  volume += (mode == 1) ? 1 : -1;
  if ((mode == 1 && volume <= AudioEngine::MaxVolume) ||
      (mode == 2 && volume >= AudioEngine::MinVolume))
    this->setSoundVolume(volume);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::creaseMapWidth(int mode)
{
  int			width = this->getMapWidth();

  width += (mode == 1) ? 1 : -1;
  if (mode == 1 || (mode == 2 && width >= ConfigEngine::MinMapWidth))
    this->setMapWidth(width);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::creaseMapHeight(int mode)
{
  int			height = this->getMapHeight();

  height += (mode == 1) ? 1 : -1;
  if (mode == 1 || (mode == 2 && height >= ConfigEngine::MinMapHeight))
    this->setMapHeight(height);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::creasePlayers(int mode)
{
  int			players = this->getPlayers();

  players += (mode == 1) ? 1 : -1;
  if ((mode == 1 && players <= ConfigEngine::MaxPlayers) ||
      (mode == 2 && players >= ConfigEngine::MinPlayers))
    this->setPlayers(players);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::creaseEnemies(int mode)
{
  int			enemies = this->getEnemies();

  enemies += (mode == 1) ? 1 : -1;
  if (mode == 1 || (mode == 2 && enemies >= ConfigEngine::MinEnemies))
    this->setEnemies(enemies);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::creaseBoxPercent(int mode)
{
  int			boxPercent = this->getBoxPercent();

  boxPercent += (mode == 1) ? 1 : -1;
  if ((mode == 1 && boxPercent <= ConfigEngine::MaxBoxPercent) ||
      (mode == 2 && boxPercent >= ConfigEngine::MinBoxPercent))
    this->setBoxPercent(boxPercent);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::creaseScoreName(int i)
{
  static int		tmp = -1;
  int			pos = (i < 5) ? i : i - 5;
  std::string&		name = (i < 5) ? this->scoreName1_ : this->scoreName2_;

  if (tmp == i)
    {
      if (++name[pos] > 'Z')
	name[pos] = '0';
      else if (name[pos] < 'A' && name[pos] > '9')
	name[pos] = 'A';
      tmp = -1;
    }
  else
    tmp = i;
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::creaseMapName(int pos)
{
  static int		tmp = -1;

  if (tmp == pos)
    {
      if (++this->mapName_[pos] > 'Z')
	this->mapName_[pos] = '0';
      else if (this->mapName_[pos] < 'A' && this->mapName_[pos] > '9')
	this->mapName_[pos] = 'A';
      tmp = -1;
    }
  else
    tmp = pos;
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeDimensionMode(int dim)
{
  if (dim == 2)
    this->setGameMode(WindowEngine::TWOD);
  else if (dim == 3)
    this->setGameMode(WindowEngine::TREED);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeMusic(int status)
{
  this->setMusicStatus(static_cast<bool>(status));
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeSound(int status)
{
  this->setSoundStatus(static_cast<bool>(status));
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeUpGamer(int gamer)
{
  if (gamer == 1)
    this->changeEvent(InputEngine::UpGamer1);
  else if (gamer == 2)
    this->changeEvent(InputEngine::UpGamer2);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeDownGamer(int gamer)
{
  if (gamer == 1)
    this->changeEvent(InputEngine::DownGamer1);
  else if (gamer == 2)
    this->changeEvent(InputEngine::DownGamer2);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeLeftGamer(int gamer)
{
  if (gamer == 1)
    this->changeEvent(InputEngine::LeftGamer1);
  else if (gamer == 2)
    this->changeEvent(InputEngine::LeftGamer2);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeRightGamer(int gamer)
{
  if (gamer == 1)
    this->changeEvent(InputEngine::RightGamer1);
  else if (gamer == 2)
    this->changeEvent(InputEngine::RightGamer2);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeBombGamer(int gamer)
{
  if (gamer == 1)
    this->changeEvent(InputEngine::BombGamer1);
  else if (gamer == 2)
    this->changeEvent(InputEngine::BombGamer2);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeCtrlGamer(int gamer)
{
  if (gamer == 1)
    this->changeEvent(InputEngine::CtrlGamer1);
  else if (gamer == 2)
    this->changeEvent(InputEngine::CtrlGamer2);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeUpCamera(int)
{
  this->changeEvent(InputEngine::UpCamera);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeDownCamera(int)
{
  this->changeEvent(InputEngine::DownCamera);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeSavesIterator(int diff)
{
  if (diff < 0 && (this->savesIterator_ + diff) >= 0)
    this->savesIterator_ += diff;
  else if (diff > 0)
    {
      const std::multimap<time_t, const XmlEngine::Save>& saves = this->xml.getSaves();
      if ((this->savesIterator_ + diff) < static_cast<int>(saves.size()))
	this->savesIterator_ += diff;
    }
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changeMapsIterator(int diff)
{
  if (diff < 0 && (this->mapsIterator_ + diff) >= 0)
    this->savesIterator_ += diff;
  else if (diff > 0)
    {
      const std::multimap<const std::string, const XmlEngine::Map>& maps = this->xml.getMaps();
      if ((this->mapsIterator_ + diff) < static_cast<int>(maps.size()))
	this->mapsIterator_ += diff;
    }
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::changePause(int)
{
  this->changeEvent(InputEngine::Pause);
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::saveScore(int)
{
  if (this->ModeGame == Modes::AdventureGame)
    this->xml.saveScore(this->scoreName1_, this->getTotalScore());
  else
    {
      this->xml.saveScore(this->scoreName1_, this->player1->getScore());
      if (this->getPlayers() == 2)
	this->xml.saveScore(this->scoreName2_, this->player2->getScore());
    }
  this->currentMenu_ = Modes::Main;
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::saveGame(int)
{
  this->xml.saveGame();
  this->currentMenu_ = Modes::Main;
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::saveMap(int)
{
  this->xml.saveMap(this->mapName_);
  this->currentMenu_ = Modes::Main;
  return (Modes::Menu);
}

/*****************
***** Update *****
*****************/

Modes::Mode		MenuEngine::updateStage(void)
{
  if (this->isClicked(0, this->getWidthAdapt(800), 0, this->getHeightAdapt(600)))
    {
      this->ModeGame = Modes::AdventureGame;
      this->currentMenu_ = Modes::SwitchPause;
      return (Modes::Game);
    }
  return (Modes::Menu);
}

Modes::Mode		MenuEngine::updateMenu(void)
{
  if (this->currentMenu_ == Modes::SwitchPause)
    this->switchPause();
  else if (this->currentMenu_ == Modes::Stage)
    return (this->updateStage());
  else
    {
      MenuEngine::t_menumap::iterator it = this->menusContent_.begin();
      for (; it != this->menusContent_.end(); ++it)
	if (this->currentMenu_ == it->first && it->second.interactive_ &&
	    this->isClicked(this->getWidthAdapt(it->second.x_), this->getWidthAdapt(it->second.x_ + it->second.width_), this->getHeightAdapt(it->second.y_), this->getHeightAdapt(it->second.y_ + this->fontSize_)))
	  return ((this->*it->second.fct_)(it->second.arg_));
    }
  return (Modes::Menu);
}

/***************
***** Draw *****
***************/

void			MenuEngine::drawConfig(void) const
{
  this->displayText(Common::stringOfNbr<int>(this->getMapWidth()), White, this->fontSize_, 235, 140);
  this->displayText(Common::stringOfNbr<int>(this->getMapHeight()), White, this->fontSize_, 235, 170);
  this->displayText(Common::stringOfNbr<int>(this->getPlayers()), White, this->fontSize_, 235, 210);
  this->displayText(Common::stringOfNbr<int>(this->getEnemies()), White, this->fontSize_, 235, 240);
  this->displayText(Common::stringOfNbr<int>(this->getBoxPercent()), White, this->fontSize_, 235, 280);
}

void			MenuEngine::drawLoadSaves(void) const
{
  const std::multimap<time_t, const XmlEngine::Save>& saves = this->xml.getSaves();
  std::multimap<time_t, const XmlEngine::Save>::const_reverse_iterator it = saves.rbegin();

  for (int y = 180, nbr = 0, count = 0; it != saves.rend() && count < 8; ++it, nbr++)
    if (nbr >= this->savesIterator_)
      {
	this->displayText(ctime(&it->first), White, this->fontSize_, 70, y);
	this->displayText(Common::stringOfNbr<int>(it->second.stage), White, this->fontSize_, 300, y);
	this->displayText(Common::stringOfNbr<int>(it->second.score), White, this->fontSize_, 380, y);
	this->displayText("[Launch]", White, this->fontSize_, 480, y);
	y += 30;
	++count;
      }
}

void			MenuEngine::drawLoadMaps(void) const
{
  const std::multimap<const std::string, const XmlEngine::Map>& maps = this->xml.getMaps();
  std::multimap<const std::string, const XmlEngine::Map>::const_iterator it = maps.begin();

  this->displayText(Common::stringOfNbr<int>(this->getPlayers()), White, this->fontSize_, 235, 140);
  this->displayText(Common::stringOfNbr<int>(this->getEnemies()), White, this->fontSize_, 235, 170);
  for (int y = 270, nbr = 0, count = 0; it != maps.end() && count < 6; ++it, nbr++)
    if (nbr >= this->mapsIterator_)
      {
	this->displayText(it->first, White, this->fontSize_, 70, y);
	this->displayText(Common::stringOfNbr<int>(it->second.width), White, this->fontSize_, 200, y);
	this->displayText(Common::stringOfNbr<int>(it->second.height), White, this->fontSize_, 280, y);
	this->displayText("[Launch]", White, this->fontSize_, 380, y);
	y += 30;
	++count;
      }
}

void			MenuEngine::drawScores(void)
{
  const std::multimap<int, const std::string>& scores1 = this->xml.getScores(Modes::AdventureGame);
  const std::multimap<int, const std::string>& scores2 = this->xml.getScores(Modes::FreeGame);
  std::multimap<int, const std::string>::const_reverse_iterator it1 = scores1.rbegin();
  std::multimap<int, const std::string>::const_reverse_iterator it2 = scores2.rbegin();

  for (int y = 180; y < 270 && it1 != scores1.rend(); ++it1, y += 30)
    {
      this->displayText(it1->second, White, this->fontSize_, 120, y);
      this->displayText(Common::stringOfNbr<int>(it1->first), White, this->fontSize_, 180, y);
    }
  for (int y = 320; y < 410 && it2 != scores2.rend(); ++it2, y += 30)
    {
      this->displayText(it2->second, White, this->fontSize_, 120, y);
      this->displayText(Common::stringOfNbr<int>(it2->first), White, this->fontSize_, 180, y);
    }
}

void			MenuEngine::drawWin(void) const
{
  if (this->getPlayers() == 1)
    this->displayText("You", White, this->fontSize_, 40, 140);
  else
    this->displayText("Gamer1", White, this->fontSize_, 40, 140);
  if (this->player1->getStatus() == Model::WIN)
    this->displayText("Win !", White, this->fontSize_, 115, 140);
  else if (this->player1->getStatus() == Model::LOOSE)
    this->displayText("Lose !", White, this->fontSize_, 115, 140);
  if (this->ModeGame == Modes::AdventureGame)
    this->displayText(Common::stringOfNbr<int>(this->getTotalScore()), White, this->fontSize_, 150, 180);
  else
    this->displayText(Common::stringOfNbr<int>(this->player1->getScore()), White, this->fontSize_, 150, 180);
  this->displayText(this->scoreName1_, White, this->fontSize_, 150, 220);
  if (this->getPlayers() == 2)
    {
      this->displayText("Gamer2", White, this->fontSize_, 40, 260);
      if (this->player2->getStatus() == Model::WIN)
	this->displayText("Win !", White, this->fontSize_, 115, 260);
      else if (this->player2->getStatus() == Model::LOOSE)
	this->displayText("Lose !", White, this->fontSize_, 115, 260);
      this->displayText("Score", White, this->fontSize_, 70, 300);
      this->displayText("Name", White, this->fontSize_, 70, 340);
      this->displayText(Common::stringOfNbr<int>(this->player2->getScore()), White, this->fontSize_, 150, 300);
      this->displayText(this->scoreName2_, White, this->fontSize_, 150, 340);
    }
}

void			MenuEngine::drawPreferences(void) const
{
  this->displayText("x", White, this->fontSize_, ((this->getGameMode() == WindowEngine::TWOD) ? 213 : 283), 170);
  this->displayText("x", White, this->fontSize_, ((this->getMusicStatus()) ? 213 : 283), 200);
  this->displayText(Common::stringOfNbr<int>(this->getMusicVolume()), White, this->fontSize_, 413, 200);
  this->displayText("x", White, this->fontSize_, ((this->getSoundStatus()) ? 213 : 283), 230);
  this->displayText(Common::stringOfNbr<int>(this->getSoundVolume()), White, this->fontSize_, 413, 230);
  this->displayText(this->getStringKeyOfEvent(InputEngine::Pause), White, this->fontSize_, 257, 300);
  this->displayText(this->getStringKeyOfEvent(InputEngine::UpCamera), White, this->fontSize_, 257, 330);
  this->displayText(this->getStringKeyOfEvent(InputEngine::DownCamera), White, this->fontSize_, 437, 330);
  this->displayText(this->getStringKeyOfEvent(InputEngine::UpGamer1), White, this->fontSize_, 257, 360);
  this->displayText(this->getStringKeyOfEvent(InputEngine::LeftGamer1), White, this->fontSize_, 437, 360);
  this->displayText(this->getStringKeyOfEvent(InputEngine::BombGamer1), White, this->fontSize_, 617, 360);
  this->displayText(this->getStringKeyOfEvent(InputEngine::DownGamer1), White, this->fontSize_, 257, 390);
  this->displayText(this->getStringKeyOfEvent(InputEngine::RightGamer1), White, this->fontSize_, 437, 390);
  this->displayText(this->getStringKeyOfEvent(InputEngine::CtrlGamer1), White, this->fontSize_, 617, 390);
  this->displayText(this->getStringKeyOfEvent(InputEngine::UpGamer2), White, this->fontSize_, 257, 420);
  this->displayText(this->getStringKeyOfEvent(InputEngine::LeftGamer2), White, this->fontSize_, 437, 420);
  this->displayText(this->getStringKeyOfEvent(InputEngine::BombGamer2), White, this->fontSize_, 617, 420);
  this->displayText(this->getStringKeyOfEvent(InputEngine::DownGamer2), White, this->fontSize_, 257, 450);
  this->displayText(this->getStringKeyOfEvent(InputEngine::RightGamer2), White, this->fontSize_, 437, 450);
  this->displayText(this->getStringKeyOfEvent(InputEngine::CtrlGamer2), White, this->fontSize_, 617, 450);
}

void			MenuEngine::drawEditor(void) const
{
  this->displayText(Common::stringOfNbr<int>(this->getMapWidth()), White, this->fontSize_, 235, 140);
  this->displayText(Common::stringOfNbr<int>(this->getMapHeight()), White, this->fontSize_, 235, 180);
}

void			MenuEngine::drawPauseEditor(void) const
{
  this->displayText(this->mapName_, White, this->fontSize_, 180, 140);
}

void			MenuEngine::drawMenu(void)
{
  int			fontSize;
  MenuEngine::t_menumap::const_iterator it = this->menusContent_.begin();

  if (this->currentMenu_ == Modes::Stage)
    this->displayImage("img/next.jpg", 0, 0, 800, 600);
  else
    {
      this->displayImage("img/menu.jpg", 0, 0, 800, 600);
      for (; it != this->menusContent_.end(); ++it)
	if (this->currentMenu_ == it->first)
	  {
	    fontSize = this->fontSize_;
	    if (it->second.interactive_ && this->isOnHover(this->getWidthAdapt(it->second.x_), this->getWidthAdapt(it->second.x_ + it->second.width_), this->getHeightAdapt(it->second.y_), this->getHeightAdapt(it->second.y_ + this->fontSize_)))
	      fontSize += 2;
	    this->displayText(it->second.text_, this->fontColor_, fontSize, it->second.x_, it->second.y_);
	  }
      if (this->currentMenu_ == Modes::Config)
	this->drawConfig();
      else if (this->currentMenu_ == Modes::LoadSaves)
	this->drawLoadSaves();
      else if (this->currentMenu_ == Modes::LoadMaps)
	this->drawLoadMaps();
      else if (this->currentMenu_ == Modes::Scores)
	this->drawScores();
      else if (this->currentMenu_ == Modes::Preferences)
	this->drawPreferences();
      else if (this->currentMenu_ == Modes::Editor)
	this->drawEditor();
      else if (this->currentMenu_ == Modes::PauseEditor)
	this->drawPauseEditor();
      else if (this->currentMenu_ == Modes::Win)
	this->drawWin();
    }
  this->displayText("", White, 0, 0, 0);
}
