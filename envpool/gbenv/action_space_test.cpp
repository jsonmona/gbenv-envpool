#include "action_space.h"

#include <unordered_set>

#include <gtest/gtest.h>


namespace {

using namespace gbenv;

static void test_action(const ActionSpace& space, int action, std::unordered_set<uint8_t>& btns) {
    uint8_t btn = space.from_action(action);
    auto itr = btns.find(btn);
    EXPECT_FALSE(itr != btns.end()) << "Action #" << action << " produced duplicate button of " << static_cast<int>(btn) << space.debug_btn(btn);
    EXPECT_EQ(action, space.to_action(btn)) << "The action produced button: " << space.debug_btn(btn);
    
    if (action == 0) {
        EXPECT_EQ(0, btn) << "Action #0 should be NOOP";
    }
}

// Tests with invalid dpad on
TEST(GbenvActionSpaceTest, DpadInvalid) {
    ActionSpace space(Button::ALL, true);
    std::unordered_set<uint8_t> btns;

    ASSERT_EQ(256, space.actions());

    for (int i = 0; i < space.actions(); i++) {
        test_action(space, i, btns);
    }
}

// Tests with invalid dpad off
TEST(GbenvActionSpaceTest, DpadValid) {
    ActionSpace space(Button::ALL, false);
    std::unordered_set<uint8_t> btns;

    ASSERT_EQ(144, space.actions());

    for (int i = 0; i < space.actions(); i++) {
        test_action(space, i, btns);
    }
}

#if 0
TEST(GbenvActionSpaceTest, DpadPartialUp) {
    ActionSpace space(Button::ALL & (~Button::UP) & (~Button::A), false);
    std::unordered_set<uint8_t> btns;

    ASSERT_EQ(48, space.actions());

    for (int i = 0; i < space.actions(); i++) {
        test_action(space, i, btns);
    }
}

TEST(GbenvActionSpaceTest, DpadPartialLeft) {
    ActionSpace space(Button::DPAD & (~Button::LEFT), false);
    std::unordered_set<uint8_t> btns;

    ASSERT_EQ(6, space.actions());

    for (int i = 0; i < space.actions(); i++) {
        test_action(space, i, btns);
    }
}
#endif

}
