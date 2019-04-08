# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/26 12:26:28 by fpetras           #+#    #+#              #
#    Updated: 2019/04/08 14:17:47 by fpetras          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRC_PATH = src/
SRC = main.c \
	  usage.c \
	  command.c \
	  options.c \
	  error.c \
	  join.c \
	  print.c \
	  \
	  message_digest/options_hash.c \
	  message_digest/hash.c \
	  message_digest/read_hash.c \
	  message_digest/md5/md5.c \
	  message_digest/md5/md5_algo.c \
	  message_digest/sha/sha224_256.c \
	  message_digest/sha/sha224_256_algo.c \
	  message_digest/sha/sha384_512.c \
	  message_digest/sha/sha384_512_algo.c \
	  message_digest/hash_value.c \
	  message_digest/rotate.c \
	  message_digest/endianness.c \
	  \
	  cipher/options_cipher.c \
	  cipher/cipher.c \
	  cipher/base64/read_base64.c \
	  cipher/base64/base64.c

OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH),$(SRC:.c=.o))

HEADER_PATH = include/

MD5_PATH = message_digest/md5/
SHA_PATH = message_digest/sha/
BASE64_PATH = cipher/base64/

CC = gcc
CFLAGS = -Wall -Werror -Wextra

# ----- ANSI Escape Sequences ----- #
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
PURPLE = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m
UNDERLINE = \033[0;4m
TEXT_RESET = \033[0;0m
# --------------------------------- #

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(TEXT_RESET)"
	@echo "$(UNDERLINE)libft:$(TEXT_RESET)"
	@echo "$(BLUE)"
	@make -C libft
	@echo "$(TEXT_RESET)"
	@echo "Generating executable file:\n$(WHITE)$@\n$(TEXT_RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -Llibft/ -lft
	@echo "$(GREEN)Success$(TEXT_RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@test -d $(OBJ_PATH) || mkdir $(OBJ_PATH)
	@test -d $(OBJ_PATH)$(MD5_PATH) || mkdir -p $(OBJ_PATH)$(MD5_PATH)
	@test -d $(OBJ_PATH)$(SHA_PATH) || mkdir -p $(OBJ_PATH)$(SHA_PATH)
	@test -d $(OBJ_PATH)$(BASE64_PATH) || mkdir -p $(OBJ_PATH)$(BASE64_PATH)
	@echo "$(CYAN)Compiling $< $(TEXT_RESET)"
	@$(CC) $(CFLAGS) -I$(HEADER_PATH) -I libft/ -c $< -o $@

test_hash: $(NAME)
	@./test_hash.sh all

test_md5: $(NAME)
	@./test_hash.sh md5

test_sha: $(NAME)
	@./test_hash.sh sha224 sha256 sha384 sha512 sha512224 sha512256

test_sha224: $(NAME)
	@./test_hash.sh sha224

test_sha256: $(NAME)
	@./test_hash.sh sha256

test_sha384: $(NAME)
	@./test_hash.sh sha384

test_sha512: $(NAME)
	@./test_hash.sh sha512

test_sha512224: $(NAME)
	@./test_hash.sh sha512224

test_sha512256: $(NAME)
	@./test_hash.sh sha512256

clean:
	@make clean -C libft
	@rm -rf $(OBJ_PATH)
	@rm -rf $(NAME).dSYM
	@rm -f file file1 file2

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test_hash test_md5 test_sha224 test_sha256 test_sha384 test_sha512 test_sha512224 test_sha512256
