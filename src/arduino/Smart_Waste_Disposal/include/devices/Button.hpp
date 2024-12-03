#ifndef __BUTTON__
#define __BUTTON__

/// @brief Class to use buttons by polling
class Button {
private:
    int pin;
public:
    /// @brief Button constructor, it creates a button and sets the pin in INPUT mode.
    /// @param pin the input pin for the button.
    Button(int pin);
    
    /// @brief Method that returns if the button is pressed.
    /// @return 1 if the button is pressed, 0 otherwise.
    int isPressed();
};

#endif
