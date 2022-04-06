NAME = test

MAIN_SRC = tests.cpp\
			insert_test.cpp

SRC = $(addprefix srcs/, $(MAIN_SRC))
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)

CXX = c++
CXXFLAGS = -MMD -I ./includes/ -Wall -Wextra -Werror
# -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)

re: clean all

reclean: re clean

.PHONY: all clean fclean re reclean

include $(wildcard $(DEP))