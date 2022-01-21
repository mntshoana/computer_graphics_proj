# Computer Graphics School Project
This is a school assignment which was required in 2018 to showcase the use of modern open GL and c++. I had to render a translating and rotating animation. Another test case I inclded for bonus points was the solar system (milky way) with 9 planets that rotate around the sun.

Dependencies include GLFW, GLEW and IMGUI. This are included in the configuration.

Note A premake script was used to generate an xcode project file (which has only been tested on macOS - not on windows or linux)
Premake binaries are include under the premake folder (possibly may be outdated)
To generate xcode workspace project file run the premake script using: 
````
premake/premake5 xcode4
````
