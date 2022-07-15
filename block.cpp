#include "block.h"

// 构造函数
Block::Block(QWidget* parent) {
    this->p = 0;
    this->value = 0;
    this->setParent(parent);
    this->setFixedSize(100, 100);
    this->updateImage();
}

// 根据value值设定每个块的图片
void Block::setButtonImage(QString image) {
    this->setText("");
    QPixmap pixmap(image);
    QPixmap fitpixmap = pixmap.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->setIcon(QIcon(fitpixmap));
    this->setIconSize(QSize(100, 100));
    this->setFlat(true);
    this->setStyleSheet("border: 0px;");
}

// 获取块的value值
int Block::getValue() {
    return this->value;
}

// 修改块的value值
void Block::setValue(int v) {
    if(v < 0 || v > 15) {
        return;
    }
    this->value = v;
    this->updateImage();
}

// 切换图片
void Block::setP(int p) {
    this->p = p;
    this->updateImage();
}

// 根据value、p的值每次刷新应该显示的图片
void Block::updateImage() {
    QString image = ":/puzzles/p" + QString::number(this->p, 10) + "/" + QString::number(this->value,10) + ".jpg";
    this->setButtonImage(image);
}
