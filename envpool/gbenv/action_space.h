#ifndef ENVPOOL_GBENV_GAMEBOY_H_
#define ENVPOOL_GBENV_GAMEBOY_H_


#include <cstdint>
#include <string>

#include <gambatte.h>

namespace gbenv {

namespace Button {

/// @brief Copied from gambatte inputspec.h
enum Button : uint8_t {
    A      = 0x01,
    B      = 0x02,
    SELECT = 0x04,
    START  = 0x08,
    RIGHT  = 0x10,
    LEFT   = 0x20,
    UP     = 0x40,
    DOWN   = 0x80,
    ALL    = 0xFF,
    DPAD   = 0xF0,
};

}

class ActionSpace {
public:
    ActionSpace(uint8_t button_mask, bool allow_invalid_dpad);

    int actions() const { return m_actions; }
    uint8_t from_action(int action) const;
    int to_action(uint8_t btn) const;

    std::string debug_btn(uint8_t btn) const;

private:
    uint8_t m_button_mask;
    uint8_t m_effective_mask;
    bool m_allow_invalid_dpad;
    int m_buttons;
    int m_actions;
};

}


#endif
