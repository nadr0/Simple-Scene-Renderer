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
* 10,000 sample per pixel
* 44 minutes to render

![alt text](https://github.com/nadr0/Simple-Scene-Renderer/blob/master/SSR/32789%2C100k.png "")

* 512x512
* 100,000 sample per pixel
* 9.1 hours to render

