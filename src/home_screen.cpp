#include "home_screen.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

// CONSTANTES DE PATH
const char * MOUNTAIN_SPRITE_1 = "assets/scenario/mountains_1.png"; // caminho das montanhas (da frente)
const char * MOUNTAIN_SPRITE_2 = "assets/scenario/mountains_2.png"; // caminho das montanhas (do meio)
const char * MOUNTAIN_SPRITE_3 = "assets/scenario/mountains_3.png"; // caminho das montanhas (de trás)
const char * GRASS_SPRITE = "assets/scenario/grama.png";            // caminho da grama
const char * BACKGROUND_SPRITE = "assets/scenario/background.png";  // caminho do background
const char * ACHIEVEMENTS_BUTTON_SPRITE[2] = {"assets/UI/achievements_button.png","assets/UI/achievements_button_pressed.png"}; // caminho do botão de conquistas
const char * SETTINGS_BUTTON_SPRITE[2] = {"assets/UI/settings_button.png","assets/UI/settings_button_pressed.png"};             // caminho do botão de configurações
const char * TITLE_SPRITE = {"assets/UI/title_text.png"};           // caminho para o título do jogo

Home_Screen::Home_Screen() {

}

Home_Screen::~Home_Screen() {

}