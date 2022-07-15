#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "block.h"
#include <QMessageBox>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class mainWidget; }
QT_END_NAMESPACE

const int picNum = 5;

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget* parent = nullptr);
    ~mainWidget();
    // 移动被点击的块
    void swapMove(int x, int y);
    // 判断是否完成拼图
    bool isCompleted();
    // 随机打乱图片
    void shuffle(int n = 10000000);

private:
    Ui::mainWidget *ui;
    //背景音乐
    QMediaPlayer* mediaPlayer_gameWindowBackground;
    QMediaPlaylist* mediaPlaylist_gameWindowBackground;
    // 图片编号
    int pnum;
    // 4*4的块
    Block* blks[4][4];
    // 游戏完成提示框
    QMessageBox* mess;
};
#endif // MAINWIDGET_H
