-- Platform Libraries
macOSXLinks = {
    "OpenGL.framework",
    "AppKit.framework",
    "CoreFoundation.framework",
    "CoreGraphics.framework",
    "IOKit.framework",
}
win32Links = {
    "gdi32",
    "OpenGL32"
}

glfw_proj = "ext/glfw-3.3.2"
glew_proj = "ext/glew-2.1.0"
imgui_proj = "ext/imgui-1.77"
glm_proj = "ext/glm-0.9.9"
stb_proj = "ext/stb"
------------------

-- Workspace Setup
workspace "Computer Graphics"
    startproject "CG"
	architecture "x86_64"
    language "c++"
    cppdialect "c++17"

    configurations {
        "Debug",
        "NonDebug",
        "Release"
    }
    -- Configuration Settings
    filter "configurations:Debug"
        defines { "_DEBUG" }
        symbols "On"
        objdir "bin-obj"
        targetdir "bin"
    filter "configurations:NonDebug"
        defines { "NDEBUG" }
        optimize "On"
        objdir "bin-obj"
        targetdir "bin"
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        objdir "bin-obj"
        targetdir "bin"
    filter ""
    
    --
    
-- Project 1
project "CG"
    location "CG"
    kind "ConsoleApp"
    sysincludedirs {
         "%{glfw_proj}/include",
         "%{glew_proj}/include",
         "%{imgui_proj}/include",
         "%{glm_proj}/include",
         "%{stb_proj}/include",
         "%{prj.location}/src",
         "%{prj.location}/src/tests",
    }
    resincludedirs {
        "%{prj.location}/src/data/shaders",
        "%{prj.location}/src/data/textures"
    }
    files {
        "%{prj.location}/**.cpp",
        "%{prj.location}/**.h",
        "%{prj.location}/**.shader",
    }
    if os.ishost("macosx") then
        sysincludedirs {""}
        links {table.unpack(macOSXLinks)}
    end
	if os.ishost("windows") then
		links { table.unpack(win32Links)}
	end
    links {
        "GLFW",
        "GLEW",
        "IMGUI",
        "stb"
    }
--

-- Project 2 - external dependency
project "GLFW"
    location "%{glfw_proj}"
    kind "StaticLib"
    if os.ishost "windows" then
        links {
            table.unpack(win32Links)
    }
    end
    if os.ishost "macosx" then
        links {
            table.unpack(macOSXLinks)
        }
    end
    sysincludedirs {
         "%{prj.location}/include"
    }

    files {
        "%{prj.location}/include/*.h",
        "%{prj.location}/src/internal.h",
        "%{prj.location}/src/mappings.h",
        "%{prj.location}/src/context.c",
        "%{prj.location}/src/init.c",
        "%{prj.location}/src/input.c",
        "%{prj.location}/src/monitor.c",
        "%{prj.location}/src/vulkan.c",
        "%{prj.location}/src/window.c",
        "%{prj.location}/src/osmesa_context.c",
        "%{prj.location}/src/osmesa_context.h"
    }
    if os.ishost("macosx") then
       files {
            "%{prj.location}/src/cocoa_platform.h",
            "%{prj.location}/src/cocoa_joystick.h",
            "%{prj.location}/src/posix_thread.h",
            "%{prj.location}/src/nsgl_context.h",
            "%{prj.location}/src/egl_context.h",
            "%{prj.location}/src/cocoa_init.m",
            "%{prj.location}/src/cocoa_joystick.m",
            "%{prj.location}/src/cocoa_monitor.m",
            "%{prj.location}/src/cocoa_window.m",
            "%{prj.location}/src/cocoa_time.c",
            "%{prj.location}/src/posix_thread.c",
            "%{prj.location}/src/nsgl_context.m",
            "%{prj.location}/src/egl_context.c"
        }
        defines {
            "_GLFW_COCOA"
        }
    end
    if os.ishost("windows") then
        files {
             "%{prj.location}/src/win32_platform.h",
             "%{prj.location}/src/win32_joystick.h",
             "%{prj.location}/src/wgl_context.h",
             "%{prj.location}/src/egl_context.h",
             "%{prj.location}/src/win32_init.c",
             "%{prj.location}/src/win32_joystick.c",
             "%{prj.location}/src/win32_monitor.c",
             "%{prj.location}/src/win32_time.c",
             "%{prj.location}/src/win32_thread.c",
             "%{prj.location}/src/win32_window.c",
             "%{prj.location}/src/wgl_context.c",
             "%{prj.location}/src/egl_context.c",
             "%{prj.location}/src/osmesa_context.c"
        }
        defines {
            "_GLFW_WIN32"
        }
    end
--

-- Project 3 - external as well
project "GLEW"
    location "%{glew_proj}"
    kind "StaticLib"
    sysincludedirs {
         "%{prj.location}/include"
    }
    files {
        "%{prj.location}/include/**.h",
        "%{prj.location}/src/*.c"
    }
    defines {
    "GL_SILENCE_DEPRECATION"
    }
--

-- Project 4 - external
project "IMGUI"
    location "%{imgui_proj}"
    kind "StaticLib"
    sysincludedirs {
        "%{prj.location}/include",
        "%{glfw_proj}/include",
        "%{glew_proj}/include",
    }
    files {
        "%{prj.location}/include/**.h",
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }
--

-- Project 5  - external
project "stb"
    location "%{stb_proj}"
    kind "StaticLib"
    sysincludedirs {
        "%{prj.location}/include"
    }
    files {
        "%{prj.location}/src/*.cpp",
        "%{prj.location}/**.h"
}

---------------------------
