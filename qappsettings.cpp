#include "qappsettings.hpp"



qappSettings &qappSettings::instance()
{
  static qappSettings res;
  return res;
}

void qappSettings::load()
{

}

void qappSettings::save()
{

}

unsigned qappSettings::screenWidth() const
{
  static unsigned res{};
  return res;
}

unsigned qappSettings::screenHeight() const
{
  static unsigned res{};
  return res;
}

qappSettings::qappSettings()
{
  load();
}

qappSettings::~qappSettings()
{
  save();
}
