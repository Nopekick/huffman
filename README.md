# Huffman Decoder

## Important: this program is still a bit buggy on larger files

## Descriptions of Huffman Encoding

Wikipedia: https://en.wikipedia.org/wiki/Huffman_coding

Nachenberg's slides: https://drive.google.com/drive/folders/1mINni4Vn-NQVrqT7tmVwswmm46MB34TS

## Usage

First run this to generate executable
```bash
make
```
or
```bash
g++ main.cpp encode.cpp decode.cpp -o main
```


To encode:
```bash
./main -e input-file output-file
```

To decode:
```bash
./main -d input-file output-file
```


To remove .o files generated from 'make':
```bash
make clean
```

This program currently assumes that the input file for decoding
was encoded by the same program. Using a random file as the input file
for decoding will cause undefined behavior.

Additionally, for small input files, the resulting compressed output 
file may be larger. The compression is more effective on 
larger text files. 

## Possible TODOS:

TODO: optimize tree building with priority queue

TODO: better encoding of huffman tree

