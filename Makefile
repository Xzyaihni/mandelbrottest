CXX = g++
CXXFLAGS = -IC:/SFML/include -LC:/SFML/lib -DSFML_STATIC
LIBS = -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lfreetype -lopengl32 -lwinmm -lgdi32 -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread

output: mandelbrot.o mandelimg.o mandelpoint.cpp
	$(CXX) $(CXXFLAGS) mandelbrot.o mandelimg.o mandelpoint.cpp -o build/mandelbrot  $(LIBS)

mandelbrot.o: mandelbrot.cpp mandelimg.h mandelpoint.h
	$(CXX) $(CXXFLAGS) -c mandelbrot.cpp mandelimg.cpp mandelpoint.cpp  $(LIBS)
