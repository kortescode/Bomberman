#ifndef		CASE_HH_
# define	CASE_HH_

enum	CaseType
  {
    BOX,
    BOX_EX,
    FLOOR,
    WALL,
    BOMB,
    FIRE,
    FIRE_BONUS,
    BONUS,
    PLAYER
  };

class	Case
{
  double	xMin_;
  double	xMax_;
  double	yMin_;
  double	yMax_;
  CaseType	type_;

public:
  Case();
  Case(double, double, double, double, CaseType);

  void		setXmin(double);
  void		setXmax(double);
  void		setYmin(double);
  void		setYmax(double);
  void		setType(CaseType);
  void		setWBomb(int);
  void		setWUnit(int);
  void		setWPower(int);
  double	getXmin() const;
  double	getXmax() const;
  double	getYmin() const;
  double	getYmax() const;
  CaseType	getType() const;
  int		getWBomb() const;
  int		getWUnit() const;
  int		getWPower() const;
  bool		isInCase(double, double) const;
};

bool		operator!=(const Case &, const Case &);

#endif	// !CASE_HH_
