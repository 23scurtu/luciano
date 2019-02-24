#include "Command.h"
#include <iostream>

using namespace std;

void MoveCommand::execute(entityx::Entity &entity)
{
  entityx::ComponentHandle<MoveAction> action = entity.component<MoveAction>();
  if(!action)
  {
    entity.assign<MoveAction>(direction);
    action = entity.component<MoveAction>();
  }

  // TEMP Code to test actions 
  // TODO Adding dirction twice?
  action->velocity += direction;
}

void RotateCommand::execute(entityx::Entity &entity)
{
  entityx::ComponentHandle<RotateAction> action = entity.component<RotateAction>();
  if(!action)
  {
    entity.assign<RotateAction>(glm::vec3(0.0,0.0,0.0));
    action = entity.component<RotateAction>();
  }

  // TEMP Code to test actions 
  // TODO Make from center?
  switch(axis)
  {
    case X_AXIS: action->rotation.x += getAnalog(); break;
    case Y_AXIS: action->rotation.y += getAnalog(); break;
    case Z_AXIS: action->rotation.z += getAnalog(); break;
  }
}