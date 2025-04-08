#include <Geode/Geode.hpp>
#include "CustomTowerLayer.hpp"
#include "Geode/utils/SeedValue.hpp"

using namespace geode::prelude;

void CustomTowerLayer::keyBackClicked() {
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
}

void CustomTowerLayer::backWrapper(CCObject* sender) {
    CustomTowerLayer::keyBackClicked();
}

CCScene* CustomTowerLayer::scene() {
    auto scene = CCScene::create();
    scene->addChild(CustomTowerLayer::create());
    return scene;
}

CustomTowerLayer* CustomTowerLayer::create() {
    CustomTowerLayer* ret = new CustomTowerLayer();
    if (ret && ret->init(false, true)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool CustomTowerLayer::init(bool returning, bool nextFloorLocked) {
    if (!LevelAreaInnerLayer::init(false)) {
        return false;
    }

    setKeypadEnabled(true);

    // Back button fix

    if (auto menu = this->getChildByID("back-menu")) {
        CCMenuItemSpriteExtra* btn = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("back-button"));
        btn->m_pfnSelector = menu_selector(CustomTowerLayer::backWrapper);
    }

    // Disable 2nd floor button

    if (nextFloorLocked) {
        if (auto menu = this->getChildByID("main-node")->getChildByID("main-menu")) {
			auto secondFloorBtnOld = menu->getChildByID("second-floor-button");
			auto secondFloorBtn = menu->getChildByID("second-floor-button-enabled");
			secondFloorBtnOld->setVisible(true);
			secondFloorBtn->setVisible(false);
		}
    }

    // Custom levels

    if (auto menu = this->getChildByID("main-node")->getChildByID("main-menu")) {
        CCMenuItemSpriteExtra* level5001 = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("level-5001-button"));
        level5001->setID("level-5005-button");
        level5001->setTag(5005);
        level5001->m_pfnSelector = menu_selector(CustomTowerLayer::onDoor);

        CCMenuItemSpriteExtra* level5002 = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("level-5002-button"));
        level5002->setID("level-5006-button");
        level5002->setTag(5006);
        level5002->m_pfnSelector = menu_selector(CustomTowerLayer::onDoor);

        CCMenuItemSpriteExtra* level5003 = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("level-5003-button"));
        level5003->setID("level-5007-button");
        level5003->setTag(5007);
        level5003->m_pfnSelector = menu_selector(CustomTowerLayer::onDoor);

        CCMenuItemSpriteExtra* level5004 = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("level-5004-button"));
        level5004->setID("level-5008-button");
        level5004->setTag(5008);
        level5004->m_pfnSelector = menu_selector(CustomTowerLayer::onDoor);
    }

    return true;
}

struct LevelData {
    int levelID;
    std::string name;
    int songID;
    int moons;
};

static const std::unordered_map<int, LevelData> levelMap = {
    {5005, {5005, "The Foolish Tower", 10003039, 0}},
    {5006, {5006, "The Deep Sewers", 10003040, 0}},
    {5007, {5007, "The Lost Cellar", 10002875, 0}},
    {5008, {5008, "The Sneaky Hollow", 10000749, 0}},
};

void CustomTowerLayer::onDoor(CCObject* sender) {
    auto it = levelMap.find(sender->getTag());
    if (it == levelMap.end()) {
        log::error("Level ID not found: {}", sender->getTag());
        return;
    }

    const auto& data = it->second;
    auto level = GJGameLevel::create();
    level->m_levelID = data.levelID;
    level->m_levelType = GJLevelType::Saved;
    level->m_autoLevel = false;
    level->m_stars = data.moons;
    level->m_levelName = data.name;
    level->m_songID = data.songID;

    const auto& levelPath = Mod::get()->getResourcesDir() / (std::to_string(sender->getTag()) + ".txt");
    if (!std::filesystem::exists(levelPath)) {
        log::error("Level file does not exist: {}", levelPath);
        return;
    }

    std::ifstream file(levelPath);
    if (!file) {
        log::error("Failed to open level file: {}", levelPath);
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    level->m_levelString = buffer.str();

    FMODAudioEngine::get()->playEffect("playSound_01.ogg", 1.f, 1.f, 0.5f);

    auto scene = CCTransitionFade::create(0.5f, PlayLayer::scene(level, false, false));
    CCDirector::sharedDirector()->pushScene(scene);
}

// void CustomTowerLayer::playLevel5005(CCObject*) {
//     playTowerLevel(5005);
// }

// void CustomTowerLayer::playLevel5006(CCObject*) {
//     playTowerLevel(5006);
// }

// void CustomTowerLayer::playLevel5007(CCObject*) {
//     playTowerLevel(5007);
// }

// void CustomTowerLayer::playLevel5008(CCObject*) {
//     playTowerLevel(5008);
// }