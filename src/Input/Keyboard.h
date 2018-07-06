#pragma once

#include <mutex>
#include <vector>
#include "Keyboard.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window;

using namespace std;

int const MAX_KEY = GLFW_KEY_LAST;

enum Key
{
  W_KEY = GLFW_KEY_W,
  A_KEY = GLFW_KEY_A,
  S_KEY = GLFW_KEY_S,
  D_KEY = GLFW_KEY_D
};

enum KeyAction
{
  PRESS = GLFW_PRESS,
  RELEASE = GLFW_RELEASE,
  REPEAT = GLFW_REPEAT
};


class Keyboard
{
  friend class Window;

  KeyAction *keyboard_buffer;
  KeyAction *intermediate_keyboard_buffer;

  mutex  intermediate_buffer_lock;

  void keyInputCallback(int key, int scancode, int action, int mods);

public:
  Keyboard();
  void update();
  KeyAction getKeyInput(Key key);
};
