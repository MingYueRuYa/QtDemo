#include "rotatingimage.h"
#include <QPixmap>
#include <QTransform>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPainter>
#include <QEasingCurve>

RotatingImage::RotatingImage(QWidget *parent)
    : QWidget(parent), m_rotation(0)
{
    // 创建布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    
    // 创建标签并设置图片
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(QSize(200, 200));
    originalPixmap.load(":/images/test.png");
    
    // 设置目标大小
    targetSize = QSize(200, 200);  // 比Label小一点，留出边距
    
    // 初始化图片
    updatePixmap();
    
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("QLabel { border-radius: 100px; background: transparent; }");
    layout->addWidget(imageLabel, 0, Qt::AlignCenter);

    // 设置动画
    rotationAnimation = new QPropertyAnimation(this, "rotation", this);
    rotationAnimation->setStartValue(0.0);
    rotationAnimation->setEndValue(360.0);
    rotationAnimation->setDuration(5000);
    rotationAnimation->setLoopCount(-1);
    
    // 使用QEasingCurve使动画更流畅
    rotationAnimation->setEasingCurve(QEasingCurve::Linear);
    rotationAnimation->start();
}

void RotatingImage::setRotation(qreal rotation)
{
    if (m_rotation != rotation) {
        m_rotation = rotation;
        updatePixmap();
    }
}

void RotatingImage::updatePixmap()
{
    QPixmap scaledPix = getScaledPixmap();
    
    // 创建一个透明的目标图片，大小与Label相同
    QPixmap targetPixmap(imageLabel->size());
    targetPixmap.fill(Qt::transparent);
    
    // 在目标图片上绘制旋转后的图片
    QPainter painter(&targetPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    
    // 计算中心点
    QPointF center = targetPixmap.rect().center();
    painter.translate(center);
    painter.rotate(m_rotation);
    painter.translate(-center);
    
    // 计算绘制位置使图片居中
    QPointF drawPos(
        (targetPixmap.width() - scaledPix.width()) / 2.0,
        (targetPixmap.height() - scaledPix.height()) / 2.0
    );
    
    painter.drawPixmap(drawPos, scaledPix);
    painter.end();
    
    imageLabel->setPixmap(targetPixmap);
}

QPixmap RotatingImage::getScaledPixmap() const
{
    return originalPixmap.scaled(
        targetSize,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );
}

void RotatingImage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updatePixmap();
}

void RotatingImage::startRotation()
{
    rotationAnimation->start();
}

void RotatingImage::stopRotation()
{
    rotationAnimation->stop();
}

void RotatingImage::pauseRotation()
{
    rotationAnimation->pause();
}

void RotatingImage::resumeRotation()
{
    rotationAnimation->resume();
}

void RotatingImage::setRotationDuration(int msecs)
{
    rotationAnimation->setDuration(msecs);
} 
