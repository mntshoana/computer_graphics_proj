# Computer Graphics School Project
This is a school assignment which was required in 2018 to showcase the use of modern open GL and c++. I had to render a translating and rotating animation. Another test case I included for bonus points was the solar system (milky way) with 9 planets that rotate around the sun.

Dependencies for this project are:
GLFW, GLEW and IMGUI. 

These included in the configuration (no need to download seperately)

Note:
I used a premake script to generate the xcode project file (which was tested on macOS - not windows, not linux)
Premake folder include premake binaries to run configuration (may possibly may be outdated)
To generate xcode workspace project file run the premake script using: 
````
premake/premake5 xcode4
````
