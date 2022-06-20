# PNG to Raw images converter

I've developed it for myself - to convert PNGs to RAW images on my Apollo V4 computer(amiga compatible).

It builds with vbcc(for amiga) via simple command: 

```
vc -lamiga -lauto -c99 -O2 +aos68k lodepng.c main.c -o pngconv
```

Or you can just grab binary from release page.

## How to use it?

Just run this command via shell(on AmigaOS/ApolloOS) - it will print usage to console:

```
PNG to SAGA raw chunks converter by Nihirash
v.1.0 21 Jun 2022
usage: pngconv MODE input.png output.raw
 Where MODE is:
  * 888 - RGB888
  * A888 - ARGB888
  * 565 - RGB565
  * 555 - RGBA555
  ```