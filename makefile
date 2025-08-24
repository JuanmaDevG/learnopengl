.PHONY: clean

XLIBDIR = xlib


window: $(XLIBDIR)/window.c
	gcc $^ -lX11 -o $@

clean:
	rm window
