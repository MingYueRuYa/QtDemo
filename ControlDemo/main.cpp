#include "ControlDemo.h"
#include <QtWidgets/QApplication>
#include <QPushButton>
// main.cpp
#include <QtWidgets>
#include "Button/animation_button.hpp"

#pragma execution_character_set("utf-8")



class ColorFadeButton : public QPushButton {
    Q_OBJECT
        Q_PROPERTY(QColor bg READ bg WRITE setBg)
public:
    explicit ColorFadeButton(const QString& text, QWidget* parent = nullptr)
        : QPushButton(text, parent), bgColor(palette().button().color()) {
        setAutoFillBackground(true);
        orig = bgColor;
        applyPalette();
    }
    QColor bg() const { return bgColor; }
    void setBg(const QColor& c) { bgColor = c; applyPalette(); }
protected:
    void enterEvent(QEvent* e) override {
        animateTo(palette().highlight().color().lighter(120));
        QPushButton::enterEvent(e);
    }
    void leaveEvent(QEvent* e) override {
        animateTo(orig);
        QPushButton::leaveEvent(e);
    }
private:
    QColor bgColor, orig;
    QScopedPointer<QPropertyAnimation> anim;
    void applyPalette() {
        QPalette pal = palette();
        pal.setColor(QPalette::Button, bgColor);
        setPalette(pal);
        update();
    }
    void animateTo(const QColor& c) {
        if (!anim) anim.reset(new QPropertyAnimation(this, "bg"));
        anim->stop();
        anim->setDuration(180);
        anim->setEasingCurve(QEasingCurve::OutCubic);
        anim->setStartValue(bgColor);
        anim->setEndValue(c);
        anim->start();
    }
};

class RippleButton : public QPushButton {
    Q_OBJECT
public:
    explicit RippleButton(const QString& text, QWidget* parent = nullptr)
        : QPushButton(text, parent) {
        setMouseTracking(true);
    }
protected:
    void enterEvent(QEvent* e) override { animateScale(1.08, 120); QPushButton::enterEvent(e); }
    void leaveEvent(QEvent* e) override { animateScale(1.0, 120); QPushButton::leaveEvent(e); }
    void mousePressEvent(QMouseEvent* e) override {
        rippleCenter = e->pos();
        startRipple();
        //animateBounce();
        QPushButton::mousePressEvent(e);
    }
    void paintEvent(QPaintEvent* e) override {
        QPushButton::paintEvent(e);
        if (!rippleAnim || rippleAnim->state() != QAbstractAnimation::Running) return;
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        QColor c = palette().highlight().color();
        c.setAlphaF(rippleOpacity);
        p.setBrush(c);
        p.setPen(Qt::NoPen);
        p.drawEllipse((QPointF)rippleCenter, rippleRadius, rippleRadius);
    }
private:
    QPoint rippleCenter;
    qreal rippleRadius = 0;
    qreal rippleOpacity = 0;
    QScopedPointer<QPropertyAnimation> scaleAnim;
    QScopedPointer<QSequentialAnimationGroup> rippleAnim;

    void animateScale(qreal target, int duration) {
        if (!scaleAnim) scaleAnim.reset(new QPropertyAnimation(this, "geometry", this));
        QRect g = geometry();
        QSize base = sizeHint();
        int w = int(base.width() * target);
        int h = int(base.height() * target);
        QRect targetRect(g.center().x() - w / 2, g.center().y() - h / 2, w, h);
        scaleAnim->stop();
        scaleAnim->setDuration(duration);
        scaleAnim->setEasingCurve(QEasingCurve::OutCubic);
        scaleAnim->setStartValue(g);
        scaleAnim->setEndValue(targetRect);
        scaleAnim->start();
    }
    void animateBounce() {
        auto* anim = new QPropertyAnimation(this, "pos");
        anim->setDuration(180);
        anim->setEasingCurve(QEasingCurve::OutBounce);
        anim->setStartValue(pos());
        anim->setEndValue(pos() + QPoint(0, 6));
        connect(anim, &QPropertyAnimation::finished, anim, &QObject::deleteLater);
        anim->start();
    }
    void startRipple() {
        rippleAnim.reset(new QSequentialAnimationGroup(this));
        auto* grow = new QVariantAnimation;
        grow->setDuration(200);
        grow->setStartValue(0.0);
        grow->setEndValue(qreal(width()) * 0.8);
        connect(grow, &QVariantAnimation::valueChanged, this, [this](const QVariant& v) {
            rippleRadius = v.toReal();
            rippleOpacity = 0.35;
            update();
            });
        auto* fade = new QVariantAnimation;
        fade->setDuration(180);
        fade->setStartValue(0.35);
        fade->setEndValue(0.0);
        connect(fade, &QVariantAnimation::valueChanged, this, [this](const QVariant& v) {
            rippleOpacity = v.toReal();
            update();
            });
        rippleAnim->addAnimation(grow);
        rippleAnim->addAnimation(fade);
        rippleAnim->start();
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QWidget w;
    w.setWindowTitle(QStringLiteral("QPushButton 动画示例 (Qt5)"));
    auto* layout = new QVBoxLayout(&w);
    layout->setSpacing(12);

    auto* btnHover = new HoverOpacityButton(QStringLiteral("悬停透明度"));
    auto* btnFade = new QPushButton(QStringLiteral("点击渐隐/渐显"));
    auto* fadeEff = new QGraphicsOpacityEffect(btnFade);
    fadeEff->setOpacity(1.0);
    btnFade->setGraphicsEffect(fadeEff);

    auto* btnColor = new ColorFadeButton(QStringLiteral("颜色渐变"));
    btnColor->setBg("#FF00FF");
    auto* btnRipple = new RippleButton(QStringLiteral("波纹 + 弹跳"));

    layout->addWidget(btnHover);
    layout->addWidget(btnFade);
    layout->addWidget(btnColor);
    layout->addWidget(btnRipple);
    layout->addStretch();

    // 点击渐隐/渐显
    QObject::connect(btnFade, &QPushButton::clicked, [fadeEff]() {
        auto* a = new QPropertyAnimation(fadeEff, "opacity");
        a->setDuration(220);
        a->setEasingCurve(QEasingCurve::InOutQuad);
        a->setStartValue(1.0);
        a->setEndValue(0.0);
        QObject::connect(a, &QPropertyAnimation::finished, [fadeEff, a]() {
            auto* b = new QPropertyAnimation(fadeEff, "opacity");
            b->setDuration(220);
            b->setEasingCurve(QEasingCurve::InOutQuad);
            b->setStartValue(0.0);
            b->setEndValue(1.0);
            QObject::connect(b, &QPropertyAnimation::finished, b, &QObject::deleteLater);
            b->start();
            a->deleteLater();
            });
        a->start();
        });

    w.resize(360, 260);
    w.show();
    return app.exec();
}

#include "main.moc"
//#include "main.moc"

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    ControlDemo w;
//    w.show();
//    return a.exec();
//}
