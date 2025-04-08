#include <Geode/Geode.hpp>

using namespace geode::prelude;

class CustomTowerLayer : public LevelAreaInnerLayer {
public:
    virtual void keyBackClicked();
    void backWrapper(CCObject* sender);
    static CCScene* scene();
    static CustomTowerLayer* create();
    bool init(bool p0, bool nextFloorLocked = false);
    void playLevel5001(CCObject* sender);
    void playLevel5002(CCObject* sender);
    void playLevel5003(CCObject* sender);
    void playLevel5004(CCObject* sender);
};