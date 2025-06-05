ALLEGRO_CFLAGS := $(shell pkg-config --cflags allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5)
ALLEGRO_LIBS := $(shell pkg-config --libs allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5)

CXX := g++
CXXFLAGS := -Iinclude $(ALLEGRO_CFLAGS) -Wall -g

OBJDIR := obj
OBJS := $(OBJDIR)/main.o $(OBJDIR)/game_object.o $(OBJDIR)/pipe_object.o $(OBJDIR)/bird_object.o $(OBJDIR)/background_object.o $(OBJDIR)/scenario.o

all: main

$(OBJDIR)/scenario.o: src/scenario.cpp include/scenario.hpp
	$(CXX) $(CXXFLAGS) -c src/scenario.cpp -o $@

$(OBJDIR)/game_object.o: src/game_object.cpp include/game_object.hpp
	$(CXX) $(CXXFLAGS) -c src/game_object.cpp -o $@

$(OBJDIR)/bird_object.o: src/bird_object.cpp include/bird_object.hpp
	$(CXX) $(CXXFLAGS) -c src/bird_object.cpp -o $@

$(OBJDIR)/pipe_object.o: src/pipe_object.cpp include/pipe_object.hpp
	$(CXX) $(CXXFLAGS) -c src/pipe_object.cpp -o $@

$(OBJDIR)/background_object.o: src/background_object.cpp include/background_object.hpp
	$(CXX) $(CXXFLAGS) -c src/background_object.cpp -o $@

$(OBJDIR)/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o $@

main: $(OBJS)
	$(CXX) $(OBJS) -o main $(ALLEGRO_LIBS)

clean:
	rm -f $(OBJDIR)/*.o main
