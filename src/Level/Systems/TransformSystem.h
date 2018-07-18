#include "entityx/entityx.h"
#include "Level/Components.h"

class TransformSystem: public entityx::System<TransformSystem>
{
  void recalculateFinal(entityx::ComponentHandle<Transform> transform);
  void dirtyChildren(entityx::ComponentHandle<Transform> transform);
  
public:
  TransformSystem();
  void update(entityx::EntityManager &es,
              entityx::EventManager &events,
              entityx::TimeDelta dt) override;
};
