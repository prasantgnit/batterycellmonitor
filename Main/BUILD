

cc_library(
    name = "cell_",
    srcs = ["cellApplication.cpp"],
    #hdrs = [
     #   "//Cell:cell.hpp",
      #  "//Cell:cellConfig.hpp",
       # "//Cell:ntcRestance.hpp"],
    deps = ["//Logger:logger",
            "//Com:communication",
            "//InterfaceType:interface",
            "//Cell:cell"],
    visibility = ["//visibility:public"],  # Make it visible for other targets
)


cc_library(
    name = "bms_",
    srcs = ["bmsApplication.cpp"],
    deps = ["//Logger:logger",
            "//Com:communication",
            "//InterfaceType:interface",
            "//BMS:bms"],
    visibility = ["//visibility:public"],  # Make it visible for other targets
)

cc_binary(
    name = "bmstest",
    deps = [":bms_"],
)

cc_binary(
    name = "celltest",
    deps = [":cell_"],
)

