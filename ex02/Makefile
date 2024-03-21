VPATH		:= src:
NAME		:= PmergeMe
CXXFLAGS	?= -Wall -Wextra -Werror -std=c++20
LDFLAGS		?=
OBJECTS		:=	obj/main.o \
                obj/PmergeMe.o
HEADERS		:=  PmergeMe.hpp
INCLUDE		:= -I./include

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

obj/%.o : %.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) -o $@ $<

clean :
	$(RM) -r obj

fclean : clean
	$(RM) $(NAME)

re : fclean all

docker-pwd-san:
	docker run \
	-it \
	--rm \
	--init \
	-v "$$PWD:/pwd" \
	--cap-add=SYS_PTRACE \
	--security-opt seccomp=unconfined \
	-e CXX="clang++" \
	-e CXXFLAGS="-std=c++20 -Wall -Wextra -O1 -g -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer" \
	-e LDFLAGS="-g -fsanitize=address -fsanitize=leak" \
	ubuntu-c-plus sh -c "cd /pwd; bash"

docker-pwd-val:
	docker run \
	-it \
	--rm \
	--init \
	-v "$$PWD:/pwd" \
	--cap-add=SYS_PTRACE \
	--security-opt seccomp=unconfined \
	-e CXX="clang++" \
	-e CXXFLAGS="-std=c++20 -Wall -Wextra -g -gdwarf-4 -gstrict-dwarf" \
	-e LDFLAGS="-g -gdwarf-4 -gstrict-dwarf" \
	ubuntu-c-plus sh -c "cd /pwd; bash"

docker-pwd:
	docker run \
	-it \
	--rm \
	--init \
	-v "$$PWD:/pwd" \
	--cap-add=SYS_PTRACE \
	--security-opt seccomp=unconfined \
	-e CXX="clang++" \
	-e CXXFLAGS="-std=c++20 -Wall -Wextra" \
	ubuntu-c-plus sh -c "cd /pwd; bash"

.PHONY	: clean fclean re docker-pwd-san docker-pwd-val docker-pwd
