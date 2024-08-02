load("@pip_requirements//:requirements.bzl", "requirement")
load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "gbenv_h",
    hdrs = ["gbenv.h"],
    deps = [
        "//envpool/core:async_envpool",
        "@gambatte//:gambatte"
    ],
)

pybind_extension(
    name = "gbenv_envpool",
    srcs = [
        "gbenv.cc",
    ],
    deps = [
        ":gbenv_h",
        "//envpool/core:py_envpool",
    ],
)

py_library(
    name = "gbenv",
    srcs = ["__init__.py"],
    data = [":gbenv_envpool.so"],
    deps = ["//envpool/python:api"],
)

py_library(
    name = "gbenv_registration",
    srcs = ["registration.py"],
    deps = [
        "//envpool:registration",
    ],
)
