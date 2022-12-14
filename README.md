# c_plot

C library for plotting figures.

## Trees

![Example video of tree drawn on polar coordinates grid](img/demo.gif)

<!-- <div style="display:flex;width:100%;">
<img src="img/tree.png" alt="example image of tree drawn on polar coordinates grid" width="49%%" />
<img src="img/tree2.jpeg" alt="example image of tree drawn on polar coordinates grid" width="49%" />
<img src="img/tree3.jpeg" alt="example image of tree drawn on polar coordinates grid" width="49%" />
<img src="img/tree4.jpeg" alt="example image of tree drawn on polar coordinates grid" width="49%" />
</div> -->

## Functions

![Example image of functions drawn on cartesian coordinates grid](img/fn.png)

## Setup (Linux)

```shell
$ sudo apt-get update
$ sudo apt-get install libsdl2-2.0-0 libsdl2-dbg libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dbg libsdl2-image-dev
```

> obs: in case you get the following errors
> E: Unable to locate package libsdl2-dbg
> E: Unable to locate package libsdl2-image-dbg
> it will still be possible to run the examples

## Compiling and running

```shell
$ make
$ ./main
```

## References

SDL documentation: http://wiki.libsdl.org/CategoryInit

SDL tutorial (with setup): https://www.youtube.com/watch?v=yFLa3ln16w0&ab_channel=CS50
