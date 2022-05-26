#include <allegro5/base.h>
#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "ArcherBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Defense.hpp"
#include "ExplosionEffect.hpp"
#include "Collider.hpp"

class Defense;

//ArmyBullet::ArmyBullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent)
ArcherBullet::ArcherBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent) :
    ArmyBullet("play/sword.png", 40, 5, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}

void ArcherBullet::OnExplode(Defense *defense) {
    // TODO 3 (1/2): Add a ShootEffect here. Remember you need to include the class.
    getPlayScene()->EffectGroup->AddNewObject(new ShootEffect(defense->Position.x, defense->Position.y));
}

// end of archer bullet

// start of frozen bullet

FrozenBullet::FrozenBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Army* parent) :
    ArmyBullet("play/frozen.png", 0, 0, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
    freeze_timer = al_create_timer(1.0f / 60.0f);
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_timer_event_source(freeze_timer));
    al_start_timer(freeze_timer);
}

void FrozenBullet::OnExplode(Defense* defense) {}

void FrozenBullet::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    PlayScene* scene = getPlayScene();

    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    for (auto& it : scene->DefenseGroup->GetObjects()) {
        Defense* defense = dynamic_cast<Defense*>(it);
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, defense->Position, defense->CollisionRadius)) {
            defense->Enabled = false;
        }
    }

    if (al_get_timer_count(freeze_timer) > 120) {
        for (auto& it : scene->DefenseGroup->GetObjects()) {
            Defense* defense = dynamic_cast<Defense*>(it);
            if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, defense->Position, defense->CollisionRadius)) {
                defense->Enabled = true;
            }
        }
        al_destroy_timer(freeze_timer);
        al_destroy_event_queue(queue);
        getPlayScene()->BulletGroup->RemoveObject(objectIterator);
        return;
    }

    // Check if out of boundary.
    if (Position.x < 0 || Position.x > PlayScene::GetClientSize().x || Position.y < 0 || Position.y > PlayScene::GetClientSize().y)
        getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}