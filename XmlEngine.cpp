#include	<string.h>
#include	<map>
#include	<time.h>
#include	<libxml/tree.h>
#include       	<sys/stat.h>
#include	<iostream>
#include	<fstream>
#include	"ConfigEngine.hh"
#include	"XmlEngine.hh"
#include	"Common.hh"
#include	"AObject.hh"

XmlEngine::Save::Save(int sta, int sco)
  : stage(sta), score(sco)
{
}

XmlEngine::Save::~Save(void)
{
}

XmlEngine::Map::Map(int w, int h)
  : width(w), height(h)
{
}

XmlEngine::Map::~Map(void)
{
}

XmlEngine::Map::Coord::Coord(int a, int b)
  : x(a), z(b)
{
}

XmlEngine::Map::Coord::~Coord(void)
{
}

const XmlEngine::Map::Coord XmlEngine::Map::Coord::operator=(const XmlEngine::Map::Coord& other)
{
  return (XmlEngine::Map::Coord(other.x, other.z));
}

XmlEngine::XmlEngine(ConfigEngine *config)
  : config_(config), ranking_(".ranking.xml"),
    saves_(".saves.xml"), maps_(".maps.xml")
{
  char		*file = const_cast<char*>(this->ranking_.c_str());
  std::string	root = "<ranking></ranking>";
  std::ifstream	ifile;
  std::ofstream	ofile;

  for (int i = 0; i < 3; i++)
    {
      if (i == 1)
	{
	  file = const_cast<char*>(this->saves_.c_str());
	  root = "<saves></saves>";
	}
      else if (i == 2)
	{
	  file = const_cast<char*>(this->maps_.c_str());
	  root = "<maps></maps>";
	}
      ifile.open(file);
      if (ifile.is_open())
	ifile.close();
      else
	{
	  ofile.open(file, std::ofstream::app);
	  ofile << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << std::endl << root;
	  ofile.close();
	}
      (void)chmod(file, S_IRUSR | S_IRGRP | S_IROTH);
    }
}

XmlEngine::~XmlEngine(void)
{
}

void	        XmlEngine::saveScore(const std::string& name, int score)
{
  xmlDocPtr	doc;
  xmlNodePtr	root, node;

  (void)chmod(this->ranking_.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  xmlKeepBlanksDefault(0);
  if ((doc = xmlParseFile(this->ranking_.c_str())) && (root = xmlDocGetRootElement(doc)))
    {
      node = xmlNewNode(NULL, BAD_CAST "score");
      xmlSetProp(node, BAD_CAST "game", BAD_CAST (Common::stringOfNbr<int>(this->config_->ModeGame)).c_str());
      xmlNewTextChild(node, NULL, BAD_CAST "name", BAD_CAST name.c_str());
      xmlNewTextChild(node, NULL, BAD_CAST "nbr", BAD_CAST (Common::stringOfNbr<int>(score)).c_str());
      xmlAddChild(root, node);
      xmlSaveFile(this->ranking_.c_str(), doc);
      xmlFreeDoc(doc);
    }
  (void)chmod(this->ranking_.c_str(), S_IRUSR | S_IRGRP | S_IROTH);
}

const std::multimap<int, const std::string> XmlEngine::getScores(int game) const
{
  xmlDocPtr	doc;
  xmlNodePtr	root, node;
  std::multimap<int, const std::string> scores;

  xmlKeepBlanksDefault(0);
  if ((doc = xmlParseFile(this->ranking_.c_str())) && (root = xmlDocGetRootElement(doc)))
    {
      if ((node = root->children))
	{
	  while (node)
	    {
	      if (node->type == XML_ELEMENT_NODE && strcmp(GOOD_CAST(xmlGetProp(node, BAD_CAST "game")), (Common::stringOfNbr<int>(game)).c_str()) == 0)
		scores.insert(std::pair<int, const std::string>(Common::nbrOfString<int>(GOOD_CAST(xmlNodeGetContent(node->children->next))), GOOD_CAST(xmlNodeGetContent(node->children))));
	      node = node->next;
	    }
	}
      xmlFreeDoc(doc);
    }
  return (scores);
}

void		XmlEngine::saveGame(void)
{
  time_t	t;
  xmlDocPtr	doc;
  xmlNodePtr	root, node;

  (void)chmod(this->saves_.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  xmlKeepBlanksDefault(0);
  if ((doc = xmlParseFile(this->saves_.c_str())) && (root = xmlDocGetRootElement(doc)))
    {
      t = time(NULL);
      node = xmlNewNode(NULL, BAD_CAST "save");
      xmlSetProp(node, BAD_CAST "timestamp", BAD_CAST (Common::stringOfNbr<int>(t)).c_str());
      xmlNewTextChild(node, NULL, BAD_CAST "stage", BAD_CAST (Common::stringOfNbr<int>(this->config_->getStage())).c_str());
      xmlNewTextChild(node, NULL, BAD_CAST "score", BAD_CAST (Common::stringOfNbr<int>(this->config_->getTotalScore())).c_str());
      xmlAddChild(root, node);
      xmlSaveFile(this->saves_.c_str(), doc);
      xmlFreeDoc(doc);
    }
  (void)chmod(this->saves_.c_str(), S_IRUSR | S_IRGRP | S_IROTH);
}

const std::multimap<time_t, const XmlEngine::Save> XmlEngine::getSaves(void) const
{
  xmlDocPtr	doc;
  xmlNodePtr	root, node;
  std::multimap<time_t, const XmlEngine::Save> saves;

  xmlKeepBlanksDefault(0);
  if ((doc = xmlParseFile(this->saves_.c_str())) && (root = xmlDocGetRootElement(doc)))
    {
      if ((node = root->children))
	{
	  while (node)
	    {
	      if (node->type == XML_ELEMENT_NODE)
		saves.insert(std::pair<time_t, const XmlEngine::Save>(Common::nbrOfString<int>(GOOD_CAST(xmlGetProp(node, BAD_CAST "timestamp"))), XmlEngine::Save(Common::nbrOfString<int>(GOOD_CAST(xmlNodeGetContent(node->children))), Common::nbrOfString<int>(GOOD_CAST(xmlNodeGetContent(node->children->next))))));
	      node = node->next;
	    }
	}
      xmlFreeDoc(doc);
    }
  return (saves);
}

void		XmlEngine::saveMap(const std::string& name)
{
  //time_t	t;
  xmlDocPtr	doc;
  xmlNodePtr	root, node, coord, boxes, box;

  (void)chmod(this->maps_.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  xmlKeepBlanksDefault(0);
  if ((doc = xmlParseFile(this->maps_.c_str())) && (root = xmlDocGetRootElement(doc)))
    {
      //t = time(NULL);
      node = xmlNewNode(NULL, BAD_CAST "map");
      xmlSetProp(node, BAD_CAST "name", BAD_CAST name.c_str());
      coord = xmlNewNode(NULL, BAD_CAST "coord");
      xmlNewTextChild(coord, NULL, BAD_CAST "width", BAD_CAST (Common::stringOfNbr<int>(this->config_->getMapWidth())).c_str());
      xmlNewTextChild(coord, NULL, BAD_CAST "height", BAD_CAST (Common::stringOfNbr<int>(this->config_->getMapHeight())).c_str());
      boxes = xmlNewNode(NULL, BAD_CAST "boxes");
      for (std::list<AObject*>::iterator it = this->config_->listBoxes.begin(); it != this->config_->listBoxes.end(); ++it)
	{
	  box = xmlNewNode(NULL, BAD_CAST "box");
	  xmlNewTextChild(box, NULL, BAD_CAST "x", BAD_CAST (Common::stringOfNbr<int>((*it)->getX() / 400)).c_str());
	  xmlNewTextChild(box, NULL, BAD_CAST "z", BAD_CAST (Common::stringOfNbr<int>((*it)->getZ() / 400)).c_str());
	  xmlAddChild(boxes, box);
	}
      xmlAddChild(node, coord);
      xmlAddChild(node, boxes);
      xmlAddChild(root, node);
      xmlSaveFile(this->maps_.c_str(), doc);
      xmlFreeDoc(doc);
    }
  (void)chmod(this->maps_.c_str(), S_IRUSR | S_IRGRP | S_IROTH);
}

const std::multimap<const std::string, const XmlEngine::Map> XmlEngine::getMaps(void) const
{
  xmlDocPtr	doc;
  xmlNodePtr	root, node;
  std::multimap<const std::string, const XmlEngine::Map> maps;

  xmlKeepBlanksDefault(0);
  if ((doc = xmlParseFile(this->maps_.c_str())) && (root = xmlDocGetRootElement(doc)))
    {
      if ((node = root->children))
	{
	  while (node)
	    {
	      if (node->type == XML_ELEMENT_NODE)
		{
		  XmlEngine::Map map(Common::nbrOfString<int>(GOOD_CAST(xmlNodeGetContent(node->children->children))), Common::nbrOfString<int>(GOOD_CAST(xmlNodeGetContent(node->children->children->next))));
		  for (xmlNodePtr it = node->children->next->children; it; it = it->next)
		    map.boxes.push_back(XmlEngine::Map::Coord(Common::nbrOfString<int>(GOOD_CAST(xmlNodeGetContent(it->children))), Common::nbrOfString<int>(GOOD_CAST(xmlNodeGetContent(it->children->next)))));
		  maps.insert(std::pair<const std::string, const XmlEngine::Map>(GOOD_CAST(xmlGetProp(node, BAD_CAST "name")) , map));
		}
	      node = node->next;
	    }
	}
      xmlFreeDoc(doc);
    }
  return (maps);
}
