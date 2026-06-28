#include <Geode/Geode.hpp>
#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    struct Fields {
        float m_timer = 0.0f;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        m_fields->m_timer = 0.0f;
        return true;
    }

    void applyEnterEffect(GameObject* object, int enterType, bool isRight) {
        PlayLayer::applyEnterEffect(object, enterType, isRight);
        
        if (Mod::get()->getSettingValue<bool>("enabled") && Mod::get()->getSettingValue<std::string>("mode") == "portal") {
            this->randomizeIcons();
        }
    }

    void postUpdate(float dt) {
        PlayLayer::postUpdate(dt);
        
        if (Mod::get()->getSettingValue<bool>("enabled") && Mod::get()->getSettingValue<std::string>("mode") == "time") {
            m_fields->m_timer += dt;
            auto interval = Mod::get()->getSettingValue<int64_t>("interval");
            
            if (m_fields->m_timer >= static_cast<float>(interval)) {
                m_fields->m_timer = 0.0f;
                this->randomizeIcons();
            }
        }
    }

    void randomizeIcons() {
        IconRandomizer::randomizeAll(RandomizeAllType::Icons, false);
        
        if (Mod::get()->getSettingValue<bool>("change-colors")) {
            IconRandomizer::randomizeAll(RandomizeAllType::Colors, false);
        }
    }
};
