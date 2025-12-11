# miniRT
This repository contains an archive of the project `miniRT` realised for the completion of 42's common core.

## Installation
The graphics library used for this project, `mlx`, is included in the repository. A simple `make` at the root of the repo should generate the executable, with platform detection (only works with Linux or MacOS).

## Usage
Run `./miniRT` with a scene of your choice. Scenes are custom parameter files located in directory `scenes/`. File `scenes/template.rt` shows different possibilities for each shape.

## Features
`miniRT` can display cones, spheres, cylinders, and planes. Reflective lighting, in this project, is technically infinite so the user can specify the maximum number of recursions used when calcultating reflective lighting, as a flag in variable `CFLAGS` of the Makefile. It is set at 2 by default. An example can be found below.
1) Camera parameters can be adjusted: FOV, position in 3D space...
2) Ambient lighting can be adjusted: colour (RGB), intensity...
3) Light sources can be specified: position, colour (RGB), intensity...

- The raytracer can display ambient lighting, specular lighting (Phong reflection model), as well as reflective lighting.
- XPM files can be 'attached' to objects, for example scene `solar_system.rt` shows different planet textures on sphere objects.
- Checkerboard pattern can also be attached to an object. See `reflection_demo.rt` for a full example.
- Bump map textures are also supported, though this feature is more experimental since bumps are determined from .xpm files alone using differences in grey levels. This makes the
bumps relatively inaccurate. See `brick_bumps.rt` for an example of bump maps, or the example below.

|`brick_bumps.rt` with `bump=on`| `brick_bumps.rt` with `bump=off`|
|---|---|
|<img width="899" height="523" alt="Screenshot 2025-12-11 at 16 01 56" src="https://github.com/user-attachments/assets/1c9eeac0-fded-49e0-9bcd-1a906b64d1ac" />|<img width="900" height="519" alt="Screenshot 2025-12-11 at 15 59 33" src="https://github.com/user-attachments/assets/c3f60487-9d46-4ebc-9251-1f6b103141e8" />
|`mirrored_sphere_cone.rt` with `REFLECTION_RECURSIONS=10`|`mirrored_sphere_cone.rt` with `REFLECTION_RECURSIONS=1`|
|<img width="900" height="519" alt="Screenshot 2025-12-11 at 16 09 45" src="https://github.com/user-attachments/assets/836b8bbd-6479-47d7-b84a-1f204028ee3b" />|<img width="897" height="520" alt="Screenshot 2025-12-11 at 16 10 47" src="https://github.com/user-attachments/assets/aa44f60d-25c8-47a0-acc0-f16c09330843" />|
|`reflections_demo.rt` with `REFLECTION_RECURSIONS=5`, all objects with non-zero reflective lighting|`reflections_demo.rt` with `REFLECTION_RECURSIONS=5`, all objects with reflective lighting set to zero|
|<img width="901" height="524" alt="Screenshot 2025-12-11 at 16 12 39" src="https://github.com/user-attachments/assets/e415ff32-edf2-4396-b744-a856e41c75d2" />|<img width="901" height="521" alt="Screenshot 2025-12-11 at 16 15 10" src="https://github.com/user-attachments/assets/999c686c-de05-4f1f-bc77-c55e866445aa" />|
