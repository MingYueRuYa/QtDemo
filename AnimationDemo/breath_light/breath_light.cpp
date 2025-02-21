#ifndef BUTTON_H
#define BUTTON_H

#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QPainter>
#include <QColor>
#include <QWidget>

class BreathingLight : public QWidget {
  Q_OBJECT
  Q_PROPERTY(int alpha READ alpha WRITE setAlpha)

 public:
  BreathingLight(QWidget *parent = nullptr) : QWidget(parent), m_alpha(0) {
    setFixedSize(200, 200);

    // 创建两个动画，一个从0到255，一个从255到0
    QPropertyAnimation *animationUp = new QPropertyAnimation(this, "alpha");
    animationUp->setDuration(2500);  // 动画时长为2000毫秒
    animationUp->setStartValue(20);   // 起始透明度
    animationUp->setEndValue(255);   // 结束透明度
    animationUp->setEasingCurve(
        QEasingCurve::InOutQuad);  // 使用平滑的缓入缓出动画曲线

    QPropertyAnimation *animationDown = new QPropertyAnimation(this, "alpha");
    animationDown->setDuration(2500);   // 动画时长为2000毫秒
    animationDown->setStartValue(255);  // 起始透明度
    animationDown->setEndValue(20);      // 结束透明度
    animationDown->setEasingCurve(
        QEasingCurve::InOutQuad);  // 使用平滑的缓入缓出动画曲线

    // 创建一个动画组，将两个动画添加进去，并设置为循环播放
    QSequentialAnimationGroup *animationGroup =
        new QSequentialAnimationGroup(this);
    animationGroup->addAnimation(animationUp);
    animationGroup->addAnimation(animationDown);
    animationGroup->setLoopCount(-1);  // 无限循环
    animationGroup->start();           // 启动动画组
  }

  int alpha() const { return m_alpha; }

  void setAlpha(int alpha) {
    m_alpha = alpha;
    update();  // 更新窗口，触发重绘事件
  }

 protected:
  void paintEvent(QPaintEvent *event) override {
    Q_UNUSED(event);
    QPainter painter(this);
    QColor color(0, 255, 0, m_alpha);  // 绿色，使用 m_alpha 透明度
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    QRect paint_rect = rect();
    paint_rect.adjust(90, 90, -90, -90);
    painter.drawEllipse(paint_rect);  // 绘制一个椭圆，填充整个窗口
  }

 private:
  int m_alpha;
};

#include <QApplication>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include "button.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //button.show();

    BreathingLight light;
    light.show();

    return a.exec();
}

#endif // BUTTON_H