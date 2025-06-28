NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -g
INCLUDES = -I headers
LIBS = -L lib
LDLIBS = -lmlx -lX11 -lXext -lm -ldl -lpthread
SRCS = $(shell find src -name "**.c")
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
MAPS = $(wildcard maps/*.cub)
UNAME_S = $(shell uname -s)
RAND=$(shell echo $$RANDOM)
FT_AUDIO_DIR = src/ft_audio

check_flag = $(shell $(CC) $(1) -E -c /dev/null -o /dev/null 2>/dev/null && echo 1 || echo 0)

HAS_SDL2_PKG = $(shell pkg-config --exists sdl2 2>/dev/null && echo 1 || echo 0)
ifeq ($(HAS_SDL2_PKG),1)
	SDL2_CFLAGS = $(shell pkg-config --cflags sdl2)
	SDL2_LIBS = $(shell pkg-config --libs sdl2)
	USE_SYSTEM_SDL2 = 1
else
	ifeq ($(UNAME_S),Darwin)
		HAS_BREW_SDL2 = $(shell brew --prefix sdl2 >/dev/null 2>&1 && echo 1 || echo 0)
		ifeq ($(HAS_BREW_SDL2),1)
			SDL2_PREFIX = $(shell brew --prefix sdl2)
			SDL2_CFLAGS = -I$(SDL2_PREFIX)/include
			SDL2_LIBS = -L$(SDL2_PREFIX)/lib -lSDL2
			USE_SYSTEM_SDL2 = 1
		else
			USE_SYSTEM_SDL2 = 0
		endif
	else
		USE_SYSTEM_SDL2 = 0
	endif
endif
ifeq ($(UNAME_S),Darwin)
	LIBS += -L /opt/X11/lib
	INCLUDES += -I /opt/X11/include
	LDLIBS += -framework OpenGL
	LDLIBS += -framework AppKit
	LDLIBS += -framework CoreAudio
	LDLIBS += -framework AudioToolbox
	LDLIBS += -framework CoreHaptics
	LDLIBS += -framework CoreVideo
	LDLIBS += -framework GameController
	LDLIBS += -framework IOKit
	LDLIBS += -framework ForceFeedback
	LDLIBS += -framework CoreFoundation
	LDLIBS += -framework Cocoa
	LDLIBS += -framework Carbon 
	LDLIBS += -framework Metal 
else
	ifeq ($(shell $(CC) --version | grep -i clang > /dev/null && echo clang),clang)
    	CFLAGS += -Wno-unknown-warning-option
	else
    	CFLAGS += -Wno-stringop-overflow
	endif
endif

ifeq ($(USE_SYSTEM_SDL2),1)
	INCLUDES += $(SDL2_CFLAGS)
	LDLIBS += $(SDL2_LIBS)
	SDL2_TARGET = 
else
	LDLIBS += -lSDL2
	SDL2_TARGET = lib/libSDL2.a
endif

all: $(NAME)

$(NAME): fonts assets/wolf3d lib/libmlx.a $(SDL2_TARGET) headers/miniaudio.h $(OBJS)
ifeq ($(USE_SYSTEM_SDL2),1)
	@echo "\033[1;33mUsing system SDL2 library for linking.\033[0m"
else
	@echo "\033[1;32mUsing bundled SDL2 library for linking.\033[0m"
endif
	@echo "\033[1;32mCompiling \033[1;0m\"$(OBJS)\"\033[1;32m into \033[1;0m\"$(NAME)\"\033[1;32m.\033[0m"
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES) $(LIBS) $(LDLIBS)

lib/libmlx.a:
	@echo "\033[1;32mCompiling \033[1;0m\"minilibx\"\033[1;32m.\033[0m"
	@rm -rf lib/minilibx-linux
	@tar -xzf lib/minilibx-linux.tgz -C lib
ifeq ($(UNAME_S),Darwin)
	@cp lib/libmlx_Darwin.a lib/libmlx.a
else
	@$(MAKE) -j -C lib/minilibx-linux
	@cp lib/minilibx-linux/libmlx.a lib
endif
	@cp lib/minilibx-linux/mlx.h headers
	@rm -rf lib/minilibx-linux

headers/miniaudio.h:
	@echo "\033[1;32mCompiling \033[1;0m\"miniaudio\"\033[1;32m.\033[0m"
	@rm -rf headers/miniaudio.h
	@tar -xzf lib/miniaudio.tar.gz -C headers

lib/libSDL2.a:
ifeq ($(USE_SYSTEM_SDL2),1)
	@echo "\033[1;33mUsing system SDL2 library.\033[0m"
else
	@echo "\033[1;32mCompiling \033[1;0m\"SDL2\"\033[1;32m.\033[0m"
	@rm -rf lib/SDL2-2.32.8
	@tar -xzf lib/SDL2-2.32.8.tar.gz -C lib
	@mkdir -p lib/SDL2-2.32.8/build
	@cd lib/SDL2-2.32.8/build && ../configure --disable-shared --enable-static --prefix=$(abspath lib) && make -j
	@cp lib/SDL2-2.32.8/build/build/.libs/libSDL2.a lib/
	@mkdir -p headers/SDL2
	@cp -r lib/SDL2-2.32.8/include/* headers/SDL2/
	@rm -rf lib/SDL2-2.32.8
endif

$(OBJ_DIR)/%.o: %.c
	@echo "\033[1;32mCompiling \033[1;0m\"$<\"\033[1;32m into \033[1;0m\"$@\"\033[1;32m.\033[0m"
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean-everything-but-ft-audio:
	@if [ -d "$(OBJ_DIR)/$(FT_AUDIO_DIR)" ]; then \
		tar -cf ft_audio.tar -C $(OBJ_DIR) $(FT_AUDIO_DIR); \
	fi
	@$(MAKE) -j clean
	@if [ -f "ft_audio.tar" ]; then \
		mkdir -p $(OBJ_DIR); \
		tar -xf ft_audio.tar -C $(OBJ_DIR); \
		rm -f ft_audio.tar; \
	fi

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf lib/libmlx.a
	@rm -rf headers/mlx.h
	@rm -rf headers/SDL2/
	@rm -rf lib/libSDL2.a
	@rm -rf headers/miniaudio.h

re: fclean all

cdev: clean-everything-but-ft-audio dev

run: $(NAME)
	./$(NAME) maps/hub.cub

val: $(NAME)
	@valgrind --show-leak-kinds=all --leak-check=full --track-fds=all --suppressions=cub.supp ./$(NAME) maps/hub.cub

lldb: $(NAME)
	@lldb -o "run" ./$(NAME) maps/hub.cub

fonts:
	@bash scripts/fonts.sh

debug-sdl2:
ifeq ($(USE_SYSTEM_SDL2),1)
	@echo "\033[1;33mUsing system SDL2 library\033[0m"
	@echo "SDL2 CFLAGS: $(SDL2_CFLAGS)"
	@echo "SDL2 LIBS: $(SDL2_LIBS)"
else
	@echo "\033[1;31mUsing bundled SDL2 library (will compile from source)\033[0m"
	@echo "SDL2 will be compiled from lib/SDL2-2.32.8.tar.gz"
endif

.PHONY: all re clean fclean run val errors debug-sdl2
