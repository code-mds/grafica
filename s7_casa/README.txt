Autore: Massimo De Santi
Corso: M-I5070P - Grafica PAP 2020
Ambiente: 
- Windows 10
- CLion 2019.3.4
- MinGW 64 (x86_64-8.1.0-posix-seh-rt_v6-rev0)
----------------------------------------------
Serie: 7
----------------------------------------------
ATTENZIONE: Nel file CMakeLists.txt è definito il percorso di freeglut e glew
	    Nel mio caso C:/SUPSI/freeglut e C:/SUPSI/glew-2.1.0
	    Modificare il percorso per puntare al path corretto

Pacchetto:
- s7_casa\draw_utils.h
- s7_casa\draw_utils.cpp
- s7_casa\house.h
- s7_casa\house.cpp
- s7_casa\camera.h
- s7_casa\camera.cpp
- s7_casa\vertex.h
- s7_casa\vertex.cpp
- s7_casa\main.h
- s7_casa\main.cpp
- bin\s7_casa.exe

Funzioni:
- Show/Hide Axes (x,X keys / Right Click menu)
- Show/Hide Wireframe (w,W keys / Right Click menu)
- Change Color (c,C / Right Click menu)
- Reset (F12 / Right Click menu)

- House Translate X axis (F1/F2 keys)
- House Translate Y axis (F3/F4 keys)
- House Translate Z axis (F5/F6 keys)

- Auto Rotate House (r,R key / Right Click menu)
- Stop Rotate House (s,S key / Right Click menu)
- Open/Close Door (d,D key / Right Click menu)

- Automatic Draw flag animation
- Show/Hide Wind (Right Click menu)

- Orthographic projection (a,A key / Right Click menu)
- Perspective projection (p,P key / Right Click menu)

- Camera (arrows, PG UP, PG DOWN)
- Check House in Viewing Volume (blocca traslazione o movimento camera se fuori da confini del volume)