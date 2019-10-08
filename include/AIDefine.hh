#ifndef		AIDEFINE_HH_
# define	AIDEFINE_HH_

typedef enum State { _ATTACK, _SURVIVE, _EXPLORE, _COLLECT } State;
typedef enum Action { _THINK, _UP, _RIGHT, _DOWN, _LEFT, _BOMB } Decision;

struct	posXY
{
  posXY() : X(), Y() {}
  posXY(int x, int y)
    : X(x), Y(y) {}

  int		X;
  int		Y;
};

#endif
