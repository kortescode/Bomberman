#include <iostream>
#include "Skybox.hh"

Skybox::Skybox(ConfigEngine *a)
  : AObject(a)
{
}

void		Skybox::initialize(void)
{
  this->texture_[1] = gdl::Image::load("img/sud.bmp");
  this->texture_[2] = gdl::Image::load("img/est.bmp");
  this->texture_[3] = gdl::Image::load("img/haut.bmp");
  this->texture_[4] = gdl::Image::load("img/bas.bmp");
  this->texture_[5] = gdl::Image::load("img/ouest.bmp");
  this->texture_[6] = gdl::Image::load("img/nord.bmp");
}

void		Skybox::update(void)
{
}

void		Skybox::draw(void)
{
  this->texture_[1].bind();

  glBegin(GL_QUADS);
  glColor3f(255.0f, 255.0f, 255.0f);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-size_, size_, size_);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-size_, -size_, size_);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(size_, -size_, size_);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(size_, size_, size_);
  glEnd();

  this->texture_[2].bind();
  glBegin(GL_QUADS);
  glColor3f(255.0f, 255.0f, 255.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-size_, size_, -size_);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-size_, -size_, -size_);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-size_, -size_, size_);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-size_, size_, size_);
  glEnd();

  this->texture_[6].bind();
  glBegin(GL_QUADS);
  glColor3f(255.0f, 255.0f, 255.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(size_, size_, -size_);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(size_, -size_, -size_);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-size_, -size_, -size_);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-size_, size_, -size_);
  glEnd();

  this->texture_[5].bind();
  glBegin(GL_QUADS);
  glColor3f(255.0f, 255.0f, 255.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(size_, size_, size_);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(size_, -size_, size_);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(size_, -size_, -size_);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(size_, size_, -size_);
  glEnd();

  this->texture_[3].bind();
  glBegin(GL_QUADS);
  glColor3f(255.0f, 255.0f, 255.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-size_, size_, -size_);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-size_, size_, size_);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(size_, size_, size_);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(size_, size_, -size_);
  glEnd();

  this->texture_[4].bind();
  glBegin(GL_QUADS);
  glColor3f(255.0f, 255.0f, 255.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-size_, -size_, -size_);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-size_, -size_, size_);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(size_, -size_, size_);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(size_, -size_, -size_);
  glEnd();
}

void		Skybox::setSize(int size)
{
  this->size_ = size * 400 + 400 + 10000;
}
