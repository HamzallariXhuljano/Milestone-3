# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/09 17:24:10 by xhamzall          #+#    #+#              #
#    Updated: 2025/06/10 18:39:14 by xhamzall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g

# Includi la directory di include per readline
INCLUDES = -I/usr/include

NAME = philo

SRCDIR = source/
SRC = philo.c parsing.c \

ALL_SRC = $(SRC)
OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(ALL_SRC:.c=.o)))

all: $(NAME)

$(NAME):$(OBJECTS)
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
	mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRCDIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@if [ -d "$(LIBFTDIR)" ]; then $(MAKE) clean -C $(LIBFTDIR); fi
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	rm -rf $(NAME)

re: fclean all

vall: all clean
		valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./philo

.PHONY: all clean fclean re
