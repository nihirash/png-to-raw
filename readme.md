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
v.1.1 23 Jul 2022
usage: pngconv MODE NOISE input.png output.raw
 Where MODE is:
  * 888 - RGB888
  * A888 - ARGB888
  * 565 - RGB565
  * 555 - RGBA555
 Where NOISE is:
  * N - add no noise
  * Y - add noise

  ```

  Noise adding allows get better results when you converting images with losing bit depth.