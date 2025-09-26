cc_library(
    name = "base_class",
    hdrs = ["include/BaseClass.h"],
    srcs = ["src/BaseClass.cpp"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "sub_class",
    hdrs = ["include/SubClass.h"],
    srcs = ["src/SubClass.cpp"],
    strip_include_prefix = "include",
    deps = [":base_class"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "demo",
    srcs = ["src/main.cpp"],
    deps = [":sub_class"],
)