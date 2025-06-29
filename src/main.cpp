#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

auto mod = Mod::get();

auto doShipMod = mod->getSettingValue<bool>("enable-shipmod");
auto doRobotMod = mod->getSettingValue<bool>("enable-robotmod");
auto doSwingMod = mod->getSettingValue<bool>("enable-swingmod");

auto swapShipColors = mod->getSettingValue<bool>("swap-shipcolors");
auto swapRobotColors = mod->getSettingValue<bool>("swap-robotcolors");
auto swapSwingColors = mod->getSettingValue<bool>("swap-swingcolors");

auto useCustomShipColors = mod->getSettingValue<bool>("ship-customcolor");
auto useCustomRobotColors = mod->getSettingValue<bool>("robot-customcolor");
auto useCustomSwingColors = mod->getSettingValue<bool>("swing-customcolor");

//particle colors
auto shipMainStartColor = mod->getSettingValue<cocos2d::ccColor4B>("ship-startcolor");
auto shipMainEndColor = mod->getSettingValue<cocos2d::ccColor4B>("ship-endcolor");
auto shipClickStartColor = mod->getSettingValue<cocos2d::ccColor4B>("shipclick-startcolor");
auto shipClickEndColor = mod->getSettingValue<cocos2d::ccColor4B>("shipclick-endcolor");

auto robotStartColor = mod->getSettingValue<cocos2d::ccColor4B>("robot-startcolor");
auto robotEndColor = mod->getSettingValue<cocos2d::ccColor4B>("robot-endcolor");

auto swingStartColor = mod->getSettingValue<cocos2d::ccColor4B>("swing-startcolor");
auto swingEndColor = mod->getSettingValue<cocos2d::ccColor4B>("swing-endcolor");

$on_mod(Loaded){
    listenForSettingChanges("enable-shipmod", [](bool value) {
        doShipMod = value;
    });
    listenForSettingChanges("enable-robotmod", [](bool value) {
        doRobotMod = value;
    });
    listenForSettingChanges("enable-swingmod", [](bool value) {
        doSwingMod = value;
    });
    listenForSettingChanges("swap-shipcolors", [](bool value) {
        swapShipColors = value;
    });
    listenForSettingChanges("swap-robotcolors", [](bool value) {
        swapRobotColors = value;
    });
    listenForSettingChanges("swap-swingcolors", [](bool value) {
        swapSwingColors = value;
    });
    listenForSettingChanges("ship-customcolor", [](bool value) {
        useCustomShipColors = value;
    });
    listenForSettingChanges("robot-customcolor", [](bool value) {
        useCustomRobotColors = value;
    });
    listenForSettingChanges("swing-customcolor", [](bool value) {
        useCustomSwingColors = value;
    });
    listenForSettingChanges("ship-startcolor", [](cocos2d::ccColor4B value) {
        shipMainStartColor = value;
    });
    listenForSettingChanges("ship-endcolor", [](cocos2d::ccColor4B value) {
        shipMainEndColor = value;
    });
    listenForSettingChanges("shipclick-startcolor", [](cocos2d::ccColor4B value) {
        shipClickStartColor = value;
    });
    listenForSettingChanges("shipclick-endcolor", [](cocos2d::ccColor4B value) {
        shipClickEndColor = value;
    });
    listenForSettingChanges("robot-startcolor", [](cocos2d::ccColor4B value) {
        robotStartColor = value;
    });
    listenForSettingChanges("robot-endcolor", [](cocos2d::ccColor4B value) {
        robotEndColor = value;
    });
    listenForSettingChanges("swing-startcolor", [](cocos2d::ccColor4B value) {
        swingStartColor = value;
    });
    listenForSettingChanges("swing-endcolor", [](cocos2d::ccColor4B value) {
        swingEndColor = value;
    });
}

class $modify(PColorsPlayerObject, PlayerObject) {
    struct Fields {
        // ccColor4F for everything
        cocos2d::ccColor3B myColor1 = GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor());
        cocos2d::ccColor3B myColor2 = GameManager::sharedState()->colorForIdx(GameManager::sharedState()->getPlayerColor2());
        cocos2d::ccColor4F primaryColorParticle = cocos2d::ccColor4F(myColor1.r / 255.0f, myColor1.g / 255.0f, myColor1.b / 255.0f, 255.0f);
        cocos2d::ccColor4F secondaryColorParticle = cocos2d::ccColor4F(myColor2.r / 255.0f, myColor2.g / 255.0f, myColor2.b / 255.0f, 255.0f);
        // custom colors now
        cocos2d::ccColor4F mShipStart = cocos2d::ccColor4F(shipMainStartColor.r / 255.0f, shipMainStartColor.g / 255.0f, shipMainStartColor.b / 255.0f, shipMainStartColor.a / 255.0f);
        cocos2d::ccColor4F mShipEnd = cocos2d::ccColor4F(shipMainEndColor.r / 255.0f, shipMainEndColor.g / 255.0f, shipMainEndColor.b / 255.0f, shipMainEndColor.a / 255.0f);
        cocos2d::ccColor4F cShipStart = cocos2d::ccColor4F(shipClickStartColor.r / 255.0f, shipClickStartColor.g / 255.0f, shipClickStartColor.b / 255.0f, shipClickStartColor.a / 255.0f);
        cocos2d::ccColor4F cShipEnd = cocos2d::ccColor4F(shipClickEndColor.r / 255.0f, shipClickEndColor.g / 255.0f, shipClickEndColor.b / 255.0f, shipClickEndColor.a / 255.0f);
        cocos2d::ccColor4F robotStart = cocos2d::ccColor4F(robotStartColor.r / 255.0f, robotStartColor.g / 255.0f, robotStartColor.b / 255.0f, robotStartColor.a / 255.0f);
        cocos2d::ccColor4F robotEnd = cocos2d::ccColor4F(robotEndColor.r / 255.0f, robotEndColor.g / 255.0f, robotEndColor.b / 255.0f, robotEndColor.a / 255.0f);
        cocos2d::ccColor4F swingStart = cocos2d::ccColor4F(swingStartColor.r / 255.0f, swingStartColor.g / 255.0f, swingStartColor.b / 255.0f, swingStartColor.a / 255.0f);
        cocos2d::ccColor4F swingEnd = cocos2d::ccColor4F(swingEndColor.r / 255.0f, swingEndColor.g / 255.0f, swingEndColor.b / 255.0f, swingEndColor.a / 255.0f);
    };
    void update(float p0) {
        PlayerObject::update(p0);

        auto f = m_fields.self();

        if (m_isShip) {
            if (doShipMod) {
                if (!useCustomShipColors) {
                    if (swapShipColors) {
                        m_trailingParticles->m_tStartColor = f->secondaryColorParticle;
                        m_trailingParticles->m_tEndColor = f->secondaryColorParticle;
                        m_shipClickParticles->m_tStartColor = f->primaryColorParticle;
                        m_shipClickParticles->m_tEndColor = f->primaryColorParticle;
                    } else {
                        m_trailingParticles->m_tStartColor = f->primaryColorParticle;
                        m_trailingParticles->m_tEndColor = f->primaryColorParticle;
                        m_shipClickParticles->m_tStartColor = f->secondaryColorParticle;
                        m_shipClickParticles->m_tEndColor = f->secondaryColorParticle;
                    }
                } else {
                    m_trailingParticles->m_tStartColor = f->mShipStart;
                    m_trailingParticles->m_tEndColor = f->mShipEnd;
                    m_shipClickParticles->m_tStartColor = f->cShipStart;
                    m_shipClickParticles->m_tEndColor = f->cShipEnd;
                }
            }

        } else if (m_isRobot) {

            if (doRobotMod) {
                if (!useCustomRobotColors) {
                    if (swapRobotColors) {
                        m_robotBurstParticles->m_tStartColor = f->secondaryColorParticle;
                        m_robotBurstParticles->m_tEndColor = f->primaryColorParticle;
                    } else {
                        m_robotBurstParticles->m_tStartColor = f->primaryColorParticle;
                        m_robotBurstParticles->m_tEndColor = f->secondaryColorParticle;
                    }
                } else {
                    m_robotBurstParticles->m_tStartColor = f->robotStart;
                    m_robotBurstParticles->m_tEndColor = f->robotEnd;
                }
            }

        } else if (m_isSwing) {

            if (doSwingMod) {
                if (!useCustomSwingColors) {
                    if (swapSwingColors) {
                        m_trailingParticles->m_tStartColor = f->secondaryColorParticle;
                        m_trailingParticles->m_tEndColor = f->primaryColorParticle;
                        m_swingBurstParticles1->m_tStartColor = f->secondaryColorParticle;
                        m_swingBurstParticles1->m_tEndColor = f->primaryColorParticle;
                        m_swingBurstParticles2->m_tStartColor = f->secondaryColorParticle;
                        m_swingBurstParticles2->m_tEndColor = f->primaryColorParticle;
                    } else {
                        m_trailingParticles->m_tStartColor = f->primaryColorParticle;
                        m_trailingParticles->m_tEndColor = f->secondaryColorParticle;
                        m_swingBurstParticles1->m_tStartColor = f->primaryColorParticle;
                        m_swingBurstParticles1->m_tEndColor = f->secondaryColorParticle;
                        m_swingBurstParticles2->m_tStartColor = f->primaryColorParticle;
                        m_swingBurstParticles2->m_tEndColor = f->secondaryColorParticle;
                    }
                } else {
                    m_trailingParticles->m_tStartColor = f->swingStart;
                    m_trailingParticles->m_tEndColor = f->swingEnd;
                    m_swingBurstParticles1->m_tStartColor = f->swingStart;
                    m_swingBurstParticles1->m_tEndColor = f->swingEnd;
                    m_swingBurstParticles2->m_tStartColor = f->swingStart;
                    m_swingBurstParticles2->m_tEndColor = f->swingEnd;
                }
            }

        }
    }
};