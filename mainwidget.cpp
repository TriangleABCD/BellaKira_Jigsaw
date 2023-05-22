#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "block.h"
#include <QDebug>
#include <QTime>
#include <QMediaPlaylist>
#include <string>
#include <queue>
#include <set>
#include <vector>

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainWidget)
{
    ui->setupUi(this);

    // 设置标题
    this->setWindowTitle("贝拉kira超级擅长的华容道");
    // 设置窗口固定大小
    this->setFixedSize(503, 703);
    // 设定程序图标
    this->setWindowIcon(QIcon(":/images/icon.png"));
    //透明度及颜色设置
    this->setWindowOpacity(0.9);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(219, 125, 116));
    this->setPalette(pal);

    //游戏背景音乐的设置
    mediaPlayer_gameWindowBackground = new QMediaPlayer(this);
    mediaPlaylist_gameWindowBackground = new QMediaPlaylist(this);
    mediaPlaylist_gameWindowBackground->addMedia(QUrl("qrc:/sound/Shiny_Dancer.mp3"));
    mediaPlaylist_gameWindowBackground->setCurrentIndex(1);
    mediaPlaylist_gameWindowBackground->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    mediaPlayer_gameWindowBackground->setPlaylist(mediaPlaylist_gameWindowBackground);
    mediaPlayer_gameWindowBackground->setVolume(80);
    mediaPlayer_gameWindowBackground->play();

    // 块初始化
    int k = 0;
    this->pnum = 0;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            this->blks[i][j] = new Block(this);
            this->blks[i][j]->setValue(k++);
            this->blks[i][j]->setP(this->pnum);
        }
    }

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            this->blks[i][j]->move(50+100*j+j, 50+100*i+i);
        }
    }

    this->next_x = this->next_y = 3;

    // 切换图片按钮
    QPushButton* shiftImage = new QPushButton(this);
    shiftImage->setFixedSize(403, 90);
    shiftImage->move(50, 500);
    shiftImage->setText("切换图片");

    // 开始游戏按钮
    QPushButton* start = new QPushButton(this);
    start->setFixedSize(403, 90);
    start->move(50, 600);
    start->setText("开始游戏");

    // 游戏完成提示框
    mess = new QMessageBox(this);
    mess->setWindowTitle("拼图完成");
    mess->setText("你竟然完成了? 你根本不是贝极星! 你到底是谁?");


    // 实现切换图片 连接
    QObject::connect(shiftImage, &QPushButton::clicked, this, [&](){
        this->pnum = (this->pnum+1) % picNum;
        for(int i = 0; i < 4; ++i) {
            for(int j = 0; j < 4; ++j) {
                this->blks[i][j]->setP(this->pnum);
            }
        }
    });

    // 实现点击开始游戏按钮之后打乱
    QObject::connect(start, &QPushButton::clicked, this, [&](){
        this->shuffle(1000);
    });

    // 16个块的点击事件
    QObject::connect(this->blks[0][0], &QPushButton::clicked, this, [&](){
        this->swapMove(0, 0);
        if(this->isCompleted()) {
            mess->exec();
        }
    });
    QObject::connect(this->blks[0][1], &QPushButton::clicked, this, [&](){
        this->swapMove(0, 1);
        if(this->isCompleted()) {
            mess->exec();
        }
    });
    QObject::connect(this->blks[0][2], &QPushButton::clicked, this, [&](){
        this->swapMove(0, 2);
        if(this->isCompleted()) {
            mess->exec();
        }
    });
    QObject::connect(this->blks[0][3], &QPushButton::clicked, this, [&](){
        this->swapMove(0, 3);
        if(this->isCompleted()) {
            mess->exec();
        }
    });

    QObject::connect(this->blks[1][0], &QPushButton::clicked, this, [&](){
        this->swapMove(1, 0);
        if(this->isCompleted()) {
            mess->exec();
        }
    });
    QObject::connect(this->blks[1][1], &QPushButton::clicked, this, [&](){
        this->swapMove(1, 1);
        if(this->isCompleted()) {
            mess->exec();
        }
    });
    QObject::connect(this->blks[1][2], &QPushButton::clicked, this, [&](){
        this->swapMove(1, 2);
        if(this->isCompleted()) {
            mess->exec();
        }
    });
    QObject::connect(this->blks[1][3], &QPushButton::clicked, this, [&](){
        this->swapMove(1, 3);
        if(this->isCompleted()) {
            mess->exec();
        }
    });

    QObject::connect(this->blks[2][0], &QPushButton::clicked, this, [&](){
        this->swapMove(2, 0);
        if(this->isCompleted()) {
            mess->exec();
        }
    });
    QObject::connect(this->blks[2][1], &QPushButton::clicked, this, [&](){
        this->swapMove(2, 1);
        if(this->isCompleted()) {
            mess->exec();
        }
    });
    QObject::connect(this->blks[2][2], &QPushButton::clicked, this, [&](){
        this->swapMove(2, 2);
        if(this->isCompleted()) {
            mess->exec();
        }
    });
    QObject::connect(this->blks[2][3], &QPushButton::clicked, this, [&](){
        this->swapMove(2, 3);
        if(this->isCompleted()) {
            mess->exec();
        }
    });

    QObject::connect(this->blks[3][0], &QPushButton::clicked, this, [&](){
        this->swapMove(3, 0);
        if(this->isCompleted()) {
            mess->exec();
        }
    });
    QObject::connect(this->blks[3][1], &QPushButton::clicked, this, [&](){
        this->swapMove(3, 1);
        if(this->isCompleted()) {
            mess->exec();
        }
    });
    QObject::connect(this->blks[3][2], &QPushButton::clicked, this, [&](){
        this->swapMove(3, 2);
        if(this->isCompleted()) {
            mess->exec();
        }
    });
    QObject::connect(this->blks[3][3], &QPushButton::clicked, this, [&](){
        this->swapMove(3, 3);
        if(this->isCompleted()) {
            mess->exec();
        }
    });



}

mainWidget::~mainWidget()
{
    delete ui;
}

// 移动被点击的块
void mainWidget::swapMove(int x, int y) {
    // 空白块被点击不需要移动
    if(this->blks[x][y]->getValue() == 15) {
        return;
    }
    // 找出被点击块的周围的空白块并移动，否则不做任何操作
    int nx = x, ny = y;
    if(x-1 >= 0 && this->blks[x-1][y]->getValue() == 15) {
        nx = x-1;
        ny = y;
    }
    else if(y-1 >= 0 && this->blks[x][y-1]->getValue() == 15) {
        nx = x;
        ny = y-1;
    }
    else if(x+1 < 4 && this->blks[x+1][y]->getValue() == 15) {
        nx = x+1;
        ny = y;
    }
    else if(y+1 < 4 && this->blks[x][y+1]->getValue() == 15) {
        nx = x;
        ny = y+1;
    }
    else {
        return;
    }
    int t = this->blks[x][y]->getValue();
    this->blks[x][y]->setValue(this->blks[nx][ny]->getValue());
    this->blks[nx][ny]->setValue(t);
    return;
}

// 判断是否完成拼图
bool mainWidget::isCompleted() {
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(this->blks[i][j]->getValue() != (i*4 + j)) {
                return false;
            }
        }
    }
    return true;
}

void mainWidget::shuffle(int n) {
    QTime randtime;
    randtime = QTime::currentTime();
    qsrand(randtime.msec()+randtime.second()*1000);
    while(n--) {
        int x = qrand() % 4;
        int y = qrand() % 4;
        this->swapMove(x, y);
    }
}



