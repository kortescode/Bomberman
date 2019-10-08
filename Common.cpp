#include		<string>
#include		<sstream>
#include		<iostream>
#include		"Common.hh"
#include		"Common.tpl"

template <typename T>
const std::string	Common::stringOfNbr(T i)
{
  std::ostringstream	oss;

  oss << i;
  return (oss.str());
}

template <typename T>
T			Common::nbrOfString(const std::string& str)
{
  T			nbr;
  std::istringstream	iss(str);

  iss >> nbr;
  return (nbr);
}
