Autore: Massimo De Santi
Corso: M-I5070P - Grafica PAP 2020
Ambiente: 
- Windows 10
- CLion 2019.3.4
- MinGW 64 (x86_64-8.1.0-posix-seh-rt_v6-rev0)
----------------------------------------------
ATTENZIONE: Nel file CMakeLists.txt è definito il percorso di freeglut e glew
	    Nel mio caso C:/SUPSI/freeglut e C:/SUPSI/glew-2.1.0
	    Modificare il percorso per puntare al path corretto

Pacchetto:
- src\camera.h
- src\camera.cpp
- src\house.h
- src\house.cpp
- src\main.h
- src\main.cpp
- src\RgbImage.h
- src\RgbImage.cpp
- src\shaders_loader.h
- src\shaders_loader.cpp
- src\solid.h
- src\solid.cpp
- src\Texture.h
- src\Texture.cpp
- src\vertex.h
- src\vertex.cpp

- images\roof_texture.bmp
- images\wall_texture.bmp
- images\wood_texture.bmp
- images\flag_texture.bmp

- shaders\shader.frag
- shaders\shader.vert

- bin\s13_casa.exe

Funzioni:

*** NEW ***
- 3 Textures: Wall, Door, Roof, Flag
- Il programma cerca le seguenti immagini nella sottocartella images:
	- images\roof_texture.bmp
	- images\wall_texture.bmp
	- images\wood_texture.bmp
	- images\flag_texture.bmp

*** NEW ***
- Shader, indici EBO, glDrawElements

*** OLD ***
- Export as bmp (Right Click menu) salva framebuffer in "capture.bmp"
- Reset (F12 / Right Click menu)

- House Translate X axis (F1/F2 keys)
- House Translate Y axis (F3/F4 keys)
- House Translate Z axis (F5/F6 keys)

- Auto Rotate House (r,R key / Right Click menu)
- Stop Rotate House (s,S key / Right Click menu)
- Open/Close Door (d,D key / Right Click menu)

- Automatic Draw flag animation
- Camera (arrows, PG UP, PG DOWN)
