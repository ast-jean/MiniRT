# MiniRT <img src="img/grade.png" alt="grade" width="20"/>
![Phong demo](img/phong_demo.png)
The MiniRT project is a minimalist ray-tracing engine built using fixed-point arithmetic in C. This compact yet powerful engine renders 3D scenes with realistic lighting and shadows, while leveraging the precision and performance benefits of fixed-point number representation. Designed with simplicity and efficiency in mind, MiniRT demonstrates the potential of ray-tracing techniques in resource-constrained environments, using the new updated Codam's version of the MLX42[^1].
## This is a RayTracer in C
Made for UNIX systems, Linux and MacOs
- With implementation of fixed point numbers
- With Phong reflexion
- Paper style shapes with light passing through one side.
    - Spheres
    - Cylinders
    - Planes
## Compile
`$>make` in main repo
 - It will build the Codam's MLX42[^1] in the include repo depending on OS and detect if GLFW[^2] is installed. 
## Run
ex: `./miniRT scene/columns.rt`
## Controls
 - Toggle: Press a key to activate the toggled trigger, then increment with `+` or `-`.
 - Select an object, then change its properties
    - Click on a shape
        - Drag and drop to move an object on the Y and Z axis.
        - Toggle `x`, `y` and/or `z`, then `+` or `-` to change position.
        - Toggle `o` then `x`, `y` and/or `z` then `+` or `-` to change orientation.
        - Toggle `r` then `+` or `-` to change radius for the sphere and cylinder.
        - Toggle `h` then `+` or `-` to change height for the cylinder.
    - Press `a` to toggle the ambient light
        - Change the color red(`1`), green(`2`), blue(`3`).
        - `+` or `-` to change the light intensity.
    - Press `l` to toggle the light
        - Click anywhere to change its position on the Y and Z axis.
        - Toggle `x`, `y` and/or `z`, then `+` or `-` to change position.
        - Toggle `r` to change its radiance/brightness.
    - Press `c` to toggle the camera
        - Toggle `x`, `y` and/or `z`, then `+` or `-` to change position.
        - Toggle `o` then `x`, `y` and/or `z` then `+` or `-` to change orientation.
        - Toggle `f` then `+` or `-` to change field of view.
## Examples :
 - `phong_demo.rt`
 ![phong_demo](img/phong_demo.rt.png)
 - `columns.rt`
![columns](img/columns.rt.png)
 - `spot.rt`
![columns](img/spot.rt.png)
 - Why not cloud point data: `pcd.rt`
![pcd](img/pcd.rt.png)
### Made by :
- [ast-jean](https://github.com/ast-jean)

- [mtrembla](https://github.com/Zelxopi)

- [slavoie](https://github.com/Steven1659139)

[^1]:[Codam's MLX42: https://github.com/codam-coding-college/MLX42](https://github.com/codam-coding-college/MLX42)

[^2]:[GLFW used by Codam's MLX42: https://www.glfw.org/](https://www.glfw.org/)