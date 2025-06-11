# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 14:57:23 by isainz-r          #+#    #+#              #
#    Updated: 2024/06/28 18:51:24 by isainz-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the final executable for the main program
NAME		= pipex

# Name of the final executable for the bonus (checker)
NAME_BONUS	= pipex_bonus

# Compiler to use
CC			= gcc

# Compiler flags: warnings, debugging info (optional: sanitize for leaks)
CFLAGS		= -Wall -Werror -Wextra -g3 #-fsanitize=address

# Source files for the main program
SRCS		=	main.c forks.c path_command.c

# Source files for the bonus program (checker)
SRCS_BONUS	=	src_bonus/main_bonus.c src_bonus/forks_bonus.c \
				src_bonus/path_command_bonus.c src_bonus/here_doc_bonus.c
# Object files generated from main sources
OBJS		=	$(SRCS:.c=.o)

# Object files generated from bonus sources
OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)

# Default target: builds the main executable
all: $(NAME)

# Rule to link object files and produce the main executable
$(NAME): $(OBJS)
	$(MAKE) -C libft			# Build libft first
	$(CC) $(OBJS) -L libft -lft -o $(NAME)	# Link everything

# Target to build the bonus executable
bonus: $(NAME_BONUS)

# Rule to link object files and produce the bonus executable
$(NAME_BONUS) : $(OBJS_BONUS)
	$(MAKE) -C libft						# Build libft first
	$(CC) $(CFLAGS) $(OBJS_BONUS) -L libft -lft -o $(NAME_BONUS)	# Link everything

# Removes object files (main and bonus)
clean:
	$(MAKE) -C libft clean		# Clean libft object files
	@rm -f	$(OBJS)			# Remove main object files
	@rm -f	$(OBJS_BONUS)		# Remove bonus object files

# Cleans all generated files including executables
fclean: clean
	$(MAKE) -C libft fclean		# Also remove libft.a
	@rm -f	$(NAME)			# Remove main executable
	@rm -f	$(NAME_BONUS)		# Remove bonus executable

# Rebuild everything from scratch
re: fclean all

# Declare non-file targets to prevent make from getting confused
.PHONY: clean fclean re all bonus
