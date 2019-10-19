This folder is for the library and include folders for the OpenGL libraries. 
This along with other things like GLFW and SOIL to make things easier.

To set this up in the project go to the properties.
In VC++ Directories->Include directories; set the path to the include folder in this folder
In VC++ Directories->Library Directories; set the path to the Lib folder

And in Linker->Input->Additional Dependencies add these lines to it
opengl32.lib;glfw3.lib;SOIL.lib;