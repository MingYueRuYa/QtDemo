#ifndef animation_button
#define animation_button

#include <QPushButton>
#include <QGraphicsOpacityEffect>
#include <QEvent>
#include <QPropertyAnimation>

#pragma execution_character_set("utf-8")

class HoverOpacityButton : public QPushButton {
  Q_OBJECT
 public:
  explicit HoverOpacityButton(const QString& text, QWidget* parent = nullptr)
      : QPushButton(text, parent) {
    setAttribute(Qt::WA_Hover, true);
    auto* eff = new QGraphicsOpacityEffect(this);
    eff->setOpacity(0.9);
    setGraphicsEffect(eff);
  }

 protected:
  bool event(QEvent* e) override {
    if (e->type() == QEvent::Enter || e->type() == QEvent::HoverEnter) {
      animateTo(0.4);
    } else if (e->type() == QEvent::Leave || e->type() == QEvent::HoverLeave) {
      animateTo(1.0);
    }
    return QPushButton::event(e);
  }

 private:
  void animateTo(qreal end) {
    auto* eff = qobject_cast<QGraphicsOpacityEffect*>(graphicsEffect());
    if (!eff) return;
    auto* a = new QPropertyAnimation(eff, "opacity", eff);
    a->setDuration(1000);
    a->setEasingCurve(QEasingCurve::OutCubic);
    a->setStartValue(eff->opacity());
    a->setEndValue(end);
    connect(a, &QPropertyAnimation::finished, a, &QObject::deleteLater);
    a->start();
  }
};

#endif // animation_button
