all: main

obj/game_object.o: include/game_object.hpp src/game_object.cpp
	g++ -o obj/game_object.o -c src/game_object.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/bird_object.o: include/bird_object.hpp src/bird_object.cpp
	g++ -o obj/bird_object.o -c src/bird_object.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/pipe_object.o: include/pipe_object.hpp src/pipe_object.cpp
	g++ -o obj/pipe_object.o -c src/pipe_object.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/background_object.o: include/background_object.hpp src/background_object.cpp
	g++ -o obj/background_object.o -c src/background_object.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/main.o: src/main.cpp
	g++ -o obj/main.o -c src/main.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

main: obj/main.o obj/game_object.o obj/pipe_object.o obj/bird_object.o obj/background_object.o
	g++ obj/main.o obj/game_object.o obj/pipe_object.o obj/bird_object.o obj/background_object.o -o main `pkg-config --libs allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5`