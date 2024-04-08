#include "stylesbutton.h"

StyledButton::StyledButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    // Set the button's text alignment to left using a style sheet
    // Remove button decoration and change background on hover
    this->setStyleSheet(R"(
  StyledButton {
            text-align: left;
            border: none;
            background-color: white;font-weight:bold;
            padding: 10px; /* Adjust padding as needed */
            margin: 0px; /* Ensure no margin */
        }
        StyledButton:hover {
            background-color: rgba(255, 255, 255, 127); /* 50% opacity for white background */
        }
    )");
}
