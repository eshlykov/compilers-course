# MiniJava Compiler

## Build

[![Travis (.org)](https://img.shields.io/travis/eshlykov/compilers-course.svg)](https://travis-ci.org/eshlykov/compilers-course)

## Code

In this section we'll briefly cover the main aspects of the code.

### AST

Everything connected to AST (Abstract Syntax Tree) lies in [ast](ast).

### IRT

Everything connected to IRT (Intermediate Representation Tree) lies in [irt](irt).

## Prerequisites

Code is written in C++17. Compilation is done via clang-7.0.1.  
For correct work of everything we suggest you to have the following:
* [bison](https://www.gnu.org/software/bison/) (parser)
* [flex](https://www.gnu.org/software/flex/) (lexical analyser)
* [valgring](http://www.valgrind.org) (used for leaks detection)
* Python3 (used for management scripts)

## References

Useful links:
* [List of tokens](https://docs.google.com/document/d/1I_kbg815RdBgth_w0F04MJiE72xIur6C-6QKBIEQnL4/edit)
* [MiniJava grammar](https://docs.google.com/document/d/1Pwhxt5oOrkgJwLB8MpaphhnbXTEM8EBW6NY9ONCl7ho/edit)
* [Course's Google Drive](https://drive.google.com/drive/u/0/folders/1Q7nlEMtqZIvuYCEbITspLKm4TuCq4KLL)

## Team

This compiler was written by 3 programmers:
* [Evgeny Shlykov](https://github.com/eshlykov)
* [Evgeny Rubanenko](https://github.com/svinkapeppa)
* [Mikhail Anukhin](https://github.com/clumpytuna)

## Acknowledgements

Thanks to our lecturer Victor Zhuravlev.
