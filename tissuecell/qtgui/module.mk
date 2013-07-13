.PHONY += GUI

GUI: $(patsubst %, %/module.mk, $(MODULES))

%/module.qt: %/module.mk
	./genqt_include.sh $^
