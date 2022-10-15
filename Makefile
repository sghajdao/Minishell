NAME = minishell

CC = cc

#LDFLAGS="-L/goinfre/sghajdao/homebrew/opt/readline/lib"
#
#CPPFLAGS="-I/goinfre/sghajdao/homebrew/opt/readline/include"

LIBFT = libft/libft.a

HEADER = ./header/minishell.h

BUILTINS = cd echo env exit export pwd unset cd_utils export_utils

ENV = env get_env sort_env shlvl env_tools

EXEC = bin builtin exec heredoc

MAIN = minishell redir signal

PARSING = parser tokens expander lexer

TOOLS = fd free token type expander parsing

SRC = $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@make bonus -C libft/
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@echo "\n\033[0;42mDone !"

%.o:%.c HEADER
	@printf "\033[0;33mGenerating minishell objects... %-10.10s\r" $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[0;31m\nDeleting objects...\033[0;37m"
	@make clean -C libft/
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft/
	@rm -rf $(OBJ)
	@rm -rf $(NAME)

re: fclean all
