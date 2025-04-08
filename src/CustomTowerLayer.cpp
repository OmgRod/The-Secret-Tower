#include <Geode/Geode.hpp>
#include "CustomTowerLayer.hpp"

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
        level5001->m_pfnSelector = menu_selector(CustomTowerLayer::playLevel5001);

        CCMenuItemSpriteExtra* level5002 = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("level-5002-button"));
        level5002->m_pfnSelector = menu_selector(CustomTowerLayer::playLevel5002);

        CCMenuItemSpriteExtra* level5003 = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("level-5003-button"));
        level5003->m_pfnSelector = menu_selector(CustomTowerLayer::playLevel5003);

        CCMenuItemSpriteExtra* level5004 = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("level-5004-button"));
        level5004->m_pfnSelector = menu_selector(CustomTowerLayer::playLevel5004);
    }

    return true;
}

void CustomTowerLayer::playLevel5001(CCObject* sender) {
    auto level = GJGameLevel::create();
    level->m_levelID = 5005;
    level->m_levelName = "The Foolish Tower";
    level->m_songID = 10003039;

    const auto& levelPath = Mod::get()->getResourcesDir() / "5005.txt";
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

    auto scene = CCTransitionFade::create(0.5f, PlayLayer::scene(level, false, false));
    CCDirector::sharedDirector()->pushScene(scene);
}

void CustomTowerLayer::playLevel5002(CCObject* sender) {
    auto level = GJGameLevel::create();
    level->m_levelID = 5006;
    level->m_levelName = "The Deep Sewers";
    level->m_songID = 10003040;

    const auto& levelPath = Mod::get()->getResourcesDir() / "5006.txt";
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

    auto scene = CCTransitionFade::create(0.5f, PlayLayer::scene(level, false, false));
    CCDirector::sharedDirector()->pushScene(scene);
}

void CustomTowerLayer::playLevel5003(CCObject* sender) {
    auto level = GJGameLevel::create();
    level->m_levelID = 5007;
    level->m_levelName = "The Lost Cellar";
    level->m_songID = 10002875;

    const auto& levelPath = Mod::get()->getResourcesDir() / "5007.txt";
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

    auto scene = CCTransitionFade::create(0.5f, PlayLayer::scene(level, false, false));
    CCDirector::sharedDirector()->pushScene(scene);
}

void CustomTowerLayer::playLevel5004(CCObject* sender) {
    auto level = GJGameLevel::create();
    level->m_levelID = 5008;
    level->m_levelName = "The Sneaky Hollow";
    level->m_songID = 10000749;

    const auto& levelPath = Mod::get()->getResourcesDir() / "5008.txt";
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

    auto scene = CCTransitionFade::create(0.5f, PlayLayer::scene(level, false, false));
    CCDirector::sharedDirector()->pushScene(scene);
}