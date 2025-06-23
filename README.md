# "Flappy Birdo" C++ com Allegro

## Descrição do Problema
O objetivo deste projeto é implementar uma versão simplificada do jogo **Flappy Bird**, aliando:

1. **Padrão Orientado a Objetos** em C++, com hierarquias de classes para tela de jogo e UI.  
2. **Interface gráfica** de menu (login, cadastro, listagem e remoção de jogadores) usando Allegro 5.  
3. **Persistência** de cadastro de jogadores em arquivo de texto, com armazenamento de nome, senha, recorde, partidas jogadas e *conquistas*.
4. **Integração** consistente entre a manipulação dos arquivos e a execução do jogo em si.
5. **Execução robusta** do jogo, sem bugs, usando Allegro 5.
6. **Configuração personalizável** das variáveis do jogo.

O sistema deve permitir:  
- **Login/Logout** de usuários.  
- **Registro** de novos jogadores.  
- **Listagem paginada** de todos os jogadores, com destaque de recordistas e navegação entre páginas.  
- **Remoção** de jogadores, com confirmação de senha.  
- **Execução do jogo** propriamente dito (Flappy Bird).

---

## Visão Geral da Solução
### Principais Componentes
#### Menu Principal / Registro:
- **`ui_object`**  
  Classe abstrata genêrica para definir objetos de interface.  
- **`text_box`** e **`button`**  
  Herdeiros de `ui_object`, tratam entrada de texto e cliques, com lógica de foco, máscara de senha e sons.  
- **Telas (`*_screen`)**  
  - **`login_screen`**: login + botões → registrar, listar, remover.  
  - **`register_screen`**: nome + senha + confirm, botões → registrar, cancelar.  
  - **`player_list_screen`**: mostra 14 jogadores/página, botões Next/Back (ativados/desativados) + voltar.  
  - **`remove_user_screen`**: *fase 1:* usuário + confirm, botões → *fase 2:* remover, confirmar, cancelar.  
- **`menu_audio`**  
  Gerencia quatro bitmaps (on/off + pressed) e controla áudio de UI do menu.
- **`registration`**  
  Lê/grava arquivo `.txt` com métodos para
- **`menu`**  
  Encapsula `enum` de telas, instancia objetos de UI e faz mudança de estado.  
#### Jogo
-
  

---

## Principais Dificuldades Encontradas

1. **Persistência em Arquivo**  
   Manter `std::fstream` sem corromper dados e tratar erros de I/O.  
2. **Testabilidade**  
    Conseguir simular eventos do Allegro sem uma interface gráfica "real".
3. **Paginação da tela de listagem**
    Criar uma lógica que fosse capaz de listar todos os jogadores considerando um espaço finito da tela 800x600 disponível.
---

## Extras Implementados

- **Melhoria da parte gráfica:** Sprites personalizados para botões e objetos do jogo.
- **Sistema de conquistas:** Conquistas que consideram dados persistentes entre execuções do programa.
- **Configuração personalizada com "sliders":** Possibilidade de alterar variáveis do jogo com interface amigável com "sliders".

---

## Como Compilar e Executar

1. **Pré-requisitos**  
   - Allegro 5 (+ addons audio, image, ttf, primitives, acodec)  
   - g++ (C++17) + pkg-config  
2. **Compilar**  
   ```sh
   make
    ```
    → gera `main `(jogo) e arquivos de teste(`testregistration`,`test_main_menu`)
3. **Executar**
     ```sh
     cd bin
     ./main
     ```
