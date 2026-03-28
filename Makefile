# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ileon <ileon@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/26 11:27:55 by rgohrig           #+#    #+#              #
#    Updated: 2026/03/28 09:14:16 by ileon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #




# **************************************************************************** #
#                             C MAKEFILE
# **************************************************************************** #

# ----------------------------- GENERAL ----------------------------------------

NAME :=				miniRT

COMPILER :=			cc

DEBUG_FLAGS:=		-fsanitize=address,undefined
PROFILE_FLAGS :=	-pg
FAST_FLAGS :=		-march=native -O3 -flto # Ofast is more extreme than O3 alters math stuff
LINKER_FLAGS :=		-ffast-math
COMPILE_FLAGS :=	-MMD -MP # MMD & MD for dependencies
LIBMLX_FLAGS :=		-ldl -lglfw -pthread -lm

CFLAGS :=			-Wall -Werror -Wextra -Wdouble-promotion  -g3 $(FAST_FLAGS) $(LINKER_FLAGS) $(COMPILE_FLAGS)

# todo: -Wpadded add at the end for testing to CFLAGS but after that remove it because it brakes with mlx42


# -ffast -flto ARE LINKER FLAGS

DIR_SRC :=		src
SRC :=			color/color_ray.c color/draw_pixel.c color/full_img.c \
				color/materials.c color/shadow.c data_structs/allocs.c \
				data_structs/dynamic_array.c data_structs/dynamic_array_access.c \
				data_structs/globals.c data_structs/random.c execution/error.c \
				execution/file_handeling.c execution/free_data.c execution/hooks.c \
				execution/hooks_camera.c execution/init_gui.c execution/init_scene.c \
				execution/main.c execution/print_debug.c execution/render.c \
				execution/statistics.c execution/time.c parsing/atof.c parsing/atoi.c \
				parsing/example_spheres.c parsing/example_spheres_2.c \
				parsing/line_handers.c parsing/line_handers_shapes.c parsing/parsing_main.c \
				parsing/smal_steps.c parsing/smal_steps_color.c shapes/cylinder.c \
				shapes/hit_all.c shapes/plane.c shapes/sphere.c testing/test_cylinder.c \
				testing/test_cylinder_ext.c testing/test_plane.c testing/testing.c \
				testing/testing_main.c vectors_math/advanced.c vectors_math/advanced_ray.c \
				vectors_math/basic.c vectors_math/basic_pointer.c \
				vectors_math/basic_pointer_scalar.c vectors_math/basic_scalar.c \
				vectors_math/clamp.c vectors_math/combine.c vectors_math/compare.c \
				vectors_math/convert_to.c vectors_math/intervals.c

DIR_OBJ :=		obj
OBJ :=			$(SRC:%.c=$(DIR_OBJ)/%.o)

LIBFT_DIR :=	./libft
LIBFT :=		$(LIBFT_DIR)/libft.a

LIBMLX_DIR :=	./MLX42
LIBMLX :=		$(LIBMLX_DIR)/build/libmlx42.a


HEADERS :=		-I $(LIBFT_DIR)/include -I $(LIBMLX_DIR)/include/MLX42 -I ./include
LIBS :=			$(LIBFT) $(LIBMLX) $(LIBMLX_FLAGS)


DEPENDENCIES := $(OBJ:.o=.d)


# ----------------------------- NORMAL -----------------------------------------

# default Rule
all: stop rust-helper-for-c $(LIBFT) $(LIBMLX) $(NAME) #TODO: rm at end rust-helper-for-c



$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) CFLAGS="$(filter-out -flto,$(CFLAGS))"


$(LIBMLX):
	@if [ ! -f $(LIBMLX_DIR)/CMakeLists.txt ]; then \
		echo "   📥 MLX42 not found, cloning..."; \
		git clone git@github.com:codam-coding-college/MLX42.git $(LIBMLX_DIR); \
	else \
		git submodule update --init --recursive; \
	fi
# 	@cmake -DDEBUG=1 $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build > /dev/null && make -C $(LIBMLX_DIR)/build -j4 > /dev/null
	@cmake -DDEBUG=1 $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4
	@echo "   🛠️ 🛠️ 🛠️  MLX42 compiled"

#  -DDEBUG=1 at cmake for debug infos # -DGLFW_FETCH=0 purpose ?


$(DIR_OBJ):
	@mkdir $(DIR_OBJ)

# Compilation
$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c | $(DIR_OBJ)
	@mkdir -p $(dir $@)
	@$(COMPILER) $(CFLAGS) $(HEADERS) -o $@ -c $<
	@echo 🎇 $@

# Linking
$(NAME): $(OBJ)
	@$(COMPILER) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "\n   🎇🎇🎇 $@   ($(CFLAGS))\n"

# ----------------------------- Dependencies -----------------------------------
-include $(DEPENDENCIES)

# ----------------------------- Clean ------------------------------------------

stop:
	@pkill -x $(NAME) > /dev/null 2>&1 && echo "🛑 stopped $(NAME)" || true

clean:
	@rm -rf $(DEPENDENCIES)
	@rm -rf $(OBJ)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
# 	@rm -rf $(LIBMLX_DIR)/build
	@echo 🧹 cleaned $(NAME) objects

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean > /dev/null
# 	@rm -rf $(LIBMLX_DIR)/build > /dev/null
	@echo 🧹🧹🧹 cleaned $(NAME)

re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all

# ----------------------------- Debug ------------------------------------------

# debug: fclean
# debug: CFLAGS += $(DEBUG_FLAGS)
# debug: all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: CFLAGS := $(filter-out $(FAST_FLAGS),$(CFLAGS))
debug:
	@$(COMPILER) $(CFLAGS) $(HEADERS) -o $(NAME) $(addprefix $(DIR_SRC)/,$(SRC)) $(LIBS)
	@echo "\n   🐞🐞🐞 DEBUG $(NAME)   ($(CFLAGS))\n"
	@./miniRT


profile: CFLAGS += $(PROFILE_FLAGS)
# profile: CFLAGS := $(filter-out $(FAST_FLAGS),$(CFLAGS))
profile:
	@$(COMPILER) $(CFLAGS) $(COMPILE_FLAGS) $(LINKER_FLAGS) $(HEADERS) -o $(NAME) $(addprefix $(DIR_SRC)/,$(SRC)) $(LIBS)
	@echo "\n   📊📊📊 PROFILE $(NAME)   ($(CFLAGS))\n"
	

# ----------------------------- Lazy Robin -------------------------------------

# temporary Rule to update the header file
rust-helper-for-c:
	@rust-helper-for-c || echo "Error: rust-helper-for-c -> skipped, ask robin about it"

# ----------------------------- Phony ------------------------------------------

.PHONY: all clean fclean re debug profile stop rust-helper-for-c
