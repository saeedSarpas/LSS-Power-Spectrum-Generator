#include <math.h>

#include "./../../../global_structs/vector_struct.h"
#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/bins_struct.h"

#include "./../../../global_functions/vector/vector.h"

void generate_linear_bins (vector_struct *bins_vector, config_struct *conf) {
	int maximum_of_k = sqrt(3) * conf->num_of_grids_in_each_axis / 2;

	int i;
	bins_struct bin;
	for (i = 1; i < maximum_of_k; i++) {
		bin.k_min = i;
		bin.k = i + .5;
		bin.k_max = i + 1;
		vector_push(bins_vector, &bin);
	}
}
