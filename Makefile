default: default

%:
	make -f Makefile_x86 $@
	make -f Makefile_x86-64 $@
