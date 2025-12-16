#include "ControlDemo.h"


#include <QPainter>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QDebug>
#include <QButtonGroup>
#include <deque>

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

    _init_btn();
}

void ControlDemo::on_test_state_btn_clicked() {
  static std::deque<StateButton::State> dequeState = {
      StateButton::State::Loading, StateButton::State::Success,
      StateButton::State::Normal};
  auto cur = dequeState.front();
  ui.stateButton->setState(cur);
  dequeState.pop_front();
  dequeState.push_back(cur);
}


void ControlDemo::_init_btn() { 
  ui.stateButton->setState(StateButton::State::Normal); 

  QString btn_style = R"(QPushButton {
    border: 1px solid #dcdfe6;
    padding: 6px 12px;
}
QPushButton:checked {
    background-color: #409EFF;
    color: white;
})";

  QButtonGroup *group = new QButtonGroup(this);
  std::vector<QPushButton *> vec_btn = {ui.pushButton_1, ui.pushButton_2,
                                        ui.pushButton_3};
  for (int i = 0; i < vec_btn.size(); ++i) {
    QPushButton *btn = vec_btn[i];
    btn->setStyleSheet(btn_style);
    btn->setCheckable(true);
    btn->setProperty("mode", i);
    group->addButton(btn, i);
  }
    connect(group, &QButtonGroup::idClicked, this,
            [](int id) { qDebug() << "current mode:"<< id; });
}

