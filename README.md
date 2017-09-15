# RAIN

## Description

Rain is an image renderer that uses the [_ray tracing_](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)) technique.

### About

This image renderer is a project of Computer Graphics course of the Federal University of Rio Grande do Norte (UFRN).

The name rain is an acronym for **RA**y trac**IN**g.

## Features and TO DOs

- [ ] Ray Tracer
  - [x] Anti-aliasing
  - [ ] Shaders
    - [x] Background
    - [x] Normal 2 RGB
    - [x] Depth Map
    - [x] Blinn-Phong
    - [ ] Lambertian

- [ ] Scene
  - [x] Scene reader
  - [ ] Scene components
    - [ ] Light
      - [x] Directional Light
      - [ ] Point Light
    - [ ] Shapes
      - [x] Sphere
      - [ ] Flat
      - [ ] Cube
      - [ ] Cuboid
      - [ ] Cone
      - [ ] Cylinder
      - [ ] Materials
        - [x] Diffuse
        - [x] Metal
        - [ ] Dielectrics
        - [ ] Texture
  - [ ] Camera
    - [ ] Perspective
    - [ ] Orthogonal

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

#### Hello rain (Just background)

```txt
# Output settings
NAME: hello-rain.ppm
TYPE: PPM
CODIFICATION: ascii # or binary
WIDTH: 200
HEIGHT: 100
# Ray Tracer Settings
SAMPLES: 100 # Number of samples for anti-aliasing
RAYS:    100 # Number of rays of the recursion
# Camera
CAMERA:
    LLC: -2 -1 -1 # Lower left corner of the view plane
    H: 4 0 0      # Horizontal dimension of the view plane
    V: 0 2 0      # Vertical dimension of the view plane
    O: 0 0 0      # The camera's origin
# Scene description
SHADER:
    BACKGROUND
BACKGROUND:
    UPPER_LEFT: 0 1 0  # Upper left corner color  (green)
    LOWER_LEFT: 0 0 0  # Lower left corner color  (black)
    UPPER_RIGHT: 1 1 0 # Upper right corner color (yellow)
    LOWER_RIGHT: 1 0 0 # Lower right corner color (red)

```

#### Blinn-Phong Shader

```txt
# Output settings
NAME: blinn_phong2.ppm
TYPE: PPM
CODIFICATION: binary # or ascii
WIDTH: 1200
HEIGHT: 600
# Ray Tracer Settings
SAMPLES: 100 # Number of samples for anti-aliasing
RAYS:    100 # Number of rays of the recursion
# Camera
CAMERA:
    LLC: -2 -1 -1 # Lower left corner of the view plane
    H: 4 0 0      # Horizontal dimension of the view plane
    V: 0 2 0      # Vertical dimension of the view plane
    O: 0 0 0      # The camera's origin
# Scene description
SHADER:
    BLINNPHONG
    AMBIENT_LIGHT: 0.4 0.4 0.4
BACKGROUND:
    TOP: 0.5 0.7 1 # Top color
    BOTTOM: 1 1 1  # Bottom color
COMPONENTS:
    LIGHT:
        DIRECTION: -8 7 0
        INTENSITY: 0.8 0.8 0.8
    LIGHT:
        DIRECTION: 20 10 15
        INTENSITY: 0.5 0.5 0.5
    SPHERE:
        ORIGIN: 0 -100.5 -1
        RADIUS: 100
        BLINN_PHONG_MATERIAL:
            KA: 0.1 0.1 0.1
            KD: 0.8 0.8 0.8
            KS: 0 0 0
            P: 64
    SPHERE:
        ORIGIN: 0 0 -1
        RADIUS: 0.5
        BLINN_PHONG_MATERIAL:
            KA: 0.1 0.1 0.1
            KD: 0.7 0.2 0.1
            KS: 1 1 1
            P: 64

```

## Author

[<img src="https://avatars2.githubusercontent.com/u/17532418?v=3&s=400" width="100"/>](https://github.com/brenov) |
---|
[Breno Viana](https://github.com/brenov) |
