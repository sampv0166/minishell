RED = \033[0;31m
BLACK = \033[0;30m
WHITE = \033[1;37m

.SILENT:

NAME = minishell

SRCS = 	srcs/main.c \
		srcs/built_ins/built_ins.c \
		srcs/env/env_vars.c \
		srcs/executor/executor.c \
		srcs/input_to_tokens/input_to_tokens.c \
		srcs/parcer/parcer.c \
		srcs/utils/ft_isenv.c \
		srcs/utils/ft_isqte.c \
		srcs/utils/ft_strcmp.c \
		srcs/utils/ft_strstr.c \
		srcs/utils/last_char.c \
		srcs/utils/signal_handling.c \
		srcs/utils/ft_putstr_2d.c \
		srcs/built_ins/echo.c \
		srcs/built_ins/cd.c \
		srcs/built_ins/export.c \
		srcs/built_ins/pwd.c \
		srcs/built_ins/env.c \
		srcs/built_ins/unset.c \
		srcs/built_ins/exit.c \
		srcs/utils/free_functions.c \
		srcs/input_to_tokens/split_by_pipe_redir_utils.c \
		srcs/input_to_tokens/split_by_pipe_redir_utils2.c \
		srcs/input_to_tokens/split_to_tokens_utils.c \
		srcs/input_to_tokens/split_to_tokens_utils_2.c \
		srcs/input_to_tokens/syntax_check_utils.c \
		srcs/parcer/parcer_utils.c \
		
OBJS = ${SRCS:.c=.o}

RM = rm -rf
CC = gcc -ggdb

# CFLAGS = -lreadline
# R_FLAG = -lreadline 
CFLAGS = -lreadline -L /usr/local/Cellar/readline/8.1/lib -I /usr/local/Cellar/readline/8.1/include

${NAME}:${OBJS}
		@echo "${WHITE}Have patience. This will take some moment!"
			${MAKE} all -C libft/
			cp ./libft/libft.a ./
			${CC} ${OBJS} libft.a ${CFLAGS} -lreadline -L /usr/local/Cellar/readline/8.1/lib -I /usr/local/Cellar/readline/8.1/include  -o ${NAME}
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWNK00KNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWKd;.${BLACK}TT${WHITE}:ONWWWWWWWWNKXWWWWWWWWWWXKNWWWWWWWWNO:${BLACK}TT${WHITE}.;dKWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWNOc.${BLACK}TTTTTT${WHITE}.';ldk0XXX0${BLACK}:;${WHITE}oddddddddo${BLACK};:${WHITE}0XXK0kdl:'.${BLACK}TTTTTT${WHITE}.cONWWWWWWWWWWWW"
		@echo "WWWWWWWWWWNO:.${BLACK}TTTTTTTTTTT${RED}...,::c:,..'''''.....,;::;,...${BLACK}TTTTTTTTTTT${WHITE}.:ONWWWWWWWWWW"
		@echo "WWWWWWWWWKc.${BLACK}TTTTTTTTTT${RED}..,,:cccc:;,,''''.'''''',,,;,,'';;..${BLACK}TTTTTTTTTT${WHITE}.cKWWWWWWWWW"
		@echo "WWWWWWWNk'${BLACK}TTTTTTTTTT${RED}.',,,;cccc;.${BLACK}TTTTTTTTTTTTTTTTTT${RED}...';c:;'.${BLACK}TTTTTTTTTT${WHITE}'kNWWWWWWW"
		@echo "WWWWWWXl.${BLACK}TTTTTTTTTT${RED}.,'.,cccccc:'.......${BLACK}TTTTTTTTTTTTTTT${RED}.',,,,.${BLACK}TTTTTTTTTT${WHITE}.lXWWWWWW"
		@echo "WWWWW0;${BLACK}TTTTTTTTTT${RED}.,,..,cccccccccccc::::::::;;;,,,'...${BLACK}TTTT${RED}..';,.${BLACK}TTTTTTTTTT${WHITE};0WWWWW"
		@echo "WWWWO,${BLACK}TTTTTTTTTTT${RED}.;'${BLACK}T${RED}.:ccccccccccccccccccccccccccccc:;'.${BLACK}TTT${RED}.;;.${BLACK}TTTTTTTTTTT${WHITE},OWWWW"
		@echo "WWWO'${BLACK}TTTTTTTTTTTTT${RED}.,,;ccccccccccccccccccccccccccccccccc:'..,,.${BLACK}TTTTTTTTTTTTT${WHITE}'OWWW"
		@echo "WW0,${BLACK}TTTTTTTTTTTTTTTT${RED}.,ccccccccccccccccccccccccccccccccccc:,.${BLACK}TTTTTTTTTTTTTTTT${WHITE},0WW"
		@echo "${WHITE}WK:${BLACK}TTTTTTTTTTTTTTTTTTT${RED}.,cc;;::ccccccccccccccccccccccccc:,.${BLACK}TTTTTTTTTTTTTTTTTTT${WHITE}:KW"
		@echo "No.${BLACK}TTTTTTTTTTTTT${WHITE}.',;;:;${RED}''','......'''''''''',,;:ccccc:,''${WHITE};:;;,'.${BLACK}TTTTTTTTTTTTT${WHITE}.oN"
		@echo "0,${BLACK}TTT${WHITE}.';:ldxkl,cONNWWWWXkl${RED};,,..${BLACK}TTTTTTTTTTTTTTTT${RED}':cc:;${WHITE};lkXWWWWNNOc,lkxdl:;'.${BLACK}TTT${WHITE},0"
		@echo "d..:xKNWWWWWWWNNWWWWWWWWWWXkoc${RED}:;,'............';::${WHITE}cokXWWWWWWWWWWNNWWWWWWWNKx:..d"
		@echo "dl0WWWWWWWWWWWWWWWWWWWWWWWWWWXOdocc${RED};,'''''',:${WHITE}ccldOXWWWWWWWWWWWWWWWWWWWWWWWWWW0ld"
		@echo "NNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWX0xl${RED};..${BLACK}TT${RED}..;${WHITE}ox0XWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWNN"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWNKxc${RED};;${WHITE}ckKNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWNK00KNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "                                                                        "
		@echo "     ███    ███ ██ ███    ██ ██       ███████ ██   ██ ███████ ██      ██     " 
		@echo "     ████  ████ ██ ████   ██ ██       ██      ██   ██ ██      ██      ██     " 
		@echo "     ${RED}██ ████ ██ ██ ██ ██  ██ ██ █████ ███████ ███████ █████   ██      ██     " 
		@echo "     ██  ██  ██ ██ ██  ██ ██ ██       ${RED}     ██ ██   ██ ██      ██      ██     " 
		@echo "     ██      ██ ██ ██   ████ ██       ${RED}███████ ██   ██ ███████ ███████ ███████"
		@echo "     ${WHITE}                                                                        "
		@cat authors

all:	${NAME}

clean:
		${RM} libft.a
		${RM} ${OBJS}
		${MAKE} clean -C ./libft/

fclean:	clean
		${RM} ${NAME}
		${MAKE} fclean -C ./libft/

re:	fclean all