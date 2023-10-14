##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## makefile
##

SRC_SERVER			= 		server/src/main.cpp	\
							R-Type-server/src/UdpServer.cpp	\
							R-Type-server/src/TcpServer.cpp	\
							R-Type-server/src/ClientSession.cpp	\
							R-Type-server/src/RTypeServer.cpp	\
							GameEngine/src/Error.cpp	\
							GameEngine/src/DeltaTime.cpp	\
							GameEngine/src/systems/ControlSystem.cpp	\
							GameEngine/src/systems/DrawSystem.cpp	\
							GameEngine/src/systems/PositionSystem.cpp	\
							GameEngine/src/Network/server/ACommunication.cpp	\
							GameEngine/src/systems/CollisionSystem.cpp	\
							GameEngine/src/systems/PressableSystem.cpp	\
							GameEngine/src/SceneManager.cpp	\

SRC_CLIENT			= 		client/src/main.cpp	\
							client/src/UdpClient.cpp	\
							client/src/TcpClient.cpp	\
							GameEngine/src/Network/server/ACommunication.cpp

OBJ_SERVER			=		$(SRC_SERVER:.cpp=.o)

OBJ_CLIENT			=		$(SRC_CLIENT:.cpp=.o)

NAME_SERVER			=		r-type_server

NAME_CLIENT			=		r-type_client

LDFLAGS				=		-pthread -lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS			=		-std=c++20 -Wall -Wextra -g3

CPPFLAGS			=		-I ./include/Client	\
							-I ./GameEngine/include	\
							-I ./GameEngine/include/Network/Server/	\
							-I ./R-Type-server/include	\
							-I ./R-Type/include	\

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

debug: CXXFLAGS += -g3
debug: re

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY:	all clean fclean re
