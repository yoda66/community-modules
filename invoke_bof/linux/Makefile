all:
	make -f Makefile.linux32; mv src/invoke_bof.d obj/x86; mv src/invoke_bof.o obj/x86
	make -f Makefile.linux64; mv src/invoke_bof.d obj/x64; mv src/invoke_bof.o obj/x64
	cd src/artifacts; zip -FSr ../../bin/package.zip *; cd ../../bin; zip -r package.zip linux/*

clean:
	make -f Makefile.linux32 clean
	make -f Makefile.linux64 clean
	rm -f bin/package.zip
