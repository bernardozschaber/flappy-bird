all: main

obj:
	mkdir -p obj

obj/game_object.o: include/game_object.hpp src/game_object.cpp
	g++ -o obj/game_object.o -c src/game_object.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/game_loop.o: include/game_loop.hpp src/game_loop.cpp
	g++ -o obj/game_loop.o -c src/game_loop.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/bird_object.o: include/bird_object.hpp src/bird_object.cpp
	g++ -o obj/bird_object.o -c src/bird_object.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/pipe_object.o: include/pipe_object.hpp src/pipe_object.cpp
	g++ -o obj/pipe_object.o -c src/pipe_object.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/background_object.o: include/background_object.hpp src/background_object.cpp
	g++ -o obj/background_object.o -c src/background_object.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/main.o: src/main.cpp | obj
	g++ -o obj/main.o -c src/main.cpp -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/main_menu.o: src/main_menu.cpp | obj
	g++ -o obj/main_menu.o -c src/main_menu.cpp -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/ui_object.o: include/ui_object.hpp src/ui_object.cpp
	g++ -o obj/ui_object.o -c src/ui_object.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/text_box.o: include/text_box.hpp src/text_box.cpp
	g++ -o obj/text_box.o -c src/text_box.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/button.o: include/button.hpp src/button.cpp
	g++ -o obj/button.o -c src/button.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/login_screen.o: include/login_screen.hpp src/login_screen.cpp
	g++ -o obj/login_screen.o -c src/login_screen.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/register_screen.o: include/register_screen.hpp src/register_screen.cpp
	g++ -o obj/register_screen.o -c src/register_screen.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/player_list_screen.o: include/player_list_screen.hpp src/player_list_screen.cpp
	g++ -o obj/player_list_screen.o -c src/player_list_screen.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/registration.o: include/registration.hpp src/registration.cpp
	g++ -o obj/registration.o -c src/registration.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

obj/moving_button.o: include/moving_button.hpp src/moving_button.cpp
	g++ -o obj/moving_button.o -c src/moving_button.cpp  -Iinclude -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include

main: obj/main.o obj/game_object.o obj/pipe_object.o obj/bird_object.o obj/background_object.o obj/game_loop.o obj/moving_button.o obj/ui_object.o
	g++ obj/main.o obj/game_object.o obj/pipe_object.o obj/bird_object.o obj/background_object.o obj/game_loop.o obj/moving_button.o obj/ui_object.o -o main `pkg-config --libs allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5`

main_menu: obj/main_menu.o obj/game_object.o obj/pipe_object.o obj/bird_object.o obj/background_object.o obj/ui_object.o obj/text_box.o obj/button.o obj/login_screen.o obj/register_screen.o obj/player_list_screen.o obj/registration.o obj/game_loop.o obj/moving_button.o
	g++ obj/main_menu.o obj/game_object.o obj/pipe_object.o obj/bird_object.o obj/background_object.o obj/ui_object.o obj/text_box.o obj/button.o obj/login_screen.o obj/register_screen.o obj/player_list_screen.o obj/registration.o obj/game_loop.o obj/moving_button.o -o main_menu `pkg-config --libs allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5`
