#ifndef PINHOLE_H_
#define PINHOLE_H_
class Pinhole: public Camera{
public:
    Pinhole();
    virtual void render_scene(World &w);
    void ray_direction(Vec4 &p, Vec4 & ray);

};
#endif
