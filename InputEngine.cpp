#include		<iostream>
#include		<string>
#include		<map>
#include		"Input.hpp"
#include		"InputEngine.hh"

/************************
***** keyCorres tab *****
************************/

KeyCorres		keyCorres[] =
  {
    {gdl::Keys::A, "A"}, {gdl::Keys::B, "B"}, {gdl::Keys::C, "C"}, {gdl::Keys::D, "D"},
    {gdl::Keys::E, "E"}, {gdl::Keys::F, "F"}, {gdl::Keys::G, "G"}, {gdl::Keys::H, "H"},
    {gdl::Keys::I, "I"}, {gdl::Keys::J, "J"}, {gdl::Keys::K, "K"}, {gdl::Keys::L, "L"},
    {gdl::Keys::M, "M"}, {gdl::Keys::N, "N"}, {gdl::Keys::O, "O"}, {gdl::Keys::P, "P"},
    {gdl::Keys::Q, "Q"}, {gdl::Keys::R, "R"}, {gdl::Keys::S, "S"}, {gdl::Keys::T, "T"},
    {gdl::Keys::U, "U"}, {gdl::Keys::V, "V"}, {gdl::Keys::W, "W"}, {gdl::Keys::X, "X"},
    {gdl::Keys::Y, "Y"}, {gdl::Keys::Z, "Z"}, {gdl::Keys::Num0, "Num0"}, {gdl::Keys::Num1, "Num1"},
    {gdl::Keys::Num2, "Num2"}, {gdl::Keys::Num3, "Num3"}, {gdl::Keys::Num4, "Num4"},
    {gdl::Keys::Num5, "Num5"}, {gdl::Keys::Num6, "Num6"}, {gdl::Keys::Num7, "Num7"},
    {gdl::Keys::Num8, "Num8"}, {gdl::Keys::Num9, "Num9"}, {gdl::Keys::Escape, "Escape"},
    {gdl::Keys::LControl, "LControl"}, {gdl::Keys::LShift, "LShift"}, {gdl::Keys::LAlt, "LAlt"},
    {gdl::Keys::LSystem, "LSystem"}, {gdl::Keys::RControl, "RControl"}, {gdl::Keys::RShift, "RShift"},
    {gdl::Keys::RAlt, "RAlt"}, {gdl::Keys::RSystem, "RSystem"}, {gdl::Keys::Menu, "Menu"},
    {gdl::Keys::LBracket, "LBracket"}, {gdl::Keys::RBracket, "RBracket"},
    {gdl::Keys::SemiColon, "SemiColon"}, {gdl::Keys::Comma, "Comma"}, {gdl::Keys::Period, "Period"},
    {gdl::Keys::Quote, "Quote"}, {gdl::Keys::Slash, "Slash"}, {gdl::Keys::BackSlash, "BackSlash"},
    {gdl::Keys::Tilde, "Tilde"}, {gdl::Keys::Equal, "Equal"}, {gdl::Keys::Dash, "Dash"},
    {gdl::Keys::Space, "Space"}, {gdl::Keys::Return, "Return"}, {gdl::Keys::Back, "Back"},
    {gdl::Keys::Tab, "Tab"}, {gdl::Keys::PageUp, "PageUp"}, {gdl::Keys::PageDown, "PageDown"},
    {gdl::Keys::End, "End"}, {gdl::Keys::Home, "Home"}, {gdl::Keys::Insert, "Insert"},
    {gdl::Keys::Delete, "Delete"}, {gdl::Keys::Add, "Add"}, {gdl::Keys::Subtract, "Subtract"},
    {gdl::Keys::Multiply, "Multiply"}, {gdl::Keys::Divide, "Divide"}, {gdl::Keys::Left, "Left"},
    {gdl::Keys::Right, "Right"}, {gdl::Keys::Up, "Up"}, {gdl::Keys::Down, "Down"},
    {gdl::Keys::Numpad0, "Numpad0"}, {gdl::Keys::Numpad1, "Numpad1"}, {gdl::Keys::Numpad2, "Numpad2"},
    {gdl::Keys::Numpad3, "Numpad3"}, {gdl::Keys::Numpad4, "Numpad4"}, {gdl::Keys::Numpad5, "Numpad5"},
    {gdl::Keys::Numpad6, "Numpad6"}, {gdl::Keys::Numpad7, "Numpad7"}, {gdl::Keys::Numpad8, "Numpad8"},
    {gdl::Keys::Numpad9, "Numpad9"}, {gdl::Keys::F1, "F1"}, {gdl::Keys::F2, "F2"},
    {gdl::Keys::F3, "F3"}, {gdl::Keys::F4, "F4"}, {gdl::Keys::F5, "F5"}, {gdl::Keys::F6, "F6"},
    {gdl::Keys::F7, "F7"}, {gdl::Keys::F8, "F8"}, {gdl::Keys::F9, "F9"}, {gdl::Keys::F10, "F10"},
    {gdl::Keys::F11, "F11"}, {gdl::Keys::F12, "F12"}, {gdl::Keys::F13, "F13"}, {gdl::Keys::F14, "F14"},
    {gdl::Keys::F15, "F15"}, {gdl::Keys::Pause, "Pause"}, {gdl::Keys::Count, "Count"},
    {static_cast<gdl::Keys::Key>(END), ""}
  };

/****************************
***** InputEngine class *****
****************************/

InputEngine::KeyInfo::KeyInfo(const std::string& name, InputEngine::Event event, bool isPressed)
  : name_(name), event_(event), isPressed_(isPressed)
{
}

InputEngine::KeyInfo::~KeyInfo(void)
{
}

InputEngine::InputEngine(void)
{
  for (unsigned int i = 0; keyCorres[i].key_ != static_cast<gdl::Keys::Key>(END); i++)
    this->keyTab_[keyCorres[i].key_] = new InputEngine::KeyInfo(keyCorres[i].name_);
  (this->keyTab_[gdl::Keys::W])->event_ = InputEngine::UpGamer1;
  (this->keyTab_[gdl::Keys::S])->event_ = InputEngine::DownGamer1;
  (this->keyTab_[gdl::Keys::A])->event_ = InputEngine::LeftGamer1;
  (this->keyTab_[gdl::Keys::D])->event_ = InputEngine::RightGamer1;
  (this->keyTab_[gdl::Keys::Space])->event_ = InputEngine::BombGamer1;
  (this->keyTab_[gdl::Keys::LShift])->event_ = InputEngine::CtrlGamer1;
  (this->keyTab_[gdl::Keys::Up])->event_ = InputEngine::UpGamer2;
  (this->keyTab_[gdl::Keys::Down])->event_ = InputEngine::DownGamer2;
  (this->keyTab_[gdl::Keys::Left])->event_ = InputEngine::LeftGamer2;
  (this->keyTab_[gdl::Keys::Right])->event_ = InputEngine::RightGamer2;
  (this->keyTab_[gdl::Keys::RControl])->event_ = InputEngine::BombGamer2;
  (this->keyTab_[gdl::Keys::RShift])->event_ = InputEngine::CtrlGamer2;
  (this->keyTab_[gdl::Keys::Add])->event_ = InputEngine::UpCamera;
  (this->keyTab_[gdl::Keys::Subtract])->event_ = InputEngine::DownCamera;
  (this->keyTab_[gdl::Keys::Escape])->event_ = InputEngine::Pause;
}

InputEngine::~InputEngine(void)
{
  InputEngine::t_keymap::iterator it = this->keyTab_.begin();

  for (; it != this->keyTab_.end(); ++it)
    delete it->second;
  this->keyTab_.clear();
}

void			InputEngine::updateKeyTab(void)
{
  InputEngine::t_keymap::iterator it = this->keyTab_.begin();

  for (; it != this->keyTab_.end(); ++it)
    it->second->isPressed_ = false;
  for (unsigned int i = 0; keyCorres[i].key_ != static_cast<gdl::Keys::Key>(END); i++)
    if (this->input_.isKeyDown(keyCorres[i].key_))
      (this->keyTab_[keyCorres[i].key_])->isPressed_ = true;
}

bool			InputEngine::changeEvent(InputEngine::Event event)
{
  int			apply = 0;
  gdl::Keys::Key	key;
  InputEngine::t_keymap::iterator it = this->keyTab_.begin();

  for (; it != this->keyTab_.end(); ++it)
    if (it->second->isPressed_)
      {
	key = it->first;
	++apply;
      }
  if (apply == 1)
    {
      it = this->keyTab_.begin();
      for (; it != this->keyTab_.end(); ++it)
	if (event == it->second->event_)
	  {
	    it->second->event_ = InputEngine::None;
	    break;
	  }
      (this->keyTab_[key])->event_ = event;
      return (true);
    }
  return (false);
}

const std::string	InputEngine::getStringKeyOfEvent(InputEngine::Event event) const
{
  InputEngine::t_keymap::const_iterator it = this->keyTab_.begin();

  for (; it != this->keyTab_.end(); ++it)
    if (event == it->second->event_)
      return (it->second->name_);
  return ("");
}

bool			InputEngine::isPressed(InputEngine::Event event) const
{
  InputEngine::t_keymap::const_iterator it = this->keyTab_.begin();

  for (; it != this->keyTab_.end(); ++it)
    if (event == it->second->event_)
      return ((it->second->isPressed_) ? true : false);
  return (false);
}

bool			InputEngine::isOnHover(int x1, int x2, int y1, int y2) const
{
  int			x = this->input_.getMousePositionX();
  int			y = this->input_.getMousePositionY();

  if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
    return (true);
  return (false);
}

bool			InputEngine::isClicked(int x1, int x2, int y1, int y2)
{
  bool			pressed = this->input_.isMouseButtonDown(gdl::Mouse::Left);

  if (pressed && this->isOnHover(x1, x2, y1, y2))
    return (true);
  return (false);
}
