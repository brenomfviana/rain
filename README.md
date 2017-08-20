# RAIN

## Description

Rain is an image renderer that uses the [_ray tracing_](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)) technique.

### About

This image renderer is a project of Computer Graphics course of the Federal University of Rio Grande do Norte (UFRN).

The name rain is an acronym for **RA**y trac**IN**g.

## Features and TO DOs

- [ ] Scene
  - [x] Scene reader
  - [x] Scene components
  - [ ] Camera

- [x] Printer
  - [x] ASCII
  - [x] Binary
  - [ ] Choose location to save the image file
  - [ ] Supported image file formats
    - [x] PPM
    - [ ] BMP
    - [ ] JPG
    - [ ] PNG
    - [ ] TIFF
    - [ ] GIF

- [ ] Shapes
  - [x] Sphere
  - [ ] Cube
  - [ ] Cuboid
  - [ ] Cone
  - [ ] Cylinder

- [ ] Materials
  - [ ] Diffuse
  - [ ] Metal
  - [ ] Glass
  - [ ] Blur

- [ ] Light

- [ ] Texture

## Dependencies

- C++11

## How to compile

Use the ```make``` command to compile the renderer.

## How to use

Choose a scene and run the renderer passing the file path of the scene as an argument to render an image.

```bash
# ./render scenefile.txt
./render hello-rain.txt
```

## Scene file format

#### Hello rain

```txt
NAME: hello-rain.ppm
TYPE: PPM
CODIFICATION: ascii # or binary
WIDTH: 200
HEIGHT: 100
BACKGROUND:
    UPPER_LEFT: 0 255 0    # Upper left corner color  (green)
    LOWER_LEFT: 0 0 0      # Lower left corner color  (black)
    UPPER_RIGHT: 255 255 0 # Upper right corner color (yellow)
    LOWER_RIGHT: 255 0 0   # Lower right corner color (red)
```

#### Sky background

```txt
NAME: sky.ppm
TYPE: PPM
CODIFICATION: binary # or ascii
WIDTH: 200
HEIGHT: 100
BACKGROUND:
    UPPER_LEFT: 128 179 255  # Upper left corner color
    LOWER_LEFT: 255 255 255  # Lower left corner color
    UPPER_RIGHT: 128 179 255 # Upper right corner color
    LOWER_RIGHT: 255 255 255 # Lower right corner color
```

## Author

[<img src="https://avatars2.githubusercontent.com/u/17532418?v=3&s=400" width="100"/>](https://github.com/brenov) |
---|
[Breno Viana](https://github.com/brenov) |
