# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/26 11:27:55 by rgohrig           #+#    #+#              #
#    Updated: 2026/01/26 14:24:57 by rgohrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



# **************************************************************************** #
#                             C MAKEFILE
# **************************************************************************** #

# ----------------------------- GENERAL ----------------------------------------

NAME :=				miniRT

COMPILER :=			cc
DEBUG_FLAGS:=		-fsanitize=address,undefined
FAST_FLAGS :=		-march=native -O3 # Ofast is mor extreme than O3 alters math stuff
LINKER_FLAGS :=		-ffast-math -flto
CFLAGS :=			-Wall -Werror -Wextra -Wdouble-promotion -Wpadded -g3 $(FAST_FLAGS)
LIBMLX_FLAGS :=	-ldl -lglfw -pthread -lm

# -ffast -flto ARE LINKER FLAGS

DIR_SRC :=		src
SRC :=			$(patsubst $(DIR_SRC)/%,%,$(shell find $(DIR_SRC) -type f -name "*.c")) # TODO: at end fix


DIR_OBJ :=		obj
OBJ :=			$(SRC:%.c=$(DIR_OBJ)/%.o)

LIBFT_DIR :=	./libft
LIBFT :=		$(LIBFT_DIR)/libft.a

LIBMLX_DIR :=	./MLX42
LIBMLX :=		$(LIBMLX_DIR)/build/libmlx42.a


HEADERS :=		-I $(LIBFT)/include -I $(LIBMLX)/include/MLX42 -I ./include
LIBS :=			$(LIBFT) $(LIBMLX) $(LIBMLX_FLAGS)


# ----------------------------- NORMAL -----------------------------------------

# default Rule
all: $(LIBFT) $(LIBMLX) $(NAME)



$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) CFLAGS="$(CFLAGS)"


$(LIBMLX):
	@git submodule update --init --recursive
	@cmake -DDEBUG=1 $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build > /dev/null && make -C $(LIBMLX_DIR)/build -j4 > /dev/null
	@echo "   🛠️ 🛠️ 🛠️  MLX42 compiled"

#  -DDEBUG=1 at cmake for debug infos # -DGLFW_FETCH=0 purpose ?


$(DIR_OBJ):
	@mkdir $(DIR_OBJ)

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c | $(DIR_OBJ)
	@mkdir -p $(dir $@)
	@$(COMPILER) $(CFLAGS) $(HEADERS) -o $@ -c $<
	@echo 🎇 $@

# Linking
$(NAME): $(OBJ)
	@$(COMPILER) $(CFLAGS) $(LINKER_FLAGS) -o $@ $^ $(LIBS)
	@echo "\n   🎇🎇🎇 $@   ($(CFLAGS))\n"


# ----------------------------- Clean ------------------------------------------

clean:
	@rm -rf $(OBJ)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(LIBMLX_DIR)/build
	@echo 🧹 cleaned $(NAME) objects

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean > /dev/null
# 	@rm -rf $(LIBMLX_DIR)/build > /dev/null
	@echo 🧹🧹🧹 cleaned $(NAME)

re: fclean all

# ----------------------------- Debug ------------------------------------------

debug: fclean
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(NAME)

# ----------------------------- Phony ------------------------------------------

.PHONY: all clean fclean re debug
