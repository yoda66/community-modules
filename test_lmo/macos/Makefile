all:
	rm -rf bin; mkdir -p bin/macos/x64; cd src/artifacts; zip -FSr ../../bin/package.zip *; cd ../py; zip -FSr ../../bin/macos/x64/test_lmo.zip *; cd ../../bin; zip -r package.zip macos; mv macos/x64 .; rmdir macos
