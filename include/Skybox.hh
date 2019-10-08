#ifndef SKYBOX_H_
# define SKYBOX_H_

# include "AObject.hh"
# include "Image.hpp"

class		Skybox : public AObject
{
public:
  Skybox(ConfigEngine *a);
  void		initialize(void);
  void		update(void);
  void		draw(void);

  void		setSize(int);

private:
  gdl::Image	texture_[7];
  double	size_;
};


#endif /* !SKYBOX_H_ */
