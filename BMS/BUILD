

cc_library(
    name = "bms",
    srcs = ["main.cpp"],
    hdrs = ["bms.hpp"],
    deps = ["//Logger:logger",
            "//Com:communication",
            "//InterfaceType:interface"],
    visibility = ["//visibility:public"],  # Make it visible for other targets
)

cc_binary(
    name = "bmstest",
    deps = [":bms"],
)

