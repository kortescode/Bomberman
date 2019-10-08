//
// Brain.hh for Bomberman in /home/sabbe_k//Tek2/Rendu/bomberman-2015-sabbe_k/bomberman
// 
// Made by kevin sabbe
// Login   <sabbe_k@epitech.net>
// 
// Started on  Thu May 31 14:17:48 2012 kevin sabbe
// Last update Fri Jun  1 18:46:39 2012 kevin sabbe
//

#ifndef		BRAIN_HH_
# define	BRAIN_HH_

# include	"AIDefine.hh"

class		Brain
{
private:
  State			_state;
  Action		_action;
  posXY			_destination;
public:
  Brain();
  Brain(const Brain &other);
  Brain & operator=(const Brain &other);
  ~Brain();
public:
  void		setState(State S);
  void		setAction(Action A);
  void		setDestination(posXY P, Action A);
  void		setDestination(posXY P);
  State		getState() const;
  Action	getAction() const;
  posXY		getDestination() const;
};

#endif
