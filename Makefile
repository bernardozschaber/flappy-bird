# -------------------------------------------------------------------------
# 1) Variáveis de Ambiente e Ferramentas
# -------------------------------------------------------------------------
CXX         := g++
INC_DIR     ?= include
CXXFLAGS    := -std=c++17
INCLUDES    := -I$(INC_DIR)
ALLEGRO_INC := -I/opt/homebrew/Cellar/allegro/5.2.10.1_1/include
PKG_LIBS    := `pkg-config --libs allegro-5 allegro_main-5 allegro_audio-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_acodec-5 allegro_ttf-5`

# -------------------------------------------------------------------------
# 2) Diretórios
# -------------------------------------------------------------------------
SRC_DIR     := src
INC_DIR     := include
OBJ_DIR     := obj
BIN_DIR     := bin
TEST_DIR    := tests

# -------------------------------------------------------------------------
# 3) Fontes e Objetos
# -------------------------------------------------------------------------
# 3.1) Núcleo do jogo
GAME_SRCS   := \
    game_object.cpp \
    game_loop.cpp \
    bird_object.cpp \
    pipe_object.cpp \
    ui_object.cpp \
    background_object.cpp \
    moving_button.cpp \
    image.cpp \
    score.cpp \
    home_screen.cpp \
    achievements_screen.cpp \
    settings_screen.cpp \
    slider.cpp

MAIN_SCR := main.cpp

MAIN_OBJ := $(addprefix $(OBJ_DIR)/, $(MAIN_SCR:.cpp=.o))  

GAME_OBJS   := $(addprefix $(OBJ_DIR)/, $(GAME_SRCS:.cpp=.o))

# 3.2) Menu principal
MENU_SRCS   := \
    menu.cpp \
    ui_object.cpp \
    text_box.cpp \
    button.cpp \
    menu_audio.cpp \
    login_screen.cpp \
    register_screen.cpp \
    remove_user_screen.cpp \
    player_list_screen.cpp \
    registration.cpp

MAIN_MENU_SCR := main_menu.cpp

MAIN_MENU_OBJ := $(addprefix $(OBJ_DIR)/, $(MAIN_MENU_SCR:.cpp=.o))  

MENU_OBJS   := $(addprefix $(OBJ_DIR)/, $(MENU_SRCS:.cpp=.o))

# 3.3) Testes
TESTREG_SRC := $(TEST_DIR)/testregistration.cpp
TESTMM_SRC  := $(TEST_DIR)/test_main_menu.cpp

TESTREG_OBJ := $(OBJ_DIR)/testregistration.o
TESTMM_OBJ  := $(OBJ_DIR)/test_main_menu.o

# -------------------------------------------------------------------------
# 4) Alvos Principais
# -------------------------------------------------------------------------
.PHONY: all clean dirs

all: dirs \
    $(BIN_DIR)/main \
    $(BIN_DIR)/main_menu \
    $(BIN_DIR)/testregistration \
    $(BIN_DIR)/test_main_menu

# -------------------------------------------------------------------------
# 5) Criação de Diretórios
# -------------------------------------------------------------------------
dirs:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
# -------------------------------------------------------------------------
# 6) Regras de Compilação Genéricas (.cpp → .o)
# -------------------------------------------------------------------------
# -MMD: gera .d de dependências, -MP: phony targets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | dirs
	$(CXX) $(CXXFLAGS) $(ALLEGRO_INC) $(INCLUDES) -MMD -MP -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | dirs
	$(CXX) $(CXXFLAGS) $(ALLEGRO_INC) $(INCLUDES) -MMD -MP -c $< -o $@

# -------------------------------------------------------------------------
# 7) Linkagem de Binários
# -------------------------------------------------------------------------
# 7.1) Executável Principal do Jogo
$(BIN_DIR)/main: $(MAIN_OBJ) $(GAME_OBJS)
	$(CXX) $^ -o $@ $(PKG_LIBS)

# 7.2) Executável do Menu Principal
$(BIN_DIR)/main_menu: $(MAIN_MENU_OBJ) $(MENU_OBJS)
	$(CXX) $^ -o $@ $(PKG_LIBS)

# 7.3) Teste da Classe registration
$(BIN_DIR)/testregistration: $(TESTREG_OBJ) $(OBJ_DIR)/registration.o
	$(CXX) $^ -o $@ $(PKG_LIBS)

# 7.4) Teste do Menu Principal
$(BIN_DIR)/test_main_menu: $(TESTMM_OBJ) $(MENU_OBJS)
	$(CXX) $^ -o $@ $(PKG_LIBS)

# -------------------------------------------------------------------------
# 8) Inclusão Automática de Dependências
# -------------------------------------------------------------------------
-include $(OBJ_DIR)/*.d

# -------------------------------------------------------------------------
# 9) Limpeza
# -------------------------------------------------------------------------
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

