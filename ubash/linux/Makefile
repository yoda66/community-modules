all:
	make -f Makefile.linux32; mv src/ubash.d obj/x86; mv src/ubash.o obj/x86
	make -f Makefile.linux64; mv src/ubash.d obj/x64; mv src/ubash.o obj/x64
	cd src/artifacts; zip -FSr ../../bin/package.zip *; cd ../../bin; zip -r package.zip linux/*

clean:
	make -f Makefile.linux32 clean
	make -f Makefile.linux64 clean
	rm -f bin/package.zip
