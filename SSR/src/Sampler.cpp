#include <stdlib.h>
#include "Sampler.h"
#include "Utility.h"

Sampler::Sampler(void)
	: 	num_samples(1),
		num_sets(83),
		count(0),
		jump(0) {
	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

Sampler::Sampler(const int ns)
	: 	num_samples(ns),
		num_sets(83),
		count(0),
		jump(0) {
	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

Sampler::Sampler(const int ns, const int n_sets)
	: 	num_samples(ns),
		num_sets(n_sets),
		count(0),
		jump(0) {
	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

void Sampler::setup_shuffled_indices(){
    shuffled_indices.reserve(num_samples * num_sets);
	vector<int> indices;

	for (int j = 0; j < num_samples; j++)
		indices.push_back(j);

	for (int p = 0; p < num_sets; p++) {
		random_shuffle(indices.begin(), indices.end());

		for (int j = 0; j < num_samples; j++)
			shuffled_indices.push_back(indices[j]);
	}
}

void Sampler::map_samples_to_sphere(void) {
	float r1, r2;
	float x, y, z;
	float r, phi;

	sphere_samples.reserve(num_samples * num_sets);

	for (int j = 0; j < num_samples * num_sets; j++) {
		r1 	= samples[j].x();
    	r2 	= samples[j].y();
    	z 	= 1.0 - 2.0 * r1;
    	r 	= sqrt(1.0 - z * z);
    	phi = TWO_PI * r2;
    	x 	= r * cos(phi);
    	y 	= r * sin(phi);
		sphere_samples.push_back(Vec4(x, y, z));
	}
}

void Sampler::map_samples_to_hemisphere(const float exp) {
	int size = samples.size();
	hemisphere_samples.reserve(num_samples * num_sets);

	for (int j = 0; j < size; j++) {
		float cos_phi = cos(2.0 * PI * samples[j].x());
		float sin_phi = sin(2.0 * PI * samples[j].x());
		float cos_theta = pow((1.0 - samples[j].y()), 1.0 / (exp + 1.0));
		float sin_theta = sqrt (1.0 - cos_theta * cos_theta);
		float pu = sin_theta * cos_phi;
		float pv = sin_theta * sin_phi;
		float pw = cos_theta;
		hemisphere_samples.push_back(Vec4(pu, pv, pw));
	}
}
Vec4 Sampler::sample_sphere(void) {
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand() % num_sets) * num_samples;

	return (sphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}


Vec4 Sampler::sample_hemisphere(void) {
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand() % num_sets) * num_samples;

	return (hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}

Vec4 Sampler::sample_unit_square() {
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand() % num_sets) * num_samples;				// random index jump initialised to zero in constructor

	return (samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}