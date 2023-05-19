# MiniRT
The MiniRT project is a minimalist ray-tracing engine built using fixed-point arithmetic in C. This compact yet powerful engine renders 3D scenes with realistic lighting and shadows, while leveraging the precision and performance benefits of fixed-point number representation. Designed with simplicity and efficiency in mind, MiniRT demonstrates the potential of ray-tracing techniques in resource-constrained environments, using the new updated Codam's version of the MLX42.

## This is a RayTracer in C
Made for UNIX systems, Linux and MacOs
- With implementation of fixed point numbers
- Reflexions
- Many shapes
    - Spheres
    - Cylinders
    - Planes
---
## Compile
`$>make` in main repo

---
##Controls
 - Drag and drop to move an object.
 - Toggle: appuyer sur la touche pour activer l'option correspondante et incrémenter avec + et -
        a = ambient +- pour modifier l'intensité
        l = light cliquer pour déplacer la lumière au curseur et +- pour avancer et reculer la lumière
        x,y et z pour activer l'axe
        o = orientation cela remplace la translation et effectue la rotation sur les axes selectionnées
        r = modifier le diamètre avec +-
        h = modifier la hauteur avec +-, valable seulement pour les cylindres
        c = caméra déplace sur l'axe x,y,z selon l'axe selection ou change l'orientation si "o" est activer
        

### With Graphic libraries GLFW and MLX42 from [Codam](https://github.com/codam-coding-college/MLX42)
### Made by :
- [ast-jean](https://github.com/ast-jean)

- [mtrembla](https://github.com/Zelxopi)

- [slavoie](https://github.com/Steven1659139)

