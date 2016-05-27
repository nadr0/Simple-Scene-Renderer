#ifndef SAMPLER_H_
#define SAMPLER_H_
#include <vector>
#include "Vec4.h"
using std::vector;

class Sampler{
public:

    Sampler();
    Sampler(int num);
    Sampler(int num, int num_sets);
    void setup_shuffled_indices();
    Vec4 sample_unit_square();


    int 					num_samples;     		// the number of sample points in a set
    int 					num_sets;				// the number of sample sets
    vector<Vec4>			samples;				// sample points on a unit square
    vector<Vec4>			sphere_samples;
    vector<Vec4>			hemisphere_samples;
    vector<Vec4>			disk_samples;			// sample points on a unit disk
    vector<int>				shuffled_indices;		// shuffled samples array indices
    unsigned long 			count;					// the current number of sample points used
    int 					jump;					// random index jump

    void map_samples_to_hemisphere(const float p);
    void map_samples_to_disk(void);
    void map_samples_to_sphere(void);

    Vec4 sample_hemisphere(void);
    Vec4 sample_sphere(void);
    Vec4 sample_disk(void);

};
#endif
