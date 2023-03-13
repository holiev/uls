.PHONY = all clean uninstall reinstall

TARGET := ULS
LIBS :=  ./libmx/libmx.a
BIN := uls
CC = clang -std=c11  -Wall -Wextra -Wpedantic  #compiler -std=c11
SOURCE := $(wildcard src/*.c)
HEAD := $(wildcard inc/*.h)
OBJECTS = $(addprefix obj/,$(notdir $(SOURCE:.c=.o)))

all: $(OBJECTS) $(TARGET) 

$(TARGET): $(SOURCE) $(OBJECTS) $(HEAD)
	@make -C ./libmx
	@$(CC) -o $(BIN) $(OBJECTS) $(LIBS)

obj/%.o: src/%.c $(HEAD)
	@mkdir -p obj 
	@$(CC) -c $< -o $@

uninstall: clean
	@rm -f $(BIN)

clean:
	@rm -drf obj
	@rm -f $(wildcard *.o)

reinstall: uninstall $(TARGET)

