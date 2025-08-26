.PHONY: clean

XLIBDIR = xlib


window: $(XLIBDIR)/window.c
	gcc $^ -lX11 -o $@

window-info: $(XLIBDIR)/window-info.c
	gcc $^ -lX11 -o $@

clean:
	rm window window-info
