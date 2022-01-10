#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <QPainter>
#include <iostream>
#include <QTime>
#include <QMessageBox>

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

public slots:
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void paintEvent(QPaintEvent*) override;

private:
    Ui::Game *ui;

    QImage _giftImg;
    QImage _snake_body;

    enum _directions{ LEFT, RIGHT, UP, DOWN};
    _directions _dir;

    int _foodCount = 0;

    static const qint16 _square_width = 20;
    static const qint16 _square_heigth = 20;
    static const qint16 _field_width = 30;
    static const qint16 _field_heigth = 25;
    static const qint16 _delay = 150;

    qint16 _timerID;
    QPoint _gift;

    bool _inGame;
    QVector<QPoint> _dots;

    void initGame();
    void gameOver();
    void doDrawing();
    void localeGift();
    void move();
    void check_snake();
    void check_gift();
};
#endif // GAME_H
