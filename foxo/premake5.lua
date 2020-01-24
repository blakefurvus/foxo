project "foxo"
    kind "ConsoleApp"
    language "C"

    includedirs { "include" }
    files { "src/**.c" }

    links { "readline" }