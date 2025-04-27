

cc_library(
    name = "cell",
    srcs = ["main.cpp"],
    hdrs = [
        "cell.hpp",
        "cellConfig.hpp",
        "ntcRestance.hpp"],
    deps = ["//Logger:logger",
            "//Com:communication",
            "//InterfaceType:interface"],
    visibility = ["//visibility:public"],  # Make it visible for other targets
)

cc_binary(
    name = "celltest",
    deps = [":cell"],
)

