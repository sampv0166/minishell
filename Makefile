RED = \033[0;31m
BLACK = \033[0;30m
WHITE = \033[1;37m

.SILENT:

NAME = minishell

SRCS = 	srcs/main.c \
		srcs/built_ins/built_ins.c \
		srcs/env/get_env.c \
		srcs/env/env_vars.c \
		srcs/executor/executor.c \
		srcs/input_to_tokens/input_to_tokens.c \
		srcs/parcer/parcer.c \
		srcs/utils/ft_isenv.c \
		srcs/utils/ft_isqte.c \
		srcs/utils/ft_delimit_qtes.c \
		srcs/utils/length_2d.c \
		srcs/utils/ft_strcmp.c \
		srcs/utils/ft_strstr.c \
		srcs/utils/last_char.c \
		srcs/utils/signal_handling.c \
		srcs/utils/ft_putstr_2d.c \
		srcs/built_ins/echo/echo_utils.c \
		srcs/built_ins/echo/echo.c \
		srcs/built_ins/cd/cd_pwd_up.c \
		srcs/built_ins/cd/cd_tild.c \
		srcs/built_ins/cd/cd.c \
		srcs/built_ins/export/export_sort_utils1.c \
		srcs/built_ins/export/export_sort_utils2.c \
		srcs/built_ins/export/export_sort_utils3.c \
		srcs/built_ins/export/export.c \
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
		srcs/expander/expander.c \
		
OBJS = ${SRCS:.c=.o}

RM = rm -rf
CC = gcc -ggdb -g

# CFLAGS = -lreadline
# R_FLAG = -lreadline 
CFLAGS = -lreadline -L /usr/local/Cellar/readline/8.1/lib -I /usr/local/Cellar/readline/8.1/include

${NAME}:
		@echo "${WHITE}Have patience. This will take some moment!"
			${MAKE} all -C libft/
			cp ./libft/libft.a ./
			${CC} ${SRCS} libft.a ${CFLAGS} -lreadline -L /usr/local/Cellar/readline/8.1/lib -I /usr/local/Cellar/readline/8.1/include  -o ${NAME}
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWNK00KNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWKd;.${BLACK}TT${WHITE}:ONWWWWWWWWNKXWWWWWWWWWWXKNWWWWWWWWNO:${BLACK}TT${WHITE}.;dKWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWNOc.${BLACK}TTTTTT${WHITE}.';ldk0XXX0${BLACK}:;${WHITE}oddddddddo${BLACK};:${WHITE}0XXK0kdl:'.${BLACK}TTTTTT${WHITE}.cONWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWNO:.${BLACK}TTTTTTTTTTT${RED}...,::c:,..'''''.....,;::;,...${BLACK}TTTTTTTTTTT${WHITE}.:ONWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWKc.${BLACK}TTTTTTTTTT${RED}..,,:cccc:;,,''''.'''''',,,;,,'';;..${BLACK}TTTTTTTTTT${WHITE}.cKWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWNk'${BLACK}TTTTTTTTTT${RED}.',,,;cccc;.${BLACK}TTTTTTTTTTTTTTTTTT${RED}...';c:;'.${BLACK}TTTTTTTTTT${WHITE}'kNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWXl.${BLACK}TTTTTTTTTT${RED}.,'.,cccccc:'.......${BLACK}TTTTTTTTTTTTTTT${RED}.',,,,.${BLACK}TTTTTTTTTT${WHITE}.lXWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWW0;${BLACK}TTTTTTTTTT${RED}.,,..,cccccccccccc::::::::;;;,,,'...${BLACK}TTTT${RED}..';,.${BLACK}TTTTTTTTTT${WHITE};0WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWO,${BLACK}TTTTTTTTTTT${RED}.;'${BLACK}T${RED}.:ccccccccccccccccccccccccccccc:;'.${BLACK}TTT${RED}.;;.${BLACK}TTTTTTTTTTT${WHITE},OWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWO'${BLACK}TTTTTTTTTTTTT${RED}.,,;ccccccccccccccccccccccccccccccccc:'..,,.${BLACK}TTTTTTTTTTTTT${WHITE}'OWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWW0,${BLACK}TTTTTTTTTTTTTTTT${RED}.,ccccccccccccccccccccccccccccccccccc:,.${BLACK}TTTTTTTTTTTTTTTT${WHITE},0WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWW${WHITE}WK:${BLACK}TTTTTTTTTTTTTTTTTTT${RED}.,cc;;::ccccccccccccccccccccccccc:,.${BLACK}TTTTTTTTTTTTTTTTTTT${WHITE}:KWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWNo.${BLACK}TTTTTTTTTTTTT${WHITE}.',;;:;${RED}''','......'''''''''',,;:ccccc:,''${WHITE};:;;,'.${BLACK}TTTTTTTTTTTTT${WHITE}.oNWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWW0,${BLACK}TTT${WHITE}.';:ldxkl,cONNWWWWXkl${RED};,,..${BLACK}TTTTTTTTTTTTTTTT${RED}':cc:;${WHITE};lkXWWWWNNOc,lkxdl:;'.${BLACK}TTT${WHITE},0WWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWd..:xKNWWWWWWWNNWWWWWWWWWWXkoc${RED}:;,'............';::${WHITE}cokXWWWWWWWWWWNNWWWWWWWNKx:..dWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWdl0WWWWWWWWWWWWWWWWWWWWWWWWWWXOdocc${RED};,'''''',:${WHITE}ccldOXWWWWWWWWWWWWWWWWWWWWWWWWWW0ldWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWX0xl${RED};..${BLACK}TT${RED}..;${WHITE}ox0XWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWNNWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWNKxc${RED};;${WHITE}ckKNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWNK00KNWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
		@echo " 			                                                                       "
		@echo " 			    ███    ███ ██ ███    ██ ██       ███████ ██   ██ ███████ ██      ██     " 
		@echo " 			    ████  ████ ██ ████   ██ ██       ██      ██   ██ ██      ██      ██     " 
		@echo " 			    ${RED}██ ████ ██ ██ ██ ██  ██ ██ █████ ███████ ███████ █████   ██      ██     " 
		@echo " 			    ██  ██  ██ ██ ██  ██ ██ ██       ${RED}     ██ ██   ██ ██      ██      ██     " 
		@echo " 			    ██      ██ ██ ██   ████ ██       ${RED}███████ ██   ██ ███████ ███████ ███████"
		@echo " 			    ${WHITE}                                                                        "
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