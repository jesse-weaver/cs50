# Questions

## What's `stdint.h`?

It is a C header file to allow definition of exact width integer types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To allow us to define a very specific integer size which uses n bytes in memory.  This allows us to very specifically define the contents of a file

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE - 8 bits / 1 byte
DWORD - 32 bits / 4 bytes
LONG - 32 bits / 4 bytes
WORD - 16 bits / 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

LONG bfType "MB" which actually BM, but reversed


## What's the difference between `bfSize` and `biSize`?

biSize
The number of bytes required by the structure.

bfSize
The size, in bytes, of the bitmap file.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount
The number of bits-per-pixel.

## Why might `fopen` return `NULL` in `copy.c`?

If no file is found at the specified location

## Why is the third argument to `fread` always `1` in our code?

Because we only want to read a specific amount of bytes for each portion of the file before we move to the next set of bytes.  This will prevent any unforseen issues with pulling data for a given chunk that shouldn't be there.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

Fseek moves to the location of the file pointer to the location specified to read the next set of bytes

## What is `SEEK_CUR`?

Seek current is the current location of the file pointer in the file referenced
