#######################################
# Author :ponlee
# Date : 2014-5-12
# Desc : 通用静态库、动态库生成makefile
#######################################

AR=ar -rc

CFLAGS = -g -Wall -fPIC -Wno-deprecated -Wno-non-template-friend

INC = -I./ -I./src/ -I./ThirdParty/
LIB = -L./
SRC_DIR=./src/

SUBSRC=$(wildcard ./src/*.cpp)
SUBOBJ=$(patsubst %.cpp, %.o, $(SUBSRC))

LIB_OBJ=libbase.a
BIN_OBJ=libbase.so

all:$(LIB_OBJ) $(BIN_OBJ)

$(LIB_OBJ):$(SUBOBJ)
	rm -f $@
	$(AR)  $(LIB_OBJ) $^ $(OBJS)
	mv $(LIB_OBJ) ./lib/

$(BIN_OBJ):$(SUBOBJ)
	rm -f $@
	g++  -shared  $(CFLAGS) -o $(BIN_OBJ) $^
	mv $(BIN_OBJ) ./lib/

%.o: %.cpp
	g++ $(CFLAGS) $(INC) -c -o $@ $<
%.o: %.c
	gcc $(CFLAGS) $(INC) -c -o $@ $<
	
clean:
	rm $(SUBOBJ)
	rm -f ./lib/*

