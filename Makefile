##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## makefile
##

SRC_SERVER			= 		server/src/main.cpp	\
							server/src/UdpServer.cpp

SRC_CLIENT			= 		client/src/main.cpp

OBJ_SERVER			=		$(SRC_SERVER:.cpp=.o)

OBJ_CLIENT			=		$(SRC_CLIENT:.cpp=.o)

NAME_SERVER			=		r_type_server

NAME_CLIENT			=		r_type_client

LDFLAGS				=		-ldl -rdynamic -pthread

CXXFLAGS			=		-std=c++20 -Wall -Wextra -DASIO_STANDALONE -pthread

CPPFLAGS			=		-I ./include

CXX					=		g++

MV					=		mv

all: 	server	client

server:	$(OBJ_SERVER)
	$(CXX) -o $(NAME_SERVER) $(OBJ_SERVER) $(LDFLAGS)

client: $(OBJ_CLIENT)
	$(CXX) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LDFLAGS)

clean:
	$(RM) $(OBJ_SERVER)
	$(RM) $(OBJ_CLIENT)

fclean: clean
	$(RM) $(NAME_CLIENT)
	$(RM) $(NAME_SERVER)

debug:	CXXFLAGS += -g3
debug: re

re:	fclean all

.PHONY:	all clean fclean re
