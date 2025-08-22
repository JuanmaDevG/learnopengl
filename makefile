.PHONY: clean

XLIBDIR = src/xlib


xlib-window: $(XLIBDIR)/window.c
	gcc $^ -lX11 -o $@

clean:
	rm xlib-window
