#include	"Case.hh"

Case::Case(void)
  : xMin_(0), xMax_(0), yMin_(0), yMax_(0), type_(FLOOR)
{
}

Case::Case(double xMin, double xMax, double yMin, double yMax, CaseType type)
  : xMin_(xMin), xMax_(xMax), yMin_(yMin), yMax_(yMax), type_(type)
{
}

void		Case::setXmin(double x)
{
  this->xMin_ = x;
}

void		Case::setXmax(double x)
{
  this->xMax_ = x;
}

void		Case::setYmin(double y)
{
  this->yMin_ = y;
}

void		Case::setYmax(double y)
{
  this->yMax_ = y;
}

void		Case::setType(CaseType type)
{
  this->type_ = type;
}

double		Case::getXmin() const
{
  return (this->xMin_);
}

double		Case::getXmax() const
{
  return (this->xMax_);
}

double		Case::getYmin() const
{
  return (this->yMin_);
}

double		Case::getYmax() const
{
  return (this->yMax_);
}

CaseType	Case::getType() const
{
  return (this->type_);
}

bool		Case::isInCase(double x, double y) const
{
  if (x < this->xMax_ && x > this->xMin_)
    if (y < this->yMax_ && y > this->yMin_)
      return (true);
  return (false);
}

bool		operator!=(const Case &first, const Case &second)
{
  if (first.getXmin() != second.getXmin()
      || first.getXmax() != second.getXmax()
      || first.getYmax() != second.getYmax()
      || first.getYmin() != second.getYmin())
    return (true);
  return (false);
}
