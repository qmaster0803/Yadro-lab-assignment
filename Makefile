all:
	mkdir -p build/
	gcc src/writer.c -o build/writer
	gcc src/reader.c -o build/reader
