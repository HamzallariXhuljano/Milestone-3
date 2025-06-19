# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/09 17:24:10 by xhamzall          #+#    #+#              #
#    Updated: 2025/06/18 19:27:36 by xhamzall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Wextra -Werror -g -pthread

NAME = philo

SRCDIR = source/
SRC = philo.c parsing.c checks.c init.c philo_do_utils.c philo_do.c start.c utils.c utils1.c

ALL_SRC = $(addprefix $(SRCDIR), $(SRC))
OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(ALL_SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "Compiling Philo..."
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo ""
	@echo "\033[1mUsage:\033[0m"
	@echo " ./program (NP) (TD) (TE) (TS) [LE]"
	@echo "   -(Number of philosophers)"
	@echo "   -(Time to die)"
	@echo "   -(Time to eat)"
	@echo "   -(Time to sleep)"
	@echo "   -[Limit a philosopher must eat] (Optional)"
	@echo "\033[1mAll time values must be in milliseconds.\033[0m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRCDIR)%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

vall: all clean
	valgrind --tool=helgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./philo

.PHONY: all clean fclean re vall
