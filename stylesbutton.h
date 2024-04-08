#ifndef STYLEDBUTTON_H
#define STYLEDBUTTON_H

#include <QPushButton>

class StyledButton : public QPushButton
{
    Q_OBJECT
public:
    explicit StyledButton(const QString &text, QWidget *parent = nullptr);
};

#endif // STYLEDBUTTON_H
