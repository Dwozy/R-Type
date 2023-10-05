##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## makefile
##

SRC_SERVER			= 		server/src/main.cpp	\
							server/src/UdpServer.cpp	\
							server/src/TcpServer.cpp	\
							server/src/ClientSession.cpp

SRC_CLIENT			= 		client/src/main.cpp	\
							client/src/UdpClient.cpp	\
							client/src/TcpClient.cpp

OBJ_SERVER			=		$(SRC_SERVER:.cpp=.o)

OBJ_CLIENT			=		$(SRC_CLIENT:.cpp=.o)

NAME_SERVER			=		r-type_server

NAME_CLIENT			=		r-type_client

LDFLAGS				=		-pthread

LIBFLAGS			=		-lboost_serialization

CXXFLAGS			=		-std=c++20 -Wall -Wextra

CPPFLAGS			=		-I ./include/Server \
							-I ./include/Client	\
							-I ./include

CXX					=		g++

MV					=		mv

all: 	server	client

server:	$(OBJ_SERVER)
	$(CXX) -o $(NAME_SERVER) $(OBJ_SERVER) $(LDFLAGS) $(LIBFLAGS)

client: $(OBJ_CLIENT)
	$(CXX) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LDFLAGS) $(LIBFLAGS)

clean:
	$(RM) $(OBJ_SERVER)
	$(RM) $(OBJ_CLIENT)

fclean: clean
	$(RM) $(NAME_CLIENT)
	$(RM) $(NAME_SERVER)

debug: CXXFLAGS += -g3
debug: re

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY:	all clean fclean re