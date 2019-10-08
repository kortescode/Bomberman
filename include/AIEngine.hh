#ifndef		AIENGINE_HH_
# define	AIENGINE_HH_

# include	<list>
# include	"AIDefine.hh"
# include	"ConfigEngine.hh"
# include	"Map.hh"

class		AiEngine
{
private:
  int			_ID;
  ConfigEngine		*_data;
  std::list<posXY>	_explosionArea;
  std::list<posXY>	_unitPosition;
  int			_updateTime;
  int			_reactionTime;

public:
  AiEngine(ConfigEngine *data);
  AiEngine(const AiEngine &other);
  AiEngine & operator=(const AiEngine &other);
  ~AiEngine();

public:
  void		setID(int ID);
  void		setData(ConfigEngine *DATA);
  void		setUpdateTime(int T);
  void		setReactionTime(int R);
  int		getID() const;
  int		getUpdateTime() const;
  ConfigEngine* getData() const;
  int		getReactionTime() const;
  
  void		resetExplosionArea();
  void		resetUnitPosition();
  void		update();
  void		updateExplosionArea();
  void		updateUnitPosition();
  void		updateBots();

  bool		isBox(int X, int Y);
  bool		isDangerousCase(int X, int Y);
  bool		isTouch(int X, int Y, int Xcmp, int Ycmp);
  bool		isTouch(posXY X, posXY Y);
  bool		isFreeCase(int X, int Y);
  bool		isSafeCase(int X, int Y);
  bool		isDifferentCase(posXY first, posXY second);
  bool		thereIsEnemieClose(int X, int Y);
  bool		thereIsNoBoxBetween(posXY pos, posXY enemiePos);
  bool		thereIsNoDanger(int X, int Y);
  bool		thereIsBoxClose(int X, int Y);
  bool		thereIsBombAt(int X, int Y );
  bool		thereIsBonusClose(int X, int Y);
  bool		thereIsUnit(int X, int Y);
  bool		enemieInRange(int X, int Y, int R);
  bool		checkLongLine(posXY from, posXY to);
  bool		checkLargLine(posXY from, posXY to);
  posXY		getSafeCase(int X, int Y);
  posXY		getCase(int X, int Y);
  posXY		getLeaveCase(int X, int Y);


  void		calculateArea(posXY pos, int P);
  void		doUpCalc(posXY pos, int P);
  void		doRightCalc(posXY pos, int P);
  void		doDownCalc(posXY pos, int P);
  void		doLeftCalc(posXY pos, int P);

  void		affExplosionArea();
  void		affUnitPosition();
  void		affPos(posXY pos);
  void		affPos(int X, int Y);
  void		affState(State S);
  
  State		evalState(posXY pos, int attackRange);
  Action	makePlan(posXY pos, State S, bool B, int power);
  Action	survive(posXY pos);
  Action	attack(posXY pos, bool haveBomb, int power);
  Action	collectBonus(posXY pos);
  Action	explore(posXY pos, bool haveBomb);
  Action	getRandMove();
  Action	calcDirection(posXY oldP, posXY newP);

};

#endif
