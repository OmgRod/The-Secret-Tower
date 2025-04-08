#include <Geode/Geode.hpp>

using namespace geode::prelude;

class CustomTowerLayer : public LevelAreaInnerLayer {
public:
    virtual void keyBackClicked();
    void backWrapper(CCObject* sender);
    static CCScene* scene();
    static CustomTowerLayer* create();
    bool init(bool p0, bool nextFloorLocked = false);
    // void playLevel5005(CCObject* sender);
    // void playLevel5006(CCObject* sender);
    // void playLevel5007(CCObject* sender);
    // void playLevel5008(CCObject* sender);
    void onDoor(CCObject* sender);
};