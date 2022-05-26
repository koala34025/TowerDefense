#ifndef ArcherBullet_hpp
#define ArcherBullet_hpp

#include <allegro5/allegro.h>
#include "ArmyBullet.hpp"

class Army;
class Defense;
namespace Engine {
struct Point;
}  // namespace Engine

class ArcherBullet: public ArmyBullet{
public:
    explicit ArcherBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent);
    void OnExplode(Defense* defense) override;
};

class FrozenBullet : public ArmyBullet {
public:
    explicit FrozenBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent);
    void OnExplode(Defense* defense) override;
    void Update(float deltaTime) override;
    ALLEGRO_TIMER* freeze_timer;
    ALLEGRO_EVENT_QUEUE* queue;
};
#endif /* ArcherBullet_hpp */
