#include <Geode/Geode.hpp>
#include <Geode/modify/LevelAreaInnerLayer.hpp>
#include "CustomTowerLayer.hpp"

using namespace geode::prelude;

class $modify(MyLevelAreaInnerLayer, LevelAreaInnerLayer) {
	bool init(bool returning) {
		if (!LevelAreaInnerLayer::init(returning)) {
			return false;
		}

		if (auto menu = this->getChildByID("main-node")->getChildByID("main-menu")) {
			auto secondFloorBtnOld = menu->getChildByID("second-floor-button");
			secondFloorBtnOld->setVisible(false);

			auto secondFloorBtn = CCMenuItemSpriteExtra::create(
				CCSprite::create("floor2Btn.png"_spr),
				this,
				menu_selector(MyLevelAreaInnerLayer::onNextFloor)
			);
			secondFloorBtn->setPosition(secondFloorBtnOld->getPosition());
			secondFloorBtn->setID("second-floor-button-enabled");

			menu->addChild(secondFloorBtn);
		}

		return true;
	}

	void onNextFloor(CCObject* sender) {
		auto scenePrev = CCTransitionFade::create(0.5f, CustomTowerLayer::scene());
        CCDirector::sharedDirector()->pushScene(scenePrev);
	}
};