#include <map>
#include "Mouse.h"
#include <iostream>

using namespace std;

Mouse::Mouse(Mode mode):
  button_buffer{new KeyAction[MAX_KEY]},
  intermediate_button_buffer{new KeyAction[MAX_KEY]},
  mode{mode},
  pos{glm::vec2(0.0,0.0)},
  scroll{glm::vec2(0.0,0.0)},
  intermediate_pos{glm::vec2(0.0,0.0)},
  intermediate_scroll{glm::vec2(0.0,0.0)}
{
    // TODO Perhaps combine mouse button code with keyboard and leave with scroll and pos
    for(int i = 0; i < MAX_KEY; i++)intermediate_button_buffer[i] = RELEASE;
    for(int i = 0; i < MAX_KEY; i++)button_buffer[i] = RELEASE;
}

void Mouse::mouseButtonCallback(int button, int action, int mods)
{
  intermediate_buffer_lock.lock();
  intermediate_button_buffer[button] = KeyAction(action);
  intermediate_buffer_lock.unlock();
}

void Mouse::cursorPosCallback(double xpos, double ypos)
{
    intermediate_buffer_lock.lock();
    intermediate_pos = glm::vec2(xpos, ypos);
    intermediate_buffer_lock.unlock();
}
    
void Mouse::scrollCallback(double xoffset, double yoffset)
{
    intermediate_buffer_lock.lock();
    intermediate_scroll = glm::vec2(xoffset, yoffset);
    intermediate_buffer_lock.unlock();
}

void Mouse::update()
{
  // Swap buffers. All calls to get keys inputs will
  // be the same until update is called again.
  intermediate_buffer_lock.lock();

  // Copy intermediate buffer.
  for(int i = 0; i < MAX_KEY; i++)button_buffer[i] = intermediate_button_buffer[i];

  pos = intermediate_pos;
  scroll = intermediate_scroll;

  intermediate_buffer_lock.unlock();
}

KeyAction Mouse::getButtonInput(Button button)
{
  return button_buffer[button];
}

glm::vec2 Mouse::getPosInput()
{
    return pos;
}

glm::vec2 Mouse::getScrollInput()
{
    return scroll;
}

Mode Mouse::getMode()
{
    return mode;
}