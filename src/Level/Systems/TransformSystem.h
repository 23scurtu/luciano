#include "entityx/entityx.h"
#include "Level/Components.h"

class TransformSystem: public entityx::System<TransformSystem>
{
  // TODO Move these helpers to transform component?
  friend class Transform;

  static void recalculateFinal(entityx::ComponentHandle<Transform> transform);
  static void recalculateInverseFinal(entityx::ComponentHandle<Transform> transform);
  static void dirtyChildren(entityx::ComponentHandle<Transform> transform);
  static void dirtyInverseChildren(entityx::ComponentHandle<Transform> transform);
  
public:
  TransformSystem();
  void update(entityx::EntityManager &es,
              entityx::EventManager &events,
              entityx::TimeDelta dt) override;
};
