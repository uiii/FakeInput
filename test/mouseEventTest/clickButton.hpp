#ifndef TEST_CLICKBUTTON_HPP
#define TEST_CLICKBUTTON_HPP

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class ClickButton : public QPushButton
{
public:
    ClickButton(QWidget* parent);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif
