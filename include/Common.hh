#ifndef				COMMON_HH_
# define			COMMON_HH_

# include			<string>

class				Common
{
public:
  Common(void);
  ~Common(void);

  template <typename T>
  static const std::string	stringOfNbr(T);

  template < typename T>
  static T			nbrOfString(const std::string&);
};

#endif				/* !COMMON_HH_ */
