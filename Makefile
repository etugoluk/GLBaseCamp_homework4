NAME = date

SRCS = Date.cpp \
		main.cpp

OBJ = $(SRCS:.cpp=.o)

CFLAGS = -std=c++11 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	g++ $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re