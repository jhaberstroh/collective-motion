.PHONY += GUI

%/module.pri: %/module.mk
	qtgui/genqt_include.sh $^
