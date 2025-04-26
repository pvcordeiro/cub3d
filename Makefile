# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 17:16:21 by afpachec          #+#    #+#              #
#    Updated: 2025/04/26 22:51:12 by afpachec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I headers
LIBS = -L lib
LDLIBS = -lX11 -lXext -lm
SRCS = $(wildcard src/**/**.c) $(wildcard src/*.c)
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
MAPS = $(wildcard maps/*.cub)
UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	LIBS += -L /opt/homebrew/lib
	LDLIBS += -lmlx_Darwin -framework OpenGL -framework AppKit
else
	LDLIBS += -lmlx
endif

all: $(NAME)

$(NAME): mlx $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES) $(LIBS) $(LDLIBS)

mlx:
	@tar -xzf lib/minilibx-linux.tgz -C lib
ifeq ($(UNAME_S),Linux)
	@$(MAKE) -C lib/minilibx-linux
	@cp lib/minilibx-linux/libmlx.a lib
endif
	@cp lib/minilibx-linux/mlx.h headers

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

run: $(NAME)
	@for map in $(MAPS); do echo "Running with $$map" && ./$(NAME) $$map; done

val: re
	@valgrind --show-leak-kinds=all --leak-check=full --track-fds=all ./$(NAME)

.PHONY: all re clean fclean v
