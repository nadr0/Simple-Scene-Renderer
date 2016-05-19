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
    * Path tracing (Global Illumination)
+ Bounding Volume Hierarchy (BVH)
    * Median split method
    
More To Come!
=====
Future additions.

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
