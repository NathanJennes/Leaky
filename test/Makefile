NAME	:=		tests

CFLAGS	:=		-Wall -Werror -Wextra -MD -fsanitize=address
LDFLAGS	:=		-fsanitize=address

SRCDIR	:=		src
SRC		:=		core.c

OBJDIR	:=		obj
OBJS	:=		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEPENDS	:=		$(OBJS:.o=.d)

LIB		:=		../libleaky.a

all:		$(NAME)
	./$(NAME)

$(NAME):	$(OBJS)
	@clang $(LDFLAGS) $(OBJS) $(LIB) -o $(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
	@clang $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

-include $(DEPENDS)
