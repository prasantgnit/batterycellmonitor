

cc_library(
    name = "interface",
    srcs = ["main.cpp"],
    hdrs = [
        "cellMonitorMsg.hpp",
        "messageType.hpp"],
    deps = ["//Logger:logger"],
    visibility = ["//visibility:public"],  # Make it visible for other targets
)

cc_binary(
    name = "intnew",
    deps = [":interface"],
)

