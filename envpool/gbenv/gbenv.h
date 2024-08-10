#ifndef ENVPOOL_GBENV_GBENV_H_
#define ENVPOOL_GBENV_GBENV_H_


#include "envpool/core/async_envpool.h"
#include "envpool/core/env.h"

namespace gbenv {

class GameBoyEnvFns {
 public:
  static decltype(auto) DefaultConfig() {
    return MakeDict(
        "stack_num"_.Bind(4), "min_frame_skip"_.Bind(0), "max_frame_skip"_.Bind(0),
        "max_episode_steps"_.Bind(200), "noop_max"_.Bind(30),
        "full_action_space"_.Bind(false),
        "rom_path"_.Bind(std::string("FlappyBird.gb")),
        "savestate_path"_.Bind(std::string("")), "task"_.Bind(std::string("")),
        "img_height"_.Bind(84), "img_width"_.Bind(84),
        "repeat_action_probability"_.Bind(0.0f),
        "use_inter_area_resize"_.Bind(true), "gray_scale"_.Bind(true));
  }

  template <typename Config>
  static decltype(auto) StateSpec(const Config& conf) {
    return MakeDict("obs"_.Bind(Spec<uint8_t>(
                        {conf["stack_num"_] * (conf["gray_scale"_] ? 1 : 3),
                         conf["img_height"_], conf["img_width"_]},
                        {0, 255})),
                    "info:lives"_.Bind(Spec<int>({-1})),
                    "info:reward"_.Bind(Spec<float>({-1})),
                    "info:terminated"_.Bind(Spec<int>({-1}, {0, 1})));
  }

  template <typename Config>
  static decltype(auto) ActionSpec(const Config& conf) {
    conf["full_action_space"_]
    ale::ALEInterface env;
    env.loadROM(GetRomPath(conf["base_path"_], conf["task"_]));
    int action_size = conf["full_action_space"_]
                          ? env.getLegalActionSet().size()
                          : env.getMinimalActionSet().size();
    return MakeDict("action"_.Bind(Spec<int>({-1}, {0, action_size - 1})));
  }
};

// this line will concat common config and common state/action spec
using GameBoyEnvSpec = EnvSpec<GameBoyEnvFns>;

// Flappy Bird https://github.com/LaroldsJubilantJunkyard/flappy-bird-gameboy
// score = [c0d8] u8
// alive = [c0dc] if nonzero

}


#endif
