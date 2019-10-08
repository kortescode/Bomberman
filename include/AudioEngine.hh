#ifndef			AUDIOENGINE_HH_
# define		AUDIOENGINE_HH_

# include		<list>
# include		<string>
# include		<SFML/Audio.hpp>
# include		"Modes.hh"

class			AudioEngine
{
  bool			musicStatus_;
  bool			soundStatus_;

  int			musicVolume_;
  int			soundVolume_;

  sf::Music		music_;
  std::list<sf::Music*>	sound_;
  Modes::Mode		currentMode_;

  const std::string	introMusic_;
  const std::string	menuMusic_;
  const std::string	gameMusic_;

protected:
  void			loadMusic(const std::string&);
  void			playMusic(void);
  void			pauseMusic(void);
  void			stopMusic(void);

public:
  static const int     	MinVolume = 0;
  static const int     	MaxVolume = 100;

  AudioEngine(void);
  ~AudioEngine(void);

  void			playSoundEffect(const std::string&);

  void			updateMusic(Modes::Mode);

  int			getMusicVolume(void) const;
  int			getSoundVolume(void) const;
  bool			getMusicStatus(void) const;
  bool			getSoundStatus(void) const;

  void			setMusicVolume(int);
  void			setSoundVolume(int);
  void			setMusicStatus(bool);
  void			setSoundStatus(bool);
};

#endif			/* !AUDIOENGINE_HH_ */
