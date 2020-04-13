BIN=~/code/gbdk-n/bin
OBJ=./obj



build:
	mkdir -p $(OBJ)
	cd image-tool && make && ./tool > ../image.h
	$(BIN)/gbdk-n-compile.sh demoboy.c -o $(OBJ)/demoboy.rel
	$(BIN)/gbdk-n-link.sh $(OBJ)/demoboy.rel -o $(OBJ)/demoboy.ihx
	$(BIN)/gbdk-n-make-rom.sh -yc $(OBJ)/demoboy.ihx demoboy.gbc

clean:
	rm -rf $(OBJ)
	rm -f demoboy.gbc
	rm -f image.h