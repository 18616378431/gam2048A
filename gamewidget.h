#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QEventLoop>
#include <QTimer>
#include <QPainter>
#include <QList>

//common struct
enum AnimationSource
{
    MOVE = 0,//rectangle move animation
    APPEARANCE = 1 //rectangle appear animation
};

//touch event
enum GestureDirect
{
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
};

//animation struct
struct Animation
{
    AnimationSource type;
    GestureDirect direct;
    QPointF startPos;
    QPointF endPos;
    int digit;
    int digit2;
};



class gamewidget : public QWidget
{
    Q_OBJECT
public:
    explicit gamewidget(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent * event);

private:
    int board[4][4];//board
    int digitCount;
    int score;
    QPoint startPos;
    QList<Animation> animationList;
    qreal w, h;
    QImage *cacheImg;
    bool isAnimating;

    bool checkGameOver();
    bool checkWin();
    int getBitCount(int);
    bool playAnimation(Animation&, QPainter&);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);

signals:
    void GestureMove(GestureDirect);
    void ScoreInc(int);
    void GameOver();
    void win();

public slots:
    void onGestureMove(GestureDirect);
    void restart();
};

#endif // GAMEWIDGET_H
