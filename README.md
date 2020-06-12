# Huffman Decoder

## Descriptions of Huffman Encoding

Wikipedia: https://en.wikipedia.org/wiki/Huffman_coding

Nachenberg's slides: https://drive.google.com/drive/folders/1mINni4Vn-NQVrqT7tmVwswmm46MB34TS

## Usage

First run this to generate executable
```bash
make
```

To encode:
```bash
./main -e input-file output-file
```

To decode:
```bash
./main -d input-file output-file
```

Note: this program currently assumes that the input file for decoding
was encoded by the same program. Using a random file as the input file
for decoding will cause undefined behavior. Also, output files should
be empty or nonexistent files.


## Possible TODOS:

TODO: fix padding issue on decode

TODO: calculate file size before and after compression/encoding

TODO: optimize tree building with priority queue

TODO: wipe output files to be careful

TODO: check for empty input files
