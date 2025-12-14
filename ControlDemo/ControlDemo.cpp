#include "ControlDemo.h"


#include <QPainter>
#include <QProxyStyle>
#include <QStyleOptionTab>

const int kTAB_ITEM_WIDTH = 120;
const int kTAB_ITEM_HEIGHT = 40;

class CustomTabStyle : public QProxyStyle {
 public:
  QSize sizeFromContents(ContentsType type, const QStyleOption *option,
                         const QSize &size, const QWidget *widget) const {
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == QStyle::CT_TabBarTab) {
      s.transpose();
      s.rwidth() = kTAB_ITEM_WIDTH;  // 设置每个tabBar中item的大小
      s.rheight() = kTAB_ITEM_HEIGHT;
    }
    return s;
  }

  void drawControl(ControlElement element, const QStyleOption *option,
                   QPainter *painter, const QWidget *widget) const {
    if (element == CE_TabBarTabLabel) {
      if (const QStyleOptionTab *tab =
              qstyleoption_cast<const QStyleOptionTab *>(option)) {
        QRect allRect = tab->rect;

        if (tab->state & QStyle::State_Selected) {
          painter->save();
          painter->setPen(0x89cfff);
          painter->setBrush(QBrush(0x89cfff));
          painter->drawRect(allRect.adjusted(6, 6, -6, -6));
          painter->restore();
        } else if (tab->state & QStyle::State_MouseOver) {
          painter->save();
          painter->setPen(0x000fff);
          painter->setBrush(QBrush(0x000fff));
          painter->drawRect(allRect.adjusted(6, 6, -6, -6));
          painter->restore();
        }

        QTextOption option;
        option.setAlignment(Qt::AlignCenter);
        if (tab->state & QStyle::State_Selected) {
          painter->setPen(0xf8fcff);
        } else if (tab->state & QStyle::State_MouseOver) {
          painter->setPen(0x00FF00);
        } else {
          painter->setPen(0x5d5d5d);
        }

        painter->drawText(allRect, tab->text, option);
        return;
      }
    }

    if (element == CE_TabBarTab) {
      QProxyStyle::drawControl(element, option, painter, widget);
    }
  }
};

ControlDemo::ControlDemo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.tabWidget->setTabPosition(QTabWidget::West);
    ui.tabWidget->tabBar()->setStyle(new CustomTabStyle());
    ui.tabWidget->setStyleSheet(R"(QTabWidget::pane { border: 1px solid #dcdcdc;})");
}
