# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afpachec <afpachec@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 17:16:21 by afpachec          #+#    #+#              #
#    Updated: 2025/05/01 14:08:12 by afpachec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I headers
LIBS = -L lib
LDLIBS = -lmlx -lX11 -lXext -lm
SRCS = $(shell find src -name "**.c")
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
MAPS = $(wildcard maps/*.cub)
UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	LIBS += -L /opt/homebrew/lib
	LDLIBS += -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(NAME): lib/libmlx.a $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES) $(LIBS) $(LDLIBS)

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
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf lib/minilibx-linux

fclean: clean
	@rm -rf $(NAME)
	@rm -rf lib/libmlx.a
	@rm -rf headers/mlx.h

re: fclean all

run: clean $(NAME)
	@for map in $(MAPS); do echo "Running with $$map" && ./$(NAME) $$map; done

val: re
	@valgrind --show-leak-kinds=all --leak-check=full --track-fds=all ./$(NAME) maps/subject.cub

errors:
	@bash -c "python3 <(git show error-msgs-script:gen_error_msgs.py)"
	@bash -c "python3 <(git show error-msgs-script:check_error_signals.py) src"

.PHONY: all re clean fclean run val errors
