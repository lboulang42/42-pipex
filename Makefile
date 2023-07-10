# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 17:31:43 by lboulang          #+#    #+#              #
#    Updated: 2023/07/10 14:57:11 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME
NAME = 			pipex
NAME_BONUS =	 pipex_bonus
#LIBRARIES
LIBFT = 		./libft/libft.a
#SOURCES
SRCS =			./srcs/mandatory/main.c\
				./srcs/mandatory/acces.c\
				./srcs/mandatory/exec.c\
				./srcs/mandatory/clean.c
SRCS_BONUS =	./srcs/bonus/main_bonus.c\
				./srcs/bonus/acces_bonus.c\
				./srcs/bonus/exec_bonus.c\
				./srcs/bonus/clean_bonus.c\
				./srcs/bonus/gnl_bonus.c
#OBJECTS
OBJS = ${SRCS:.c=.o }
OBJS_BONUS = ${SRCS_BONUS:.c=.o }
#COMPILER
CC = @ gcc
CFLAGS = -g3 -Wall -Werror -Wextra -I .
#VISUAL
BOLD_TEXT = \033[1m
RESET_TEXT = \033[0m

all: ${NAME}

$(NAME) : ${OBJS}
	@make --no-print-directory  -C ./libft/
	$(CC) ${OBJS} ${LIBFT} -o ${NAME}
	@echo "PIPEX $(BOLD_TEXT)MANDATORY$(RESET_TEXT) MAKED ✅\n"
	
bonus : ${OBJS_BONUS}
	@make --no-print-directory  -C ./libft/
	@$(CC) ${OBJS_BONUS} ${LIBFT} -o ${NAME_BONUS}
	@echo "PIPEX $(BOLD_TEXT)BONUS$(RESET_TEXT) MAKED ✅\n"
	

clean : 
	@make --no-print-directory clean -C ./libft/
	@rm -rf ${OBJS} 
	@echo "PIPEX $(BOLD_TEXT)MANDATORY$(RESET_TEXT) CLEANED 🚮\n"
	@rm -rf ${OBJS_BONUS} 
	@echo "PIPEX $(BOLD_TEXT)BONUS$(RESET_TEXT) CLEANED 🚮\n"
	
fclean : clean
	@rm -rf ${LIBFT}
	@echo "$(BOLD_TEXT)LIBFT$(RESET_TEXT) FCLEANED 🚮\n"
	@rm -rf ${NAME}
	@echo "PIPEX $(BOLD_TEXT)MANDATORY$(RESET_TEXT) FCLEANED 🚮\n"
	@rm -rf ${NAME_BONUS}
	@echo "PIPEX $(BOLD_TEXT)BONUS$(RESET_TEXT) FCLEANED 🚮\n"

re : fclean all

.PHONY : all bonus clean fclean re