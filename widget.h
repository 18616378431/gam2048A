#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QtGui>
#include "gamewidget.h"

#define qApp (static_cast<QApplication *>(QCoreApplication::instance()))

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    //restart
    QPushButton *restartBtn;
    QPushButton *closeBtn;
    //score label
    QLabel *titleLabel;
    QLabel *tipsLabel;
    QLabel *scoreLabel;
    //high score label
    QLabel *highScoreLabel;
    //game component
    gamewidget *gameWidget;
    //window ratio
    qreal ratioW, ratioH;
    int highScore;
    QPoint dragPosition;
    bool bPressFlag;

protected:
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void onScoreInc(int);
    void onGameOver();
    void onWin();
};
#endif // WIDGET_H
