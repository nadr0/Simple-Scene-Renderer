#ifndef MULTIJITTER_H_
#define MULTIJITTER_H_
class MultiJitter : public Sampler{
public:
    MultiJitter(void);
    MultiJitter(const int num_samples);
    MultiJitter(const int num_samples, const int m);
    virtual void generate_samples();

};
#endif
