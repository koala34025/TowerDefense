#ifndef BombArmy_hpp
#define BombArmy_hpp

#include "Army.hpp"

class BombArmy: public Army {
public:
    BombArmy(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
};

class Enemy4Army : public Army {
public:
    Enemy4Army(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
};


#endif /* BombArmy_hpp */
