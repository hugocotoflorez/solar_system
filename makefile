filename = ss

compile:
	g++ main.cpp -lglut -lGL -lGLU -o $(filename)

exe: win
win:

	i686-w64-mingw32-g++ main.cpp \
	include/glad/glad.c \
	-Iinclude \
	-Linclude \
	-lGLFW \
	-lGL \
	-lglut32 \
	-lglu32 \
	-o $(filename).exe \
	-static-libstdc++ \
	-static-libgcc \
	# -static \ dont work. Can fail if dont have the dll
	[[ ! -f glut32.dll ]] && ln -s ./include/glut32.dll .

