#include <string>
#include <sstream>

template<typename T>
std::string		toString(T number)
{
  std::stringstream	stream;

  stream << number;
  return (stream.str());
}

template<typename T>
T			toNumber(std::string str)
{
  T			value;
  std::stringstream	stream;

  stream << str;
  stream >> value;
  return (value);
}
