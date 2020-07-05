#ifndef QAPPSETTINGS_HPP
#define QAPPSETTINGS_HPP


class qappSettings
{
public:
  qappSettings(const qappSettings &) = delete;
  qappSettings & operator=(const qappSettings&) = delete;

  static qappSettings &instance();



  void load();
  void save();

  unsigned screenWidth() const;
  unsigned screenHeight() const;

private:
  qappSettings();
  ~qappSettings();

private:
  unsigned mScreenWidth{0};
  unsigned mScreenHeight{0};
};

#endif // QAPPSETTINGS_HPP
