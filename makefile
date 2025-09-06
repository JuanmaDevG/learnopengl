.PHONY: clean

VANILLA_DIR=using-glfw-glew

COMPILER_FLAGS = -lX11 -lpthread -lXi -lXrandr -lGL -lGLEW -lglfw3
COMPILE_SINGLE_C_FILE = gcc -o $@ $< $(COMPILER_FLAGS)


triangle: $(VANILLA_DIR)/$@.c
	$(COMPILE_SINGLE_C_FILE)

clean:
	rm $(build_dir)/*
