#include "glsnake.hpp"
#include <QDebug>
#include <QFont>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QSize>
#include <QTimer>
#include <QTime>
#include <QtDebug>
#include <QtGlobal>
#include <iostream>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <sstream>
#include <string>
#include <cstdlib>
#include <QTime>
glSnake::eMenu operator++(glSnake::eMenu &aMenu) {
  aMenu = glSnake::eMenu(int(aMenu) + 1);
  if (aMenu == glSnake::eMenu::END) {
    aMenu = glSnake::eMenu::PLAY;
    return aMenu;
  }
  return aMenu;
}
glSnake::eMenu operator--(glSnake::eMenu &aMenu) {
  aMenu = glSnake::eMenu(int(aMenu) - 1);
  if (aMenu == glSnake::eMenu::START) {
    aMenu = glSnake::eMenu::EXIT;
    return aMenu;
  }
  return aMenu;
}
int menuStateToInt(const glSnake::eMenu &aMenu) {
  switch (aMenu) {
  case glSnake::eMenu::START:
    return (int)glSnake::eMenu::START;
  case glSnake::eMenu::END:
    return (int)glSnake::eMenu::END;
  case glSnake::eMenu::PLAYER_STAT:
    return (int)glSnake::eMenu::PLAYER_STAT;
  case glSnake::eMenu::PLAY:
    return (int)glSnake::eMenu::PLAY;
  case glSnake::eMenu::EXIT:
    return (int)glSnake::eMenu::EXIT;
  }
  return -1;
}
glSnake::eState menuStateToGameState(const glSnake::eMenu &aMenu) {
  switch (aMenu) {
  case glSnake::eMenu::START:
  case glSnake::eMenu::END:
    return glSnake::eState::MENU;
  case glSnake::eMenu::PLAY:
    return glSnake::eState::PLAY;
  case glSnake::eMenu::PLAYER_STAT:
    return glSnake::eState::PLAYER_STAT;
  case glSnake::eMenu::EXIT:
    return glSnake::eState::EXIT;
  }
  return glSnake::eState::MENU;
}
glSnake::glSnake(QWidget *parent):
  QGLWidget(parent)
{
    mvMenu.push_back({eMenu::PLAY, "Play"});
    mvMenu.push_back({eMenu::PLAYER_STAT, "Statistic"});
    mvMenu.push_back({eMenu::EXIT, "Exit"});
  x1=40;
  y1=30;
  x2=50;
  y2=30;
  x3=50;
  y3=40;
  x4=40;
  y4=40;
  snakea.resize(3);
  snakea[1].px=40;snakea[1].py=40;
  snakea[1].px1=50;snakea[1].py1=40;
  snakea[1].px2=50;snakea[1].py2=50;
  snakea[1].px3=40;snakea[1].py3=50;
  snakea[2].px=40;snakea[2].py=50;
  snakea[2].px1=50;snakea[2].py1=50;
  snakea[2].px2=50;snakea[2].py2=60;
  snakea[2].px3=40;snakea[2].py3=60;
  snake_dir=up;
  glSnake::a.setHMS(0,0,0);
  QTimer *tim = new QTimer(this);
  connect(tim, SIGNAL(timeout()), this, SLOT(updateGL()));
  tim -> start(33);
  timerId = startTimer(1000);
  glSnake::locateFruit();
  glSnake::score=0;
  glSnake::i=0;
}
glSnake::~glSnake() { close(); delete tim; exit(0);}
void glSnake::initializeGL() {
  glViewport(0, 0, 800, 600);
  glLoadIdentity();
  glOrtho(0, 800, 600, 0, 0, 1);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_DEPTH);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_SMOOTH);
}
void glSnake::resizeGL(int aw, int ah) {
  glViewport(0, 0, (GLint)aw, (GLint)ah);
  glLoadIdentity();
  glOrtho(0, aw, ah, 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
void glSnake::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  qglClearColor(Qt::black);
  _processing();
  _draw();
}
void glSnake::keyReleaseEvent(QKeyEvent *apKeyEvent) {
  switch (mState) {
  case eState::MENU: {
    key_release_menu(apKeyEvent->key());
    break;
  }
  case eState::PLAYER_STAT: {
    key_release_player_stat(apKeyEvent->key());
    break;
  }
  case eState::PLAY: {
    key_release_play(apKeyEvent->key());
    break;
  }
  case eState::EXIT: {
    close();
    break;
  }
  }
}
void glSnake::resizeEvent(QResizeEvent *apsize) {
  Q_UNUSED(apsize)
//  if (apsize->Resize) {
//    qInfo() << "Resize: "<<glSnake::width() << glSnake::height();
//    }
}
void glSnake::timerEvent(QTimerEvent *e)
{
  Q_UNUSED(e)
    i++;
  if(glSnake::i%15==0){locateFruit();}
  if(glSnake::i==1000)glSnake::i=0;
  updatetime();
}
void glSnake::_processing() {
  auto aw = glSnake::width();
  auto ah = glSnake::height();
  switch (mState) {
  case eState::MENU: {
    break;
  }
  case eState::PLAYER_STAT: {
    break;
  }
  case eState::PLAY: {
        if(y3 ==30 && y4==30){
            y1=ah-10;
            y2=ah-10;
            y3=ah;
            y4=ah;
            _draw_snake();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            break;
          }
        if(y1 ==ah && y2==ah){
            y1=30;
            y2=30;
            y3=40;
            y4=40;
            _draw_snake();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            break;
          }
        if(x2 == 0 && x3==0){
            x1=aw-10;
            x2=aw;
            x3=aw;
            x4=aw-10;
            _draw_snake();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            break;
          }
            if(x1 == aw && x4==aw){
                x1=0;
                x2=10;
                x3=10;
                x4=0;
                _draw_snake();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                break;
          }
        if(y3 ==Fy2 && x3 == Fx2 && y4==Fy3 && x4 == Fx3){
            snakea.push_back(C{0,0,0,0,0,0,0,0});
            locateFruit();
            glSnake::score++;
            _draw_score();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            break;
          }
        if(y2 ==Fy1 && x2 == Fx1 && y3==Fy2 && x3 == Fx2){
            snakea.push_back(C{0,0,0,0,0,0,0,0});
            locateFruit();
            glSnake::score++;
            _draw_score();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            break;
          }
        if(y1 ==Fy && x1 == Fx && y2==Fy1 && x2 == Fx1){
            snakea.push_back(C{0,0,0,0,0,0,0,0});
            locateFruit();
            glSnake::score++;
            _draw_score();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            break;
          }
        if(y1 ==Fy && x1 == Fx && y4==Fy3 && x4 == Fx3){
            snakea.push_back(C{0,0,0,0,0,0,0,0});
            locateFruit();
            glSnake::score++;
            _draw_score();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            break;
          }
    break;
  }
  case eState::EXIT: {
    close();
    break;
  }
  }
}
void glSnake::_draw() {
  switch (mState) {
  case eState::MENU: {
    _draw_menu();
    break;
  }
  case eState::PLAYER_STAT: {
    _draw_player_stat();
    break;
  }
  case eState::PLAY: {
    _draw_play();
    _draw_snake();
    _draw_fruits();
    _draw_score();
    _draw_timer();
    break;
  }
  case eState::EXIT: {
    break;
  }
  }
}
void glSnake::_draw_menu() {
  auto app_w = glSnake::width() / 2.f;
  auto app_h = glSnake::height() / 3.f;
  static auto font = QFont("Sans", 25);
  static auto font_selected = QFont("Sans", 30);
  font_selected.setBold(true);
  auto x = app_w - 100;
  auto y = app_h;
  auto dy = 55.f;
  int end = mvMenu.size();
  for (int i = 0; i < end; ++i) {
    if (i == menuStateToInt(mCurrentMenu)) {
      qglColor(Qt::lightGray);
      renderText(x, y, mvMenu[i].second.c_str(), font_selected);
    } else {
      qglColor(Qt::lightGray);
      renderText(x, y, mvMenu[i].second.c_str(), font);
    }
    y += dy;
  }
}
void glSnake::_draw_player_stat() {
  auto aw = glSnake::width();
  auto ah = glSnake::height();
  glViewport(0, 0, (GLint)aw, (GLint)ah);
  glLoadIdentity();
  glOrtho(0, aw, ah, 0, 0, 1);
  static auto font = QFont("Sans", 18);
  renderText(aw / 8.5, 20, "Statistic", font);
  glBegin(GL_POLYGON);
  glVertex2i(22, 22);
  glVertex2i(aw - 22, 22);
  glVertex2i(aw - 22, ah - 22);
  glVertex2i(22, ah - 22);
  glEnd();
}
void glSnake::_draw_play() {
    auto aw = glSnake::width()+10;
    auto ah = glSnake::height()-20;
    int N=(aw/10);
    int M=(ah/10);
    P p[N][M];
    for(int x=0;x!=N;x++)
      {
        for(int y=0;y!=M;y++)
          {
            p[x][y].x=x*aw/N;
            p[x][y].y=y*ah/M;
          }
      }
  glViewport(0, 0, (GLint)aw, (GLint)ah);
  glLoadIdentity();
  glOrtho(0, aw, 0, ah, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLineWidth(1);
  static auto font = QFont("Sans", 18);
  renderText(aw / 8.5, 20, "Score", font);
  static auto font1 = QFont("Sans", 18);
  renderText(aw / 8.5+185, 20, "Timer", font);
  _draw_timer();
  for(int x=0;x!=N;x++)
    {
      glBegin(GL_LINE_STRIP);
      for(int y=0;y!=M;y++)
          glVertex3i(p[x][y].x,p[x][y].y,0);
      glEnd();
    }
  for(int y=0;y!=M;y++)
    {
      glBegin(GL_LINE_STRIP);
      for(int x=0;x!=N;x++)
          glVertex3i(p[x][y].x,p[x][y].y,0);
      glEnd();
   }
}
void glSnake::_draw_snake() {
  auto aw = glSnake::width();
  auto ah = glSnake::height();
  glViewport(0, 0, (GLint)aw, (GLint)ah);
  glLoadIdentity();
  glOrtho(0, aw, ah, 0, 0, 1);
  snakea[0].px=x1;snakea[0].py=y1;
  snakea[0].px1=x2;snakea[0].py1=y2;
  snakea[0].px2=x3;snakea[0].py2=y3;
  snakea[0].px3=x4;snakea[0].py3=y4;
  glBegin(GL_QUADS);
  for(int i=0;i<snakea.size();++i){
      glVertex2i(snakea[i].px,snakea[i].py);
      glVertex2i(snakea[i].px1,snakea[i].py1);
      glVertex2i(snakea[i].px2,snakea[i].py2);
      glVertex2i(snakea[i].px3,snakea[i].py3);
    }
  glEnd();
}
void glSnake::_draw_fruits() {
  auto aw = glSnake::width();
  auto ah = glSnake::height();
  glViewport(0, 0, (GLint)aw, (GLint)ah);
  glLoadIdentity();
  glOrtho(0, aw, ah, 0, 0, 1);
  glBegin(GL_POLYGON);
  glVertex2i(Fx,Fy);//40 30
  glVertex2i(Fx1,Fy1);
  glVertex2i(Fx2,Fy2);
  glVertex2i(Fx3,Fy3);
  glEnd();
  //qInfo()<<((Fx+5)/10)*10<<((Fy+5)/10)*10;
}
void glSnake::_draw_score()
{
    auto aw = glSnake::width();
    QString s;
    static auto font = QFont("Sans", 18);
    renderText(aw / 8.5+85, 20, s.setNum(score), font);
}
void glSnake::_draw_timer()
{
    auto aw = glSnake::width();
    QString s1;
    static auto font1 = QFont("Sans", 18);
    renderText(aw / 8.5+300, 20, (glSnake::a.toString("hh:mm:ss")), font1);
}
void glSnake::key_release_menu(int aKey) {
  switch (aKey) {
  case Qt::Key_Up: {
    --mCurrentMenu;
    break;
  }
  case Qt::Key_Down: {
    ++mCurrentMenu;
    break;
  }
  case Qt::Key_Escape:
  case Qt::Key_Return: {
    mState = menuStateToGameState(mCurrentMenu);
    break;
  }
  }
}
void glSnake::key_release_player_stat(int aKey) {
  switch (aKey) {
  case Qt::Key_Up: {
    --mCurrentMenu;
    break;
  }
  case Qt::Key_Down: {
    ++mCurrentMenu;
    break;
  }
  case Qt::Key_Escape: {
    mState = eState::MENU;
    break;
  }
  }
}
void glSnake::key_release_play(int aKey) {
  const int step = 10;
    for(int i= snakea.size()-1;i>0;--i){
      snakea[i]=snakea[i-1];
      }
  switch (aKey) {
  case Qt::Key_Up:
  case Qt::Key_W: {
    // qInfo()<<"UP";
    snake_dir=up;
    glSnake::setY1(glSnake::Y1() - step);
    glSnake::setY2(glSnake::Y2() - step);
    glSnake::setY3(glSnake::Y3() - step);
    glSnake::setY4(glSnake::Y4() - step);
    updateGL();
    break;
  }
  case Qt::Key_Down:
  case Qt::Key_S:{
    // qInfo()<<"D";
    snake_dir=down;
    glSnake::setY1(glSnake::Y1() + step);
    glSnake::setY2(glSnake::Y2() + step);
    glSnake::setY3(glSnake::Y3() + step);
    glSnake::setY4(glSnake::Y4() + step);
    updateGL();
    break;
  }
  case Qt::Key_Left:
  case Qt::Key_A:{
    // qInfo()<<"L";
    snake_dir=left;
    glSnake::setX1(glSnake::X1() - step);
    glSnake::setX2(glSnake::X2() - step);
    glSnake::setX3(glSnake::X3() - step);
    glSnake::setX4(glSnake::X4() - step);
    updateGL();
    break;
  }
  case Qt::Key_Right:
  case Qt::Key_D:{
    // qInfo()<<"R";
    snake_dir=right;
    glSnake::setX1(glSnake::X1() + step);
    glSnake::setX2(glSnake::X2() + step);
    glSnake::setX3(glSnake::X3() + step);
    glSnake::setX4(glSnake::X4() + step);
    updateGL();
    break;
  }
  case Qt::Key_Escape: {
    mState = eState::MENU;
    break;
  }
  }
}
void glSnake::checkFruit()
{
  Fx=rand()%glSnake::width();
  Fy=rand()%glSnake::height();
}
void glSnake::locateFruit()
{
  qsrand(QDateTime::currentDateTime().toTime_t());
  int g,j;
  g=qrand()%((glSnake::width()+1)-0)+0;
  j=qrand()%((glSnake::height()-50+1)-0)+0;
  Fx=((g+5)/10)*10;
  Fy=((j+5)/10)*10;
  if (Fy <= 30)
  {
    Fy=(30 - Fy)+30;
  }
  Fx1=Fx+10;
  Fy1=Fy;
  Fx2=Fx1;
  Fy2=Fy+10;
  Fx3=Fx;
  Fy3=Fy2;
}
void glSnake::setX1(int x) { x1 = x; }
void glSnake::setY1(int y) { y1 = y; }
void glSnake::setX2(int x) { x2 = x; }
void glSnake::setY2(int y) { y2 = y; }
void glSnake::setX3(int x) { x3 = x; }
void glSnake::setY3(int y) { y3 = y; }
void glSnake::setX4(int x) { x4 = x; }
void glSnake::setY4(int y) { y4 = y; }
int glSnake::X1() { return x1; }
int glSnake::Y1() { return y1; }
int glSnake::X2() { return x2; }
int glSnake::Y2() { return y2; }
int glSnake::X3() { return x3; }
int glSnake::Y3() { return y3; }
int glSnake::X4() { return x4; }
int glSnake::Y4() { return y4; }
void glSnake::updatetime()
{
    glSnake::a=glSnake::a.addSecs(1);
}
