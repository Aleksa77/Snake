#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    this->resize(_square_width * _field_width, _square_heigth * _field_heigth);
    this->setWindowTitle("***Snake game***");

    _giftImg.load(":/image/gift_.png");
    _snake_body.load(":/image/body_.png");

    srand(QTime::currentTime().msec());
    initGame();
}

Game::~Game()
{
    delete ui;
}

void Game::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    if (_inGame)
    {
        check_gift();
        move();
        check_snake();
    }
    this->repaint();
}

void Game::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    if (key == Qt::Key_Left && _dir != RIGHT)
        _dir = LEFT;
    if (key == Qt::Key_Right && _dir != LEFT)
        _dir = RIGHT;
    if (key == Qt::Key_Up && _dir != DOWN)
        _dir = UP;
    if (key == Qt::Key_Down && _dir != UP)
        _dir = DOWN;
}

void Game::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    doDrawing();
}

void Game::initGame()
{
    _inGame = true;
    _dir = RIGHT;
    _foodCount = 0;

    _dots.resize(3);
    for (int i = 0; i < _dots.size(); ++i) {
        _dots[i].rx() = _dots.size() - i - 1;
        _dots[i].ry() = 0;
    }

    localeGift();
    _timerID = startTimer(_delay);
}

void Game::gameOver()
{
    QMessageBox msgb;
    msgb.setText("***Game over***");
    msgb.exec();

    initGame();
}

void Game::localeGift()
{
    _gift.rx() = rand() % _square_width;
    _gift.ry() = rand() % _square_heigth;
}

void Game::move()
{
    for (int i = _dots.size() - 1; i > 0; --i) {
        _dots[i] = _dots[i-1];
    }

    switch (_dir){
    case LEFT:
        _dots[0].rx() -= 1;
        break;
    case RIGHT:
        _dots[0].rx() += 1;
        break;
    case UP:
        _dots[0].ry() -= 1;
        break;
    case DOWN:
        _dots[0].ry() += 1;
        break;
    }
}

void Game::check_snake()
{
    if(_dots.size() > 4)
        for (int i = 1; i < _dots.size(); ++i)
            if(_dots[0] == _dots[i])
                _inGame = false;
    if ((_dots[0].x() >= _field_width) || (_dots[0].x() < 0))
        _inGame = false;
    if ((_dots[0].y() >= _field_heigth) || (_dots[0].y() < 0))
        _inGame = false;
    if(!_inGame)
        killTimer(_timerID);
}

void Game::check_gift()
{
    if(_gift == _dots[0])
    {
        _dots.push_back(QPoint(0,0));
        localeGift();
        _foodCount++;
    }
}

void Game::doDrawing()
{
    QPainter qp(this);

    if(_inGame)
    {
        qp.drawImage(_gift.x() * _square_width, _gift.y() * _square_heigth, _giftImg);

        qp.setPen(Qt::green);
        qp.drawText(480, 20, "Number of gifts:  " + QString::number(_foodCount));

        for (int i = 0; i < _dots.size(); ++i)
                qp.drawImage(_dots[i].x() * _square_width, _dots[i].y() * _square_heigth, _snake_body);
    }
    else
        gameOver();
}
