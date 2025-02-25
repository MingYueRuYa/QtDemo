#ifndef ROTATINGIMAGE_H
#define ROTATINGIMAGE_H

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>

class RotatingImage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)

public:
    explicit RotatingImage(QWidget *parent = nullptr);

    qreal rotation() const { return m_rotation; }
    void setRotation(qreal rotation);

    public slots:
    void startRotation();
    void stopRotation();
    void pauseRotation();
    void resumeRotation();
    void setRotationDuration(int msecs);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void updatePixmap();
    QPixmap getScaledPixmap() const;

private:
    QLabel *imageLabel;
    QPropertyAnimation *rotationAnimation;
    qreal m_rotation;
    QPixmap originalPixmap;
    QSize targetSize;
};

#endif // ROTATINGIMAGE_H 