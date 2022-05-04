RELEASE_NAME		:=		libleaky.a
DEBUG_NAME			:=		libleakyd.a

INC_DIR		:=		-I.

CFLAGSD		:=		-Wall -Werror -Wextra -o2 -MD $(INC_DIR) -g3 -fsanitize=address -DDEBUG

CFLAGS		:=		-Wall -Werror -Wextra -o2 -MD $(INC_DIR)

CC			:=		gcc

#-----------#
#  Sources  #
#-----------#

BASIC_DIR	:=		basics
BASIC		:=		ft_calloc.c gc_memcpy.c gc_memmove.c gc_memset.c gc_memseti.c gc_memsetf.c gc_strlcpy.c gc_strlen.c

EXTRAS_DIR	:=		extras
EXTRAS		:=		gc_get_next_line.c gc_strappend.c gc_split.c

STD_DIR		:=		standard
STD			:=		gc_calloc.c gc_itoa.c gc_strdup.c gc_strjoin.c gc_substr.c

STRARR_DIR	:=		string_array
STRARR		:=		gc_strarray_append.c gc_strarray_asstr.c gc_strarray_free.c gc_strarray_from.c						\
					gc_strarray_fromstr.c gc_strarray_init.c gc_strarray_size.c

#----------------#
#  Core Sources  #
#----------------#

CORE_DIR	:=		core

#-----------#
#  Release  #
#-----------#

RELEASE_CORE_DIR		:=		$(CORE_DIR)/release
RELEASE_CORE			:=		gc_gc.c gc_grow.c gc_own.c gc_alloc.c gc_free.c gc_destroy.c gc_clean.c					\
								gc_utils.c																				\
								gc_init.c gc_scope.c																	\

RELEASE_ERROR_DIR		:=		$(RELEASE_CORE_DIR)/error_management
RELEASE_ERROR			:=		gc_error_interface.c gc_get_errors.c gc_get_errors2.c gc_get_errors3.c gc_error.c

RELEASE_FREEING_DIR		:=		$(RELEASE_CORE_DIR)/freeing
RELEASE_FREEING			:=		gc_clean.c gc_destroy.c gc_free.c

RELEASE_SETTINGS_DIR	:=		$(RELEASE_CORE_DIR)/settings
RELEASE_SETTINGS		:=		gc_settings.c gc_settings2.c

RELEASE_REFERENCES_DIR	:=		$(RELEASE_CORE_DIR)/references
RELEASE_REFERENCES		:=		gc_object.c gc_attach.c gc_childs.c gc_parents.c

RELEASE_ALLOCATION_DIR	:=		$(RELEASE_CORE_DIR)/allocation
RELEASE_ALLOCATION		:=		gc_alloc.c

RELEASE_PTR_MGT_DIR		:=		$(RELEASE_CORE_DIR)/pointer_managment
RELEASE_PTR_MGT			:=		gc_own.c gc_grow.c gc_insert.c gc_ptr_factory.c

#---------#
#  Debug  #
#---------#

DEBUG_CORE_DIR			:=		$(CORE_DIR)/debug
DEBUG_CORE				:=		gc_gcd.c gc_growd.c gc_ownd.c															\
								gc_utilsd.c																				\
								gc_initd.c gc_scoped.c																	\
								gc_debugd.c

DEBUG_ERROR_DIR			:=		$(DEBUG_CORE_DIR)/error_management
DEBUG_ERROR				:=		gc_error_interfaced.c gc_get_errorsd.c gc_get_errors2d.c gc_get_errors3d.c gc_errord.c

DEBUG_FREEING_DIR		:=		$(DEBUG_CORE_DIR)/freeing
DEBUG_FREEING			:=		gc_cleand.c gc_destroyd.c gc_freed.c

DEBUG_SETTINGS_DIR		:=		$(DEBUG_CORE_DIR)/settings
DEBUG_SETTINGS			:=		gc_settingsd.c gc_settings2d.c

DEBUG_REFERENCES_DIR	:=		$(DEBUG_CORE_DIR)/references
DEBUG_REFERENCES		:=		gc_objectd.c gc_attachd.c gc_childsd.c gc_parentsd.c

DEBUG_ALLOCATION_DIR	:=		$(DEBUG_CORE_DIR)/allocation
DEBUG_ALLOCATION			:=		gc_allocd.c

DEBUG_PTR_MGT_DIR		:=		$(DEBUG_CORE_DIR)/pointer_managment
DEBUG_PTR_MGT			:=		gc_ownd.c gc_growd.c gc_insertd.c gc_ptr_factoryd.c


RELEASE_OBJDIR		:=	obj
DEBUG_OBJDIR		:=	objd

RELEASE_OBJS		:=	$(addprefix $(RELEASE_OBJDIR)/, $(BASIC:.c=.o))				\
						$(addprefix $(RELEASE_OBJDIR)/, $(EXTRAS:.c=.o))			\
						$(addprefix $(RELEASE_OBJDIR)/, $(STD:.c=.o))				\
						$(addprefix $(RELEASE_OBJDIR)/, $(STRARR:.c=.o))			\
						$(addprefix $(RELEASE_OBJDIR)/, $(RELEASE_CORE:.c=.o))		\
						$(addprefix $(RELEASE_OBJDIR)/, $(RELEASE_ERROR:.c=.o))		\
						$(addprefix $(RELEASE_OBJDIR)/, $(RELEASE_FREEING:.c=.o))	\
						$(addprefix $(RELEASE_OBJDIR)/, $(RELEASE_SETTINGS:.c=.o))	\
						$(addprefix $(RELEASE_OBJDIR)/, $(RELEASE_REFERENCES:.c=.o))\
						$(addprefix $(RELEASE_OBJDIR)/, $(RELEASE_ALLOCATION:.c=.o))\
						$(addprefix $(RELEASE_OBJDIR)/, $(RELEASE_PTR_MGT:.c=.o))	\

DEBUG_OBJS			:=	$(addprefix $(DEBUG_OBJDIR)/, $(BASIC:.c=.o))				\
						$(addprefix $(DEBUG_OBJDIR)/, $(EXTRAS:.c=.o))				\
						$(addprefix $(DEBUG_OBJDIR)/, $(STD:.c=.o))					\
						$(addprefix $(DEBUG_OBJDIR)/, $(STRARR:.c=.o))				\
						$(addprefix $(DEBUG_OBJDIR)/, $(DEBUG_CORE:.c=.o))			\
						$(addprefix $(DEBUG_OBJDIR)/, $(DEBUG_ERROR:.c=.o))			\
						$(addprefix $(DEBUG_OBJDIR)/, $(DEBUG_FREEING:.c=.o))		\
						$(addprefix $(DEBUG_OBJDIR)/, $(DEBUG_SETTINGS:.c=.o))		\
						$(addprefix $(DEBUG_OBJDIR)/, $(DEBUG_REFERENCES:.c=.o))	\
						$(addprefix $(DEBUG_OBJDIR)/, $(DEBUG_ALLOCATION:.c=.o))	\
						$(addprefix $(DEBUG_OBJDIR)/, $(DEBUG_PTR_MGT:.c=.o))		\

DEPENDS		:=		$(DEBUG_OBJS:.o=.d) $(RELEASE_OBJS:.o=.d)

.PHONY: all
all:			$(RELEASE_NAME)

.PHONY: debug
debug:			$(DEBUG_NAME)

$(RELEASE_OBJDIR):
	@mkdir -p $(RELEASE_OBJDIR)

$(DEBUG_OBJDIR):
	@mkdir -p $(DEBUG_OBJDIR)

#-----------#
#  Release  #
#-----------#

$(RELEASE_OBJDIR)/%.o:	src/$(BASIC_DIR)/%.c | $(RELEASE_OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_OBJDIR)/%.o:	src/$(EXTRAS_DIR)/%.c | $(RELEASE_OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_OBJDIR)/%.o:	src/$(STD_DIR)/%.c | $(RELEASE_OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_OBJDIR)/%.o:	src/$(STRARR_DIR)/%.c | $(RELEASE_OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_OBJDIR)/%.o:	src/$(RELEASE_CORE_DIR)/%.c | $(RELEASE_OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_OBJDIR)/%.o:	src/$(RELEASE_ERROR_DIR)/%.c | $(RELEASE_OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_OBJDIR)/%.o:	src/$(RELEASE_FREEING_DIR)/%.c | $(RELEASE_OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_OBJDIR)/%.o:	src/$(RELEASE_SETTINGS_DIR)/%.c | $(RELEASE_OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_OBJDIR)/%.o:	src/$(RELEASE_REFERENCES_DIR)/%.c | $(RELEASE_OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_OBJDIR)/%.o:	src/$(RELEASE_ALLOCATION_DIR)/%.c | $(RELEASE_OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_OBJDIR)/%.o:	src/$(RELEASE_PTR_MGT_DIR)/%.c | $(RELEASE_OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

#---------#
#  Debug  #
#---------#

$(DEBUG_OBJDIR)/%.o:	src/$(BASIC_DIR)/%.c | $(DEBUG_OBJDIR)
	@$(CC) $(CFLAGSD) -c $< -o $@

$(DEBUG_OBJDIR)/%.o:	src/$(EXTRAS_DIR)/%.c | $(DEBUG_OBJDIR)
	@$(CC) $(CFLAGSD) -c $< -o $@

$(DEBUG_OBJDIR)/%.o:	src/$(STD_DIR)/%.c | $(DEBUG_OBJDIR)
	@$(CC) $(CFLAGSD) -c $< -o $@

$(DEBUG_OBJDIR)/%.o:	src/$(STRARR_DIR)/%.c | $(DEBUG_OBJDIR)
	@$(CC) $(CFLAGSD) -c $< -o $@

$(DEBUG_OBJDIR)/%.o:	src/$(DEBUG_CORE_DIR)/%.c | $(DEBUG_OBJDIR)
	@$(CC) $(CFLAGSD) -c $< -o $@

$(DEBUG_OBJDIR)/%.o:	src/$(DEBUG_ERROR_DIR)/%.c | $(DEBUG_OBJDIR)
	@$(CC) $(CFLAGSD) -c $< -o $@

$(DEBUG_OBJDIR)/%.o:	src/$(DEBUG_FREEING_DIR)/%.c | $(DEBUG_OBJDIR)
	@$(CC) $(CFLAGSD) -c $< -o $@

$(DEBUG_OBJDIR)/%.o:	src/$(DEBUG_SETTINGS_DIR)/%.c | $(DEBUG_OBJDIR)
	@$(CC) $(CFLAGSD) -c $< -o $@

$(DEBUG_OBJDIR)/%.o:	src/$(DEBUG_REFERENCES_DIR)/%.c | $(DEBUG_OBJDIR)
	@$(CC) $(CFLAGSD) -c $< -o $@

$(DEBUG_OBJDIR)/%.o:	src/$(DEBUG_ALLOCATION_DIR)/%.c | $(DEBUG_OBJDIR)
	@$(CC) $(CFLAGSD) -c $< -o $@

$(DEBUG_OBJDIR)/%.o:	src/$(DEBUG_PTR_MGT_DIR)/%.c | $(DEBUG_OBJDIR)
	@$(CC) $(CFLAGSD) -c $< -o $@

$(RELEASE_NAME):		$(RELEASE_OBJS)
	@ar -rcs $(RELEASE_NAME) $(RELEASE_OBJS)
	@echo "Compiled Leaky"

$(DEBUG_NAME):		$(DEBUG_OBJS)
	@ar -rcs $(DEBUG_NAME) $(DEBUG_OBJS)
	@echo "Compiled Leaky"

.PHONY: clean
clean:
	@rm -rf $(RELEASE_OBJDIR)
	@rm -rf $(DEBUG_OBJDIR)

.PHONY: fclean
fclean: clean
	@rm -f $(RELEASE_NAME)
	@rm -f $(DEBUG_NAME)

.PHONY: re
re: fclean all

.PHONY: debug_re
debug_re: fclean debug

.PHONY: both
both: $(RELEASE_NAME) $(DEBUG_NAME)

.PHONY: both_re
both_re: re debug_re

-include $(DEPENDS)
