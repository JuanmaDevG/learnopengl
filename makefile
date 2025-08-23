.PHONY: clean

XLIBDIR = xlib


xlib-window: $(XLIBDIR)/window.c
	gcc $^ -lX11 -o $@

clean:
	rm xlib-window
