.PHONY: clean

XLIBDIR = xlib

all: window window-info atoms

window: $(XLIBDIR)/window.c
	gcc $^ -lX11 -o $@

attributes: $(XLIBDIR)/info.c
	gcc $^ -lX11 -o $@

atoms: $(XLIBDIR)/atoms.c
	gcc $^ -lX11 -o $@

properties: $(XLIBDIR)/properties.c
	gcc $^ -lX11 -o $@

clean:
	rm window attributes atoms properties
