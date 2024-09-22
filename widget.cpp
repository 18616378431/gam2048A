#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , bPressFlag(false)
{
    ui->setupUi(this);

    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor("#FAF8F0"));
    setPalette(pal);

    titleLabel = new QLabel("2048", this);
    titleLabel->setStyleSheet("color:#746D65");
    titleLabel->setFont(QFont("arial", 45, QFont::Black));

    tipsLabel = new QLabel("达成2048胜利", this);
    tipsLabel->setStyleSheet("color:#B3AFA7");
    tipsLabel->setFont(QFont("arial", 10, QFont::Normal));

    highScore = 0;

    QFile file("score.f");

    if (file.open(QIODevice::ReadOnly))
    {
        file.read((char *)&highScore, sizeof(highScore));
        file.close();
    }

    //construct a game widget component
    gameWidget = new gamewidget(this);
    gameWidget->setFocus();
    connect(gameWidget, SIGNAL(ScoreInc(int)), this, SLOT(onScoreInc(int)));
    connect(gameWidget, SIGNAL(GameOver()), this, SLOT(onGameOver()));
    connect(gameWidget, SIGNAL(win()), this, SLOT(onWin()));

    QFont font;
    font.setFamily("Arial");
    font.setBold(true);
    font.setPixelSize(15);

    restartBtn = new QPushButton("新游戏", this);
    restartBtn->setFont(font);
    restartBtn->setStyleSheet("QPushButton{color:white;background:#907963;border-style:flat;}");
    restartBtn->setFocusPolicy(Qt::NoFocus);
    connect(restartBtn, SIGNAL(clicked()), gameWidget, SLOT(restart()));

    highScoreLabel = new QLabel(QString("最高\n%1").arg(highScore), this);
    highScoreLabel->setFont(font);
    highScoreLabel->setAlignment(Qt::AlignCenter);
    highScoreLabel->setStyleSheet("QLabel{color:#FFFFEE;background:#BEAD9D;}");

    scoreLabel = new QLabel("分数\n0", this);
    scoreLabel->setFont(font);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("QLabel{color:#FFFFEE;background:#BEAD9D;}");

    closeBtn = new QPushButton("x", this);
    closeBtn->setFocusPolicy(Qt::NoFocus);
    closeBtn->setFont(QFont("Arial", 11, QFont::Normal));

    closeBtn->setStyleSheet("QPushButton{border-style:flat;color:#BDAD9F;}"
                            "QPushButton:hover{border-style:flat;color:#FF0000;}}");
    closeBtn->setCursor(Qt::PointingHandCursor);
    closeBtn->setGeometry(400 - 18, 3, 15, 15);
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));

    resize(400, 510);
    move((qApp->screens()[0]->availableGeometry().width() - width()) / 2, (qApp->screens()[0]->availableGeometry().height() - height()) / 2);
}

Widget::~Widget()
{
    delete restartBtn;
    delete scoreLabel;
    delete highScoreLabel;
    delete gameWidget;
    delete ui;
}

void Widget::onScoreInc(int score)
{
    scoreLabel->setText(QString("分数:\n %1").arg(score));

    if (score > highScore)
    {
        highScore = score;
        highScoreLabel->setText(QString("最高分:\n %1").arg(highScore));

        //write file
        QFile file("score.f");
        file.open(QIODevice::WriteOnly);
        file.write((char *)&highScore, sizeof(highScore));
        file.close();
    }
}

void Widget::onGameOver()
{
    QMessageBox::information(this, "游戏结束", "失败!");
}

void Widget::onWin()
{
    QMessageBox::information(this, "恭喜", "胜利!");
}

void Widget::resizeEvent(QResizeEvent *)
{
    ratioW = width() / 400.0f;
    ratioH = height() / 510.0f;

    titleLabel->setGeometry(20 * ratioW, 40 * ratioH, 130 * ratioW, 50 * ratioH);
    tipsLabel->setGeometry(20 * ratioW, 100 * ratioH, 300 * ratioW, 20 * ratioH);
    gameWidget->setGeometry(18 * ratioW, 140 * ratioH, 365 * ratioW, 365 * ratioH);
    restartBtn->setGeometry(280 * ratioW, 90 * ratioH, 100 * ratioW, 30 * ratioH);
    highScoreLabel->setGeometry(300 * ratioW, 40 * ratioH, 80 * ratioW, 40 * ratioH);
    scoreLabel->setGeometry(210 * ratioW, 40 * ratioH, 80 * ratioW, 40 * ratioH);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    gameWidget->setFocus();
    QWidget::keyPressEvent(event);
}

//mouse
void Widget::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    dragPosition = event->pos();
    QWidget::mousePressEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag)
    {
        QPoint realPos(QCursor::pos() - dragPosition);
        move(realPos);
    }
    QWidget::mouseMoveEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}
