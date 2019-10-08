CXX			=	g++
RM			=	rm -f
PRINT		=	printf

NAME		=	bomberman

CXXFLAGS	+=	-Wall -Wextra
CXXFLAGS	+=	-D_GLIBCXX_USE_CXX11_ABI=0
CXXFLAGS	+=	-I ./include/ -I ./libgdl_gl/include/
CXXFLAGS	+=	`xml2-config --cflags`

LXXFLAGS	+=	-L ./libgdl_gl/lib/ -Wl,--rpath=./libgdl_gl/lib/ -lgdl_gl -lGL -lGLU
LXXFLAGS	+=	-lsfml-audio
LXXFLAGS	+=	`xml2-config --libs`

SRCS		=	Player.cpp				\
				Editor.cpp				\
				Map.cpp					\
				WindowEngine.cpp		\
				InputEngine.cpp			\
				ClockEngine.cpp			\
				AudioEngine.cpp			\
				ConfigEngine.cpp		\
				GameEngine.cpp			\
				IntroEngine.cpp			\
				MenuEngine.cpp			\
				EnginesManagement.cpp	\
				XmlEngine.cpp			\
				Vector3f.cpp			\
				Case.cpp				\
				Floor.cpp				\
				Box.cpp					\
				Wall.cpp				\
				Skybox.cpp				\
				Bomb.cpp				\
				AiEngine.cpp			\
				Fire.cpp				\
				main.cpp				\
				Bonus.cpp				\
				Hardbox.cpp				\
				Brain.cpp				\
				Common.cpp

OBJS		=	$(SRCS:.cpp=.o)

$(NAME)		:	$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) $(LXXFLAGS)
				@$(PRINT) "\033[32m*** Compilation of binary $(NAME) done ***\n\033[00m"

all			:	$(NAME)

clean		:
				$(RM) $(OBJS)
				$(RM) *~ \#*\#
				@$(PRINT) "\033[31m*** Objects are removed ***\n\033[00m"

fclean		:	clean
				$(RM) $(NAME)
				@$(PRINT) "\033[31m*** Binary $(NAME) is removed ***\n\033[00m"

re			:	fclean all

.PHONY		:	all clean fclean re