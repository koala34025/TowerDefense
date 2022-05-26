#ifndef WallDefense_hpp
#define WallDefense_hpp

#include "Defense.hpp"

class WallDefense: public Defense{
public:
    WallDefense(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
    void UpdateBrokenWall();
};

class TrapDefense : public Defense {
public:
    TrapDefense(float x, float y);
    void CreateBullet(Engine::Point pt) override;
    void Update(float deltaTime) override;
    void Draw() const override;
};

#endif /* WallDefense_hpp */
