NAME		:=		libleaky.a

INC_DIR		:=		-I. -Isrc/basics

CFLAGS		:=		-Wall -Werror -Wextra -o2 -MD $(INC_DIR) -fsanitize=address
LDFLAGS		:=		-fsanitize=address

CC			:=		gcc

BASIC_DIR	:=		basics
BASIC		:=		ft_calloc.c gc_memcpy.c gc_memmove.c gc_memset.c gc_memseti.c gc_memsetf.c gc_strlcpy.c gc_strlen.c

CORE_DIR	:=		core
CORE		:=		gc_gc.c gc_init.c gc_grow.c gc_own.c gc_error.c gc_alloc.c gc_free.c gc_destroy.c gc_clean.c		\
					gc_utils.c gc_scope.c settings.c

EXTRAS_DIR	:=		extras
EXTRAS		:=		gc_get_next_line.c gc_strappend.c gc_split.c

STD_DIR		:=		standard
STD			:=		gc_calloc.c gc_itoa.c gc_strdup.c gc_strjoin.c gc_substr.c

STRARR_DIR	:=		string_array
STRARR		:=		gc_strarray_append.c gc_strarray_asstr.c gc_strarray_free.c gc_strarray_from.c						\
					gc_strarray_fromstr.c gc_strarray_init.c gc_strarray_size.c

OBJDIR		:=		obj
OBJS		:=		$(addprefix $(OBJDIR)/, $(BASIC:.c=.o))		\
					$(addprefix $(OBJDIR)/, $(CORE:.c=.o))		\
					$(addprefix $(OBJDIR)/, $(EXTRAS:.c=.o))	\
					$(addprefix $(OBJDIR)/, $(STD:.c=.o))		\
					$(addprefix $(OBJDIR)/, $(STRARR:.c=.o))	\

DEPENDS		:=		$(OBJS:.o:.d)

all:			$(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	src/$(BASIC_DIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o:	src/$(CORE_DIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o:	src/$(EXTRAS_DIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o:	src/$(STD_DIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o:	src/$(STRARR_DIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
	@ar -rcs $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

-include: $(DEPENDS)
