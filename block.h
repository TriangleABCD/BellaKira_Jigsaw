#ifndef BLOCK_H
#define BLOCK_H
#include <QPushButton>
#include <QWidget>

class Block : public QPushButton
{
private:
    // 表示碎片编号, 0-15, 15表示空白块
    int value;
    // 表示图片编号
    int p;
public:
    // 构造函数
    Block(QWidget* parent = nullptr);
    // 根据value值设定每个块的图片
    void setButtonImage(QString image);
    // 获取块的value值
    int getValue();
    // 修改块的value值
    void setValue(int v);
    // 切换图片
    void setP(int p);
    // 根据value、p的值每次刷新应该显示的图片
    void updateImage();
};

#endif // BLOCK_H
