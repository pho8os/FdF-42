NAME = fdf

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = 

BONUS = 


BONUSOBJS = $(BONUS:.c=.o)

OBJS = $(patsubst %.c, %.o, $(SRCS))

all:$(NAME)

lib-ft/libft.a:
	make bonus -C lib-ft

%.o:%.c fdf.h gnl/get_next_line.h lib-ft/libft.h 
	$(CC) $(CFLAGS) -c $<

$(NAME):$(OBJS) lib-ft/libft.a
	$(CC) $(OBJS) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -o $(NAME) lib-ft/libft.a

clean:
	rm -f $(OBJS) $(BONUSOBJS)
	make clean -C lib-ft

fclean: clean 
	rm -f $(NAME)
	make fclean -C lib-ft

re: fclean all 

.PHONY: clean fclean re all