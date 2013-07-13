.PHONY += GUI

%/module.pri: qtgui/genqt_include.sh %/module.mk
	qtgui/genqt_include.sh $^
