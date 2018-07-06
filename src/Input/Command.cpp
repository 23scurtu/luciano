#include "Command.h"

void MoveCommand::execute(entityx::Entity &entity)
{
  entityx::ComponentHandle<MoveAction> action = entity.component<MoveAction>();
  if(!action)
  {
    entity.assign<MoveAction>(direction);
    action = entity.component<MoveAction>();
  }

  // TEMP Code to test actions 
  action->velocity += direction;
}
