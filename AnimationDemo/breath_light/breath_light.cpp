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

    // ��������������һ����0��255��һ����255��0
    QPropertyAnimation *animationUp = new QPropertyAnimation(this, "alpha");
    animationUp->setDuration(2500);  // ����ʱ��Ϊ2000����
    animationUp->setStartValue(20);   // ��ʼ͸����
    animationUp->setEndValue(255);   // ����͸����
    animationUp->setEasingCurve(
        QEasingCurve::InOutQuad);  // ʹ��ƽ���Ļ��뻺����������

    QPropertyAnimation *animationDown = new QPropertyAnimation(this, "alpha");
    animationDown->setDuration(2500);   // ����ʱ��Ϊ2000����
    animationDown->setStartValue(255);  // ��ʼ͸����
    animationDown->setEndValue(20);      // ����͸����
    animationDown->setEasingCurve(
        QEasingCurve::InOutQuad);  // ʹ��ƽ���Ļ��뻺����������

    // ����һ�������飬������������ӽ�ȥ��������Ϊѭ������
    QSequentialAnimationGroup *animationGroup =
        new QSequentialAnimationGroup(this);
    animationGroup->addAnimation(animationUp);
    animationGroup->addAnimation(animationDown);
    animationGroup->setLoopCount(-1);  // ����ѭ��
    animationGroup->start();           // ����������
  }

  int alpha() const { return m_alpha; }

  void setAlpha(int alpha) {
    m_alpha = alpha;
    update();  // ���´��ڣ������ػ��¼�
  }

 protected:
  void paintEvent(QPaintEvent *event) override {
    Q_UNUSED(event);
    QPainter painter(this);
    QColor color(0, 255, 0, m_alpha);  // ��ɫ��ʹ�� m_alpha ͸����
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    QRect paint_rect = rect();
    paint_rect.adjust(90, 90, -90, -90);
    painter.drawEllipse(paint_rect);  // ����һ����Բ�������������
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