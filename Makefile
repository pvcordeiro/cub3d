# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 17:16:21 by afpachec          #+#    #+#              #
#    Updated: 2025/05/18 19:29:23 by afpachec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

ifeq ($(UNAME_S),Darwin)
	LIBS += -L /opt/homebrew/lib
	INCLUDES += -I /opt/X11/include
	LDLIBS += -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(NAME): lib/libmlx.a $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES) $(LIBS) $(LDLIBS)
	@echo "\033[1;32mCompiled \033[1;0m\"$(OBJS)\"\033[1;32m into \033[1;0m\"$(NAME)\"\033[1;32m.\033[0m"

lib/libmlx.a:
	@rm -rf lib/minilibx-linux
	@tar -xzf lib/minilibx-linux.tgz -C lib
ifeq ($(UNAME_S),Darwin)
	@cp lib/libmlx_Darwin.a lib/libmlx.a
else
	@$(MAKE) -C lib/minilibx-linux
	@cp lib/minilibx-linux/libmlx.a lib
endif
	@cp lib/minilibx-linux/mlx.h headers
	@rm -rf lib/minilibx-linux

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[1;32mCompiled \033[1;0m\"$<\"\033[1;32m into \033[1;0m\"$@\"\033[1;32m.\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf lib/minilibx-linux

fclean: clean
	@rm -rf $(NAME)
	@rm -rf lib/libmlx.a
	@rm -rf headers/mlx.h

re: fclean all

dev: clean $(NAME)
	./$(NAME) maps/subject.cub

run: clean $(NAME)
	@for map in $(MAPS); do echo "Running with $$map" && ./$(NAME) $$map; done

val: re
	@valgrind --show-leak-kinds=all --leak-check=full --track-fds=all ./$(NAME) maps/subject.cub

encrypt-wolf3d-assets:
	@cd assets/wolf3d && zip --password "$$(curl -L accounts.omelhorsite.pt)" -r assets.zip *
	@cd assets/wolf3d && zip --password "$$(curl -L jokes.omelhorsite.pt)" -r wolf3d-assets.zip assets.zip
	@cd assets/wolf3d && rm -rf assets.zip
	@rm -rf assets/wolf3d-assets.zip
	@mv assets/wolf3d/wolf3d-assets.zip assets

decrypt-wolf3d-assets:
	@rm -rf assets/wolf3d
	@cd assets && unzip -P "$$(curl -L jokes.omelhorsite.pt)" wolf3d-assets.zip
	@cd assets && mkdir -p wolf3d
	@cd assets/wolf3d && unzip -P "$$(curl -L accounts.omelhorsite.pt)" ../assets.zip
	@rm -rf assets/assets.zip

errors:
	@bash -c "python3 <(git show error-msgs-script:gen_error_msgs.py)"
	@bash -c "python3 <(git show error-msgs-script:check_error_signals.py) src"

.PHONY: all re clean fclean run val errors
