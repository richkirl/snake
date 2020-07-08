#ifndef GLSNAKE_HPP
#define GLSNAKE_HPP
#include <QEvent>
#include <QGLWidget>
#include <QResizeEvent>
#include <map>
#include <string>
#include <vector>
#include <QVector>
#include <QPoint>
#include <QTime>
class glSnake : public QGLWidget {
  Q_OBJECT
public:
    glSnake();
    ~glSnake();
    struct P
    {
      int x;
      int y;
    };
    struct C{
    public:
      int px=0;int px1=0;
      int py=0;int py1=0;
      int px2=0;int px3=0;
      int py2=0;int py3=0;
    };
  enum class eState { MENU, PLAYER_STAT, PLAY, EXIT };
  enum class eMenu { START = -1, PLAY, PLAYER_STAT, EXIT, END };
  enum Dir {up,down,left,right};
  Dir snake_dir;
  const int N=80;
  const int M=60;
public:

  QTimer *tim;
  QVector<C> snakea;
  //QTimer *tmr1;
  int x1=40;int y1=30;
  int x2=50;int y2=30;
  int x3=50;int y3=40;
  int x4=40;int y4=40;
  void setX1(int);
  void setY1(int);
  void setX2(int);
  void setY2(int);
  void setX3(int);
  void setY3(int);
  void setX4(int);
  void setY4(int);
  int X1();
  int Y1();
  int X2();
  int Y2();
  int X3();
  int Y3();
  int X4();
  int Y4();
  int Fx;
  int Fy;
  int Fx1;
  int Fy1;
  int Fx2;
  int Fy2;
  int Fx3;
  int Fy3;
  //int id_timer;
  int score=0;
  int i=0;
  QTime a;
private slots:
    void updatetime();
    void locateFruit();
private:
  void initializeGL() override;
  void resizeGL(int, int) override;
  void paintGL() override;
  void keyReleaseEvent(QKeyEvent *) override;
  virtual void resizeEvent(QResizeEvent *) override;
  virtual void timerEvent(QTimerEvent *) override;
private:
  void _processing();
  void _draw();
  void _draw_menu();
  void _draw_player_stat();
  void _draw_play();
  void _draw_snake();
  void _draw_fruits();
  void _draw_score();
  void _draw_timer();
  void actioncollection();
  void key_release_menu(int);
  void key_release_player_stat(int);
  void key_release_play(int);
  void checkFruit();
private:
  std::vector<std::pair<eMenu, std::string>> mvMenu;
  eState mState{eState::MENU};
  eMenu mCurrentMenu{eMenu::PLAY};
  int mSelectLevelIndex;
  int timerId;
};
#endif // GLSNAKE_HPP
