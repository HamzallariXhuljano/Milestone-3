# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 17:12:19 by xhamzall          #+#    #+#              #
#    Updated: 2025/06/08 19:50:29 by xhamzall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g

# Includi la directory di include per readline
INCLUDES = -I/usr/include -Ilibft -I/usr/local/opt/readline/include

LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a

NAME = minishell

SRCDIR = source/
SRC = source/ dollar.c \
ft_is_something.c ft_count.c path.c \
main.c pipex_bonus.c redirect_output.c

BUILTINDIR = builtin/
BLT = builtin/ cd.c echo.c env.c export.c pwd.c exit.c unset.c

UTILSDIR = utils/
UTL = utils/ utils_export.c utils_export1.c utils_export2.c utils_bonus.c utils.c utils_cd.c \
	test_parsing_utils.c test_parsing_utils1.c test_parsing_utils2.c count_utils.c \
	utils_main.c main_utils1.c main_utils2.c utils_exc.c utils_exc1.c utils_exc2.c utils_exc3.c utils_exc4.c utils_exc5.c \
	utils1.c utils2.c utils3.c utils4.c utils5.c

PARSINGDIR = parsing/
PRS = parsing/ first_parse.c second_parse.c test_parsing.c

ALL_SRC = $(SRC) $(BLT) $(UTL) $(PRS)
OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(ALL_SRC:.c=.o)))

# Aggiungi il linking a readline con -L per specificare il percorso di libreria
LIBS = -L/usr/local/opt/readline/lib -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIBFT) $(LIBS)
# Libft compiling
$(LIBFT): $(LIBFTDIR)
	@$(MAKE) -C $(LIBFTDIR) --quiet

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRCDIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
$(OBJ_DIR)/%.o: $(BUILTINDIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
$(OBJ_DIR)/%.o: $(UTILSDIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
$(OBJ_DIR)/%.o: $(PARSINGDIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
# Bonus object

clean:
	@if [ -d "$(LIBFTDIR)" ]; then $(MAKE) clean -C $(LIBFTDIR); fi
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	rm -rf $(NAME)

re: fclean all

vall: all clean
		valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=valgrind.supp ./minishell

.PHONY: all clean fclean re
