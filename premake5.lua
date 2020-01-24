workspace "foxo"
    configurations {"debug", "release"}
    toolset "clang"

    BASE_DIR = path.getabsolute(".")
    targetdir (BASE_DIR .. "/bin")
    objdir (BASE_DIR .. "/bin/obj")

    filter "configurations:debug"
        symbols "on"
    
    filter "configurations:release"
        defines { "NDEBUG" }
        optimize "on"

include "foxo"