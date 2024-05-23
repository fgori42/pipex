# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgori <fgori@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 10:30:10 by fgori             #+#    #+#              #
#    Updated: 2024/02/22 12:00:51 by fgori            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

file = pipex.c\
		pipex_utilis.c

file_bonus =pipex_bonus.c\
			pipex_utils_bonus.c
cc = cc

flag = -Wall -Werror -Wextra

LFT = ./libft
LIBFT = $(LFT)/libft.a

NAME = pipex

BONUS = pipex_bonus

all: $(NAME)

bonus: $(BONUS)

$(NAME):
		@make all -C $(LFT)
		@$(CC) -fPIE $(CFLAG) -I$(LFT) -L$(LFT) $(file) $(LIBFT) -pthread -o $(NAME)	
$(BONUS):
		@make re -C $(LFT)		
		@$(CC) -fPIE $(CFLAG) -I$(LFT) -L$(LFT) $(file_bonus) $(LIBFT) -pthread -o $(BONUS)
clean:
		@make clean -C $(LFT)
fclean_bonus:
	rm -f $(BONUS)
fclean:
	rm -f $(NAME)
	@make fclean -C $(LFT)
fclean_all: fclean fclean_bonus
re: fclean fclean_bonus all bonus

.PHONY: all bonus clean fclean fclean_all fclean_bonus