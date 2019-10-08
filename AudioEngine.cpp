#include	<list>
#include	<iostream>
#include	<string>
#include	<SFML/Audio.hpp>
#include	"AudioEngine.hh"
#include	"Modes.hh"

AudioEngine::AudioEngine(void)
  : musicStatus_(true), soundStatus_(true), musicVolume_(50), soundVolume_(50), currentMode_(Modes::Intro),
    introMusic_("music/bonus_stage.ogg"), menuMusic_("music/title_screen.ogg"), gameMusic_("music/stage_bgm2.ogg")
{
}

AudioEngine::~AudioEngine(void)
{
  this->music_.Stop();
  for (std::list<sf::Music*>::iterator it = this->sound_.begin(); it != this->sound_.end(); ++it)
    {
      (*it)->Stop();
      delete *it;
    }
  this->sound_.clear();
}

void		AudioEngine::loadMusic(const std::string& path)
{
  if (!this->music_.OpenFromFile(path))
    this->musicStatus_ = false;
}

void		AudioEngine::playMusic(void)
{
  this->music_.Play();
}

void		AudioEngine::pauseMusic(void)
{
  this->music_.Pause();
}

void		AudioEngine::stopMusic(void)
{
  this->music_.Stop();
}

void		AudioEngine::playSoundEffect(const std::string& path)
{
  if (this->soundStatus_)
    {
      if (this->sound_.size() > 0 && this->sound_.front()->GetStatus() == sf::Sound::Stopped)
	{
	  delete this->sound_.front();
	  this->sound_.pop_front();
	}
      this->sound_.push_back(new sf::Music);
      if (this->sound_.back()->OpenFromFile(path))
	{
	  this->sound_.back()->SetVolume(this->soundVolume_);
	  this->sound_.back()->Play();
	}
    }
}

void		AudioEngine::updateMusic(Modes::Mode newMode)
{
  if (!this->musicStatus_)
    this->stopMusic();
  else if (this->musicStatus_ && (newMode != this->currentMode_ || this->music_.GetStatus() == sf::Sound::Stopped))
    {
      this->stopMusic();
      if (newMode == Modes::Intro)
	this->loadMusic(this->introMusic_);
      else if (newMode == Modes::Menu)
	this->loadMusic(this->menuMusic_);
      else if (newMode == Modes::Game)
	this->loadMusic(this->gameMusic_);
      this->music_.SetLoop(true);
      this->playMusic();
      this->currentMode_ = newMode;
    }
  this->music_.SetVolume(this->musicVolume_);
}

int		AudioEngine::getMusicVolume(void) const
{
  return (this->musicVolume_);
}

int		AudioEngine::getSoundVolume(void) const
{
  return (this->soundVolume_);
}

bool		AudioEngine::getMusicStatus(void) const
{
  return (this->musicStatus_);
}

bool		AudioEngine::getSoundStatus(void) const
{
  return (this->soundStatus_);
}

void		AudioEngine::setMusicVolume(int volume)
{
  this->musicVolume_ = volume;
}

void		AudioEngine::setSoundVolume(int volume)
{
  this->soundVolume_ = volume;
}

void		AudioEngine::setMusicStatus(bool status)
{
  this->musicStatus_ = status;
}

void		AudioEngine::setSoundStatus(bool status)
{
  this->soundStatus_ = status;
}
