#pragma once
#include <QPushButton>

class StateButton : public QPushButton {
  Q_OBJECT
 public:
  enum State { Normal, Loading, Success };
  Q_ENUM(State)

  explicit StateButton(QWidget *parent = nullptr);

  void setState(State state);

 private:
  State m_state;
};