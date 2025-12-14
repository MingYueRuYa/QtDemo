#include "StateButton.h"

#include <QStyle>
#include <QVariant>

StateButton::StateButton(QWidget *parent) : QPushButton(parent) {
  // setFixedHeight(40);
  setStyleSheet(R"(StateButton[state="0"] {
    background-color: #409EFF;
    color: white;
}
StateButton[state="1"] {
    background-color: #909399;
    color: white;
}
StateButton[state="2"] {
    background-color: #67C23A;
    color: white;
})");
  setState(Normal);
}

void StateButton::setState(StateButton::State state) {
  m_state = state;
  setProperty("state", (int)state);

  switch (state) {
    case Normal:
      setText("提交");
      setEnabled(true);
      break;
    case Loading:
      setText("处理中...");
      setEnabled(false);
      break;
    case Success:
      setText("完成");
      setEnabled(true);
      break;
  }

  style()->unpolish(this);
  style()->polish(this);
}