# Pull Request Description

## Overview
This pull request implements a complete ray tracing engine for the miniRT project, featuring real-time rendering, multiple geometric shapes, lighting systems, and interactive camera controls.

## Features Implemented

### 🎨 Ray Tracing Engine
- **Viewport System**: Implemented viewport initialization and ray generation through camera space
- **Ray-Object Intersection**: Core ray tracing algorithm for detecting intersections with scene objects
- **Scene Rendering**: Main `shoot_rays()` function that iterates through viewport pixels and renders the scene

### 🔵 Geometric Objects
- **Sphere Intersection**: Full implementation of ray-sphere intersection using quadratic equation solving
- **Plane Intersection**: Ray-plane intersection with normal vector support
- **Cylinder Intersection**: Ray-cylinder intersection with height boundaries (WIP - Work in Progress)

### 💡 Lighting System
- **Ambient Lighting**: Global ambient light with configurable intensity and color
- **Point Lights**: Support for multiple colored point lights in the scene
- **Light Calculations**: Color multiplication and scaling for realistic lighting effects
- **Shadow Calculations**: Light occlusion detection for proper shadow rendering

### 🎮 Interactive Controls
- **Camera Movement**: 
  - Forward/Backward (W/S keys)
  - Left/Right (A/D keys)
  - Up/Down (C/Z keys)
  - Reset position (X key)
- **FOV Adjustment**: Mouse scroll support for field of view changes
- **Rendering Modes**:
  - High Quality (HQ) mode for detailed rendering
  - Low Quality (LQ) mode for improved performance during interaction
  - Toggle with R key

### 📄 Scene Parsing
- **RT File Format Support**: Parser for .rt scene description files
- **Scene Elements**:
  - Ambient light (A)
  - Camera (C) with position, orientation, and FOV
  - Lights (L) with position, intensity, and color
  - Spheres (sp) with center, diameter, and color
  - Planes (pl) with point, normal vector, and color
  - Cylinders (cy) with center, axis, diameter, height, and color

### 🧮 Mathematics & Utilities
- **Vector Operations**: Complete 3D vector library
  - Addition, subtraction, scaling
  - Dot product and cross product
  - Normalization and magnitude calculation
- **Color Operations**:
  - Color scaling and multiplication
  - Color addition with clamping
  - RGB color space handling

### 🧪 Testing Infrastructure
- **Unity Testing Framework**: Integrated Unity test framework for C
- **Comprehensive Test Coverage**:
  - Vector operations tests
  - Intersection algorithm tests
  - Rendering pipeline tests
  - Graphics and color tests
- **Test Structure**: Organized test files mirroring source code structure

## Technical Implementation

### Architecture
```
miniRT/
├── src/
│   ├── core/          # Core application logic and MLX integration
│   ├── render/        # Ray tracing and rendering pipeline
│   ├── intersect/     # Geometric intersection algorithms
│   ├── color/         # Color operations and utilities
│   ├── objects/       # Scene object definitions
│   ├── parsing/       # Scene file parser
│   ├── graphics/      # Graphics primitives
│   └── vec3/          # 3D vector mathematics
├── tests/             # Unity test suite
├── maps/              # Example scene files
└── libs/              # External libraries (MLX, libft, vectors)
```

### Key Algorithms
1. **Quadratic Equation Solver**: Used for sphere and cylinder intersections
2. **Viewport Ray Generation**: Converts 2D pixel coordinates to 3D rays through camera space
3. **Nearest Intersection**: Finds the closest object intersection along each ray
4. **Phong Lighting Model**: Combines ambient and diffuse lighting for realistic shading

## Code Quality

### Standards Compliance
- ✅ Follows 42 norm coding standards
- ✅ Doxygen-style function documentation
- ✅ Consistent naming conventions
- ✅ Memory leak prevention

### Testing
- ✅ Unit tests for all major functions
- ✅ Integration tests for rendering pipeline
- ✅ Test files follow source structure convention

## Example Scenes

The following scene files are included in `maps/`:
- `sphere.rt` - Multiple spheres with colored lights
- `sphere&planes.rt` - Combination of spheres and planes
- `cylinders.rt` - Cylinder demonstrations
- `dummy.rt` - Complex test scene

## Building and Running

```bash
# Build the project
make

# Run with a scene file
./miniRT maps/sphere.rt

# Build and run tests
make test
./run_tests
```

## Controls

| Key | Action |
|-----|--------|
| W | Move camera forward |
| S | Move camera backward |
| A | Move camera left |
| D | Move camera right |
| C | Move camera up |
| Z | Move camera down |
| X | Reset camera position |
| R | Toggle HQ/LQ rendering mode |
| Mouse Scroll | Adjust FOV |
| ESC | Exit application |

## Known Limitations

- Cylinder intersection is marked as WIP (Work in Progress)
- No support for textures or reflections yet
- Limited to Phong lighting model (no global illumination)

## Future Enhancements

Potential areas for future development:
- Complete cylinder intersection implementation
- Add cone and other geometric primitives
- Implement reflection and refraction
- Add texture mapping support
- Multi-threading for faster rendering
- Anti-aliasing for smoother edges

## Dependencies

- **MinilibX**: Graphics library for X11
- **libft**: Custom C standard library
- **vectors**: Custom vector mathematics library
- **Unity**: Testing framework for C

## Authors

- kbarru ([@kbarru](mailto:kbarru@student.42lyon.fr))
- abetemps ([@aB-temps](https://github.com/aB-temps))

## License

This project is part of the 42 school curriculum.
