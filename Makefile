BIN=~/code/gbdk-n/bin
OBJ=./obj



build:
	mkdir -p $(OBJ)
	$(BIN)/gbdk-n-compile.sh galaxy.c -o $(OBJ)/galaxy.rel
	$(BIN)/gbdk-n-link.sh $(OBJ)/galaxy.rel -o $(OBJ)/galaxy.ihx
	$(BIN)/gbdk-n-make-rom.sh -yc $(OBJ)/galaxy.ihx galaxy.gbc

clean:
	rm -rf $(OBJ)
	rm -f galaxy.gbc
