.PHONY: clean

# TODO: make file more generic

XLIBDIR = xlib

all: window attributes atoms properties selections

window: $(XLIBDIR)/window.c
	gcc $^ -lX11 -o $@

attributes: $(XLIBDIR)/info.c
	gcc $^ -lX11 -o $@

atoms: $(XLIBDIR)/atoms.c
	gcc $^ -lX11 -o $@

properties: $(XLIBDIR)/properties.c
	gcc $^ -lX11 -o $@

graphics-context: $(XLIBDIR)/graphics_context.c
	gcc $^ -lX11 -o $@

clean:
	rm window attributes atoms properties graphics-context
