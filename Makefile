NAME		:=		libleaky.a

INC_DIR		:=		-I.

CFLAGS		:=		-Wall -Wextra -o2 -MD $(INC_DIR) -fsanitize=address
LDFLAGS		:=		-fsanitize=address

CC			:=		gcc

SRCDIR		:=		src
SRCS		:=		ft_calloc.c ft_memcpy.c ft_memmove.c ft_memset.c ft_memsetf.c ft_memseti.c ft_strlcpy.c				\
					gc_calloc.c gc_free.c gc_gc.c gc_get_next_line.c gc_init.c gc_itoa.c gc_split.c gc_split_free.c		\
					gc_strappend.c gc_strarray_append.c gc_strarray_asstr.c gc_strarray_free.c gc_strarray_from.c		\
					gc_strarray_fromstr.c gc_strarray_init.c gc_strarray_size.c gc_strdup.c gc_strjoin.c gc_substr.c	\

OBJDIR		:=		obj
OBJS		:=		$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

DEPENDS		:=		$(OBJS:.o:.d)

all:			$(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
	@ar -rcs $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

-include: $(DEPENDS)
