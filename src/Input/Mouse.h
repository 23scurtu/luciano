#pragma once

#include <mutex>
#include <vector>
#include <glm/glm.hpp>
// Include keyboard for KeyAction
// TODO Refactor Input classes
#include "Keyboard.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window;

using namespace std;

int const MAX_BUTTON = GLFW_MOUSE_BUTTON_LAST;

enum Button
{
  LEFT_BUTTON = GLFW_MOUSE_BUTTON_LEFT,
  RIGHT_BUTTON = GLFW_MOUSE_BUTTON_RIGHT
};

enum Mode
{
    DEFAULT_CURSOR = GLFW_CURSOR_NORMAL, // Cursor shown and position on the window is used
    DISABLED_CURSOR = GLFW_CURSOR_DISABLED, // Hide cursor, lock it to the window, and unlimited movement
    HIDDEN_CURSOR = GLFW_CURSOR_HIDDEN // Same as default but cursor is hidden
};

class Mouse
{
    friend class Window;

    // TODO Make mode changeable, give Mouse access to window.
    // Give Mouse and Keyboards a window pointer? 
    // Abstract input device to unify interfface
    Mode mode;

    KeyAction *button_buffer;
    KeyAction *intermediate_button_buffer;

    glm::vec2 pos;
    glm::vec2 scroll;
    glm::vec2 intermediate_pos;
    glm::vec2 intermediate_scroll;

    mutex  intermediate_buffer_lock;

    void cursorPosCallback(double xpos, double ypos);
    void scrollCallback(double xoffset, double yoffset);
    void mouseButtonCallback(int button, int action, int mods);

public:
    Mouse(Mode mode = DEFAULT_CURSOR);
    void update();

    Mode getMode();
    glm::vec2 getPosInput();
    // For normal mouse wheels, only yoffset is used.
    glm::vec2 getScrollInput();
    KeyAction getButtonInput(Button button);
};