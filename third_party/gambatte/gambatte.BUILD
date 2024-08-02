cc_library(
    name = "gambatte",
    srcs = glob(["common/**/*.cpp", "libgambatte/src/*.cpp", "libgambatte/src/mem/*.cpp", "libgambatte/src/sound/*.cpp", "libgambatte/video/*.cpp"]),
    hdrs = glob(["common/**/*.h", "libgambatte/include/*.h", "libgambatte/src/**/*.h"]),
    includes = [
        "common",
        "libgambatte/include",
        "libgambatte/src",
    ],
    defines = [
        "REVISION=-1",
        "HAVE_STDINT_H",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)
