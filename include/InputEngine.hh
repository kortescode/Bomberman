#ifndef		       	INPUTENGINE_HH_
# define	       	INPUTENGINE_HH_

# include	       	<string>
# include	       	<map>
# include	       	"Game.hpp"
# include      		"Input.hpp"

/******************************
***** KeyCorres structure *****
******************************/

# define       		END	-1

struct		       	KeyCorres
{
  gdl::Keys::Key       	key_;
  const std::string   	name_;
};

extern KeyCorres      	keyCorres[];

/****************************
***** InputEngine class *****
****************************/

class		       	InputEngine : virtual public gdl::Game
{
public:
  enum		      	Event
    {
      None, UpGamer1, DownGamer1, LeftGamer1,
      RightGamer1, BombGamer1, CtrlGamer1, UpGamer2,
      DownGamer2, LeftGamer2, RightGamer2,
      BombGamer2, CtrlGamer2, UpCamera, DownCamera,
      Pause
    };

  struct	      	KeyInfo
  {
    const std::string 	name_;
    InputEngine::Event  event_;
    bool	        isPressed_;

    KeyInfo(const std::string&, InputEngine::Event = InputEngine::None, bool = false);
    ~KeyInfo(void);
  };

  typedef std::map<gdl::Keys::Key, InputEngine::KeyInfo*>	t_keymap;

private:
  InputEngine::t_keymap	keyTab_;

public:
  InputEngine(void);
  ~InputEngine(void);

  void	       		updateKeyTab(void);

  bool	       		changeEvent(InputEngine::Event);

  const std::string	getStringKeyOfEvent(InputEngine::Event) const;

  bool 			isPressed(InputEngine::Event) const;
  bool	       		isOnHover(int, int, int, int) const;
  bool		       	isClicked(int, int, int, int);
};

#endif		       	/* INPUTENGINE_HH_ */
