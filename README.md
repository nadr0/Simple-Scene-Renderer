# Simple-Scene-Renderer

A ray tracer built with C++. A lot of the code comes from *__Ray Tracing From The Ground Up__* -  [[site]](http://www.raytracegroundup.com/)

Features
-----

+ Lighting
    * Direct
    * Point
    * Area
+ Materials
    * Matte
    * Phong
    * Reflective
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
    
More To Come!
=====
- depth of field
- non linear projections (fish eye)
- refraction
- instancing
- ~~glossy reflections~~
- textures
- ambient occlusion
- ~~smooth shaded triangles~~
- updated .obj reader
- scene language
- SAH BVH method
- ~~Microfacet specular BRDF~~
   * [Original Cook-Torrance Paper](http://www.cs.columbia.edu/~belhumeur/courses/appearance/cook-torrance.pdf)
   * [Siggraph 2013, Physically Based Rendering course notes](http://blog.selfshadow.com/publications/s2013-shading-course/hoffman/s2013_pbs_physics_math_notes.pdf)
   * [Implementation/Source Code](http://ruh.li/GraphicsCookTorrance.html)

-----

Rendered Images
----
Images below are created from path tracing with diffuse interreflections. 

![alt text](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/1sample.png "")
* 512x512
* 1 sample per pixel
* 0.3 seconds to render

![alt text](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/2663%2C10k.png "")

* 512x512
* 10,000 samples per pixel
* 44 minutes to render

![alt text](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/32789%2C100k.png "")

* 512x512
* 100,000 samples per pixel
* 9.1 hours to render

![alt text](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/24733%2C1k.png "")

* 512x512
* 1,000 samples per pixel
* 6.8 hours to render

![alt test](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/9701%2C10k.png "")

* 512x512
* 10,000 samples per pixel
* 2.7 hours to render

![alt test](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/8193%2C10k.png "")

* 512x512
* 10,000 samples per pixel
* 2.2 hours to render
* depth of 15
