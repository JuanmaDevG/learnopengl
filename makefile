.PHONY: clean

VPATH=src
BUILD_DIR:=build

EXECUTABLES:= triangle triforce colored_triforce

COMPILER:=gcc
FLAGS:= -g -Wall -Werror
LIBRARIES:= -lX11 -lpthread -lXi -lXrandr -lGL -lGLEW -lglfw

_TARGETS:=$(addprefix $(BUILD_DIR)/, $(EXECUTABLES))
all: $(BUILD_DIR) $(_TARGETS)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%: %.c
	$(COMPILER) -o $@  $< $(FLAGS) $(LIBRARIES)

clean:
	rm -r $(BUILD_DIR)
