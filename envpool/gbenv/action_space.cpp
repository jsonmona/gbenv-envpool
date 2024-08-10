#include "action_space.h"

#include <bitset>
#include <sstream>

using namespace gbenv;

ActionSpace::ActionSpace(const uint8_t button_mask, const bool allow_invalid_dpad) : m_button_mask(button_mask), m_allow_invalid_dpad(allow_invalid_dpad) {
    m_effective_mask = button_mask;

    if (!allow_invalid_dpad)
        m_effective_mask &= ~Button::DPAD;

    m_buttons = std::bitset<8>(m_effective_mask).count();
    m_actions = 1 << m_buttons;

    // Calculate action count and return

    if (allow_invalid_dpad) {
        return;
    }

    if ((button_mask & Button::RIGHT) && (button_mask & Button::LEFT)) {
        m_actions *= 3;
    } else if (button_mask & Button::RIGHT) {
        m_actions *= 2;
    } else if (button_mask & Button::LEFT) {
        m_actions *= 2;
    }

    if ((button_mask & Button::UP) && (button_mask & Button::DOWN)) {
        m_actions *= 3;
    } else if (button_mask & Button::UP) {
        m_actions *= 2;
    } else if (button_mask & Button::DOWN) {
        m_actions *= 2;
    }
}

uint8_t ActionSpace::from_action(int action_) const {
    unsigned action = action_;
    uint8_t out = 0;

    for (int i = 0; i < 8; i++) {
        if (!(m_effective_mask & (1 << i)))
            continue;
        
        if (action & 1)
            out |= 1 << i;
        action >>= 1;
    }

    if (action == 0 || true)
        return out;

    // Now only dpad should be left, and allow_invalid_dpad must be false

    if (!m_allow_invalid_dpad) {
        // short curcuit on error (maybe some logging?)
        return out;
    }

    if ((m_button_mask & Button::RIGHT) && (m_button_mask & Button::LEFT)) {
        unsigned extracted = action % 3;
        action /= 3;
        out |= extracted * Button::RIGHT;
    } else if (m_button_mask & Button::RIGHT) {
        if (action & 1)
            out |= Button::RIGHT;
        action >>= 1;
    } else if (m_button_mask & Button::LEFT) {
        if (action & 1)
            out |= Button::LEFT;
        action >>= 1;
    }

    if ((m_button_mask & Button::UP) && (m_button_mask & Button::DOWN)) {
        unsigned extracted = action % 3;
        action /= 3;
        out |= extracted * Button::UP;
    } else if (m_button_mask & Button::UP) {
        if (action & 1)
            out |= Button::UP;
        action >>= 1;
    } else if (m_button_mask & Button::DOWN) {
        if (action & 1)
            out |= Button::DOWN;
        action >>= 1;
    }

    // maybe some logging on error (action != 0)

    return out;
}

int ActionSpace::to_action(uint8_t btn) const {
    unsigned action = 0;

    if (!m_allow_invalid_dpad) {
        if ((m_button_mask & Button::UP) && (m_button_mask & Button::DOWN)) {
            if (btn & Button::UP)
                action += 1;
            else if (btn & Button::DOWN)
                action += 2;
            action *= 3;
        } else if (m_button_mask & Button::UP) {
            if (btn & Button::UP)
                action += 1;
            action *= 2;
        } else if (m_button_mask & Button::DOWN) {
            if (btn & Button::DOWN)
                action += 1;
            action *= 2;
        }

        if ((m_button_mask & Button::RIGHT) && (m_button_mask & Button::LEFT)) {
            if (btn & Button::RIGHT)
                action += 1;
            else if (btn & Button::LEFT)
                action += 2;
            action *= 3;
        } else if (m_button_mask & Button::RIGHT) {
            if (btn & Button::RIGHT)
                action += 1;
            action *= 2;
        } else if (m_button_mask & Button::LEFT) {
            if (btn & Button::LEFT)
                action += 1;
            action *= 2;
        }
    }

    for (int i = 7; i >= 0; i--) {
        if (!(m_effective_mask & (1 << i)))
            continue;

        if (btn & (1 << i))
            action |= 1;
        
        if (i != 0)
            action <<= 1;
    }

    return action;
}

std::string ActionSpace::debug_btn(uint8_t btn) const {
    std::ostringstream out;

    if (btn & Button::A)
        out << "|A";
    if (btn & Button::B)
        out << "|B";
    if (btn & Button::SELECT)
        out << "|SELECT";
    if (btn & Button::START)
        out << "|START";
    if (btn & Button::RIGHT)
        out << "|RIGHT";
    if (btn & Button::LEFT)
        out << "|LEFT";
    if (btn & Button::UP)
        out << "|UP";
    if (btn & Button::DOWN)
        out << "|DOWN";
    
    if (btn != 0)
        out << '|';
    else
        out << "(EMPTY)";
    
    return out.str();
}
