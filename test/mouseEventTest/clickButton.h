#ifndef TEST_CLICKBUTTON_H
#define TEST_CLICKBUTTON_H

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
