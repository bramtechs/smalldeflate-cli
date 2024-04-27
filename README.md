# smalldeflate cli

Command line interface to `sdefl` and `sinfl`, the compression
libraries used in [Raylib](https://github.com/raysan5/raylib).

Can be called from other programming languages as a process to make
asset package formats and such...

## Usage
```sh
cat img.jpg | smalldeflate > img.dat
cat img.dat | smallinflate > img2.jpg

cat sample.txt | smalldeflate > sample.dat
cat sample.dat | smallinflate > sample2.txt
```

> Note: Both commands use stdin and stdout, so pipe and redirect accordingly!
