#ifndef			XMLENGINE_HH_
# define		XMLENGINE_HH_

# include		<vector>
# include		<map>
# include		<string>
# include		"ConfigEngine.hh"

# define		GOOD_CAST(x)	reinterpret_cast<const char*>(x)

class			XmlEngine
{
public:
  struct		Save
  {
    Save(int, int);
    ~Save(void);

    int			stage;
    int			score;
  };

  struct		Map
  {
    struct		Coord
    {
      Coord(int, int);
      ~Coord(void);

      int		x;
      int		z;

      const Coord      	operator=(const Coord&);
    };

    Map(int, int);
    ~Map(void);

    int			width;
    int			height;
    std::vector<XmlEngine::Map::Coord> boxes;
  };

private:
  ConfigEngine		*config_;

  const std::string	ranking_;
  const std::string	saves_;
  const std::string	maps_;

public:
  XmlEngine(ConfigEngine *config);
  ~XmlEngine(void);

  void			saveScore(const std::string&, int);
  const std::multimap<int, const std::string> getScores(int) const;

  void			saveGame(void);
  const std::multimap<time_t, const XmlEngine::Save> getSaves(void) const;

  void			saveMap(const std::string&);
  const std::multimap<const std::string, const XmlEngine::Map> getMaps(void) const;
};

#endif			/* !XMLENGINE_HH_ */
