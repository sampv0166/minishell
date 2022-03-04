SRC_DIR = ./srcs/

LIBFT_DIR = ./libft/

SRC_FILES = main.c ./built_ins/built_ins.c ./utils/ft_strcmp.c ./input_to_tokens/input_to_tokens.c \
			./utils/signal_handling.c ./env/env_vars.c ./executor/executor.c ./parcer/parcer.c

# add predfix to all the src files    prefix = ./srcs/
SRC_NAME =  $(addprefix $(SRC_DIR), $(SRC_FILES))

CFLAG = -Wall -Wextra -Werror

LIBFT_LIB = libft.a

TARGET = minishell

all: ${LIBFT_LIB}  
	@gcc $(SRC_NAME) $(LIBFT_DIR)${LIBFT_LIB} -lreadline -o $(TARGET)

# ${LIBFT_LIB} ---> This will run the makefile inside the libft directory and create libft.a 
${LIBFT_LIB}:
	@$(MAKE) -C $(LIBFT_DIR) all 

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(TARGET)

re: fclean all


.PHONY: all clean fclean re