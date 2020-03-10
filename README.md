# PTLib

PTLib is a library for the rendering of path traced scenes and objects. 

Currently, the library is limited to the tracing of spheres. Other object types such as cubes and meshes are in the works.

PTLib uses OpenMP by default. Be sure the development library is installed, and a supported compiler version is used. Alternatively, build without OpenMP as shown.
```bash
make OPENMP=0
```

### Traceable Objects
PTLib defines every object as a traceable structure. Current, and planned traceables are shown below.
* Spheres (Implemented)
* Triangular Meshes (In Progress)
* Cubes (Planned)

### Custom Traceable Objects
New objects can be added by providing a properly configured traceable structure. This structure must be configured with:
* A pointer to a function to find the normal vector of any given point.
* A pointer to a function to find the distance to any given point on the object's surface.
* Object properties such as position, emission, color, and material. 

For a sphere, these functions can be found in ptl_sphere.c.

Any properties that need to be stored within the object that do not conform to any of the standard members of a traceable should be stored in the traceable's *properties* data structure. By default, this consists of 9 values accessible as *v1* to *v9*. This data can also be accessed as an array by reading values from *values*.

### PTLib Scene File
PTLib can load scenes from a scene file (.pts). A scene file is a simple text file describing a single traceable object on each line. Comments may be added with # if desired.

The format is as follows.

```html
<Type> [Position <x> <y> <z>] [Emission <r> <g> <b>] [Color <r> <g> <b>] <Material> [Properties (optional) <p1>...<p9>]
```

For example, a matte, reddish sphere with a radius of 23.5, at position (10.2, 0, 0) might be:
```c
SPHERE    10.2 0 0    0 0 0    0.75 0.3 0.3   MAT_DIFFUSE    23.5    
```
**Note**: A sphere's radius is stored within it's p1 property.


## Installation

Clone this repo, then enter the *ptlib* directory.
```bash
git clone git@github.com:Techmo2/ptlib.git
cd ptlib/ptlib
```
Run make to build and install the library.

```bash
make
sudo make install
```

## Usage
An example is provided in the *test* folder. 

Build and run the example after installing PTLib using:
```bash
cd test
make
./ptlib-test
```

The result will be written to *output.bmp*.

## License
[MIT](https://choosealicense.com/licenses/mit/)