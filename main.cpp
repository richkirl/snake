#include <QApplication>
#include <QDebug>
#include <QSize>
#include <QTimer>
#include <QTime>
#include <QtDebug>
#include <glsnake.hpp>
#include <QStyle>
#include <QDesktopWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  glSnake w;
  w.show();
  w.resize(800,600);
  //glutPositionWindow(0,0);
  w.setFixedWidth(800);
  w.setFixedHeight(600);
  w.setGeometry(
      QStyle::alignedRect(
          Qt::LeftToRight,
          Qt::AlignCenter,
          w.size(),
          a.desktop()->availableGeometry()
      )
  );
  return a.exec();
}
