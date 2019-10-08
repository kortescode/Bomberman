#ifndef		EDITOR_HH_
# define	EDITOR_HH_

# include	"Case.hh"
# include	"AObject.hh"
# include	"ConfigEngine.hh"

class		Editor : public AObject
{
  float		doMove(void);
  bool		canGo(CaseType);
  void		updateMap(Case&);

  gdl::Image	texture_;
  static const int	size = 150;

public:
  typedef struct	s_side
  {
    Side		side;
    float		(Editor::*fct)(Case &, float, int);
  }			t_side;

  Editor(ConfigEngine*);
  ~Editor(void);

  float		goRight(Case&, float, int);
  float		goLeft(Case&, float, int);
  float		goUp(Case&, float, int);
  float		goDown(Case&, float, int);

  void		initialize(void);
  void		update(void);
  void		draw(void);
};

#endif		/* !EDITOR_HH_ */
