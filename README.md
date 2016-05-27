# Simple-Scene-Renderer

A ray tracer built with C++. A lot of the code comes from *__Ray Tracing From The Ground Up__* -  [[site]](http://www.raytracegroundup.com/)

Check out the wiki for more images [https://github.com/nadr0/Simple-Scene-Renderer/wiki](https://github.com/nadr0/Simple-Scene-Renderer/wiki)

Features
-----

+ Lighting
    * Direct
    * Point
    * Area
    * Ambient
+ Ambient Occlusion
+ Materials
    * Matte
    * Phong
    * Reflective
    * Glossy reflections
    * Microfacet specular BRDF
      * [Original Cook-Torrance Paper](http://www.cs.columbia.edu/~belhumeur/courses/appearance/cook-torrance.pdf)
      * [Siggraph 2013, Physically Based Rendering course notes](http://blog.selfshadow.com/publications/s2013-shading-course/hoffman/s2013_pbs_physics_math_notes.pdf)
      * [Implementation/Source Code](http://ruh.li/GraphicsCookTorrance.html)
+ Primitives 
    * Sphere
    * Rectangle
    * Plane
    * Triangle
+ Tracers
    * Basic (non whitted)
    * Whitted
    * Path tracing (Global Illumination with Monte Carlo Method)
+ Bounding Volume Hierarchy (BVH)
    * Median split method
+ Fast Building of Orthonormal Basis
    * [Research paper](http://orbit.dtu.dk/files/57573287/onb_frisvad_jgt2012.pdf)
+ Smooth shaded triangles
    
More To Come!
=====
- depth of field
- non linear projections (fish eye)
- refraction
- instancing
- textures
- ambient occlusion
- updated .obj reader
- scene language
- SAH BVH method

-----

Rendered Images
----
Images below are created from path tracing with diffuse interreflections. 

![alt text](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/1sample.png "")

SPP|Image Size|Render Time|# Primitives
--- | --- | --- | ---
1|512x512|0.3 sec | 8

![alt text](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/2663%2C10k.png "")

SPP|Image Size|Render Time|# Primitives
--- | --- | --- | ---
10,000 |512x512| 44 mins | 8

![alt text](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/32789%2C100k.png "")

SPP|Image Size|Render Time|# Primitives
--- | --- | --- | ---
100,000 |512x512| 9.1 hours | 8

![alt text](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/24733%2C1k.png "")

SPP|Image Size|Render Time|# Primitives
--- | --- | --- | ---
1,000 |512x512| 6.8 hours | 5811

![alt test](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/9701%2C10k.png "")

SPP|Image Size|Render Time|# Primitives
--- | --- | --- | ---
10,000|512x512| 2.7 hours | 8

![alt test](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/8193%2C10k.png "")

SPP|Image Size|Render Time|# Primitives | Depth
--- | --- | --- | --- | ---
10,000 |512x512| 2.2 hours | 8 | 15
