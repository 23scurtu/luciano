#include <map>
#include "Keyboard.h"
#include <iostream>

using namespace std;

Keyboard::Keyboard():
  keyboard_buffer{new KeyAction[MAX_KEY]},
  intermediate_keyboard_buffer{new KeyAction[MAX_KEY]}
{
  for(int i = 0; i < MAX_KEY; i++)intermediate_keyboard_buffer[i] = RELEASE;
  for(int i = 0; i < MAX_KEY; i++)keyboard_buffer[i] = RELEASE;
}

void Keyboard::keyInputCallback(int key, int scancode, int action, int mods)
{
  intermediate_buffer_lock.lock();
  intermediate_keyboard_buffer[key] = KeyAction(action);
  intermediate_buffer_lock.unlock();
}

void Keyboard::update()
{
  // Swap buffers. All calls to get keys inputs will
  // be the same until update is called again.

  intermediate_buffer_lock.lock();

  // Copy intermediate buffer.
  for(int i = 0; i < MAX_KEY; i++)keyboard_buffer[i] = intermediate_keyboard_buffer[i];

  intermediate_buffer_lock.unlock();
}

KeyAction Keyboard::getKeyInput(Key key)
{
  return keyboard_buffer[key];
}
