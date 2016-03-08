#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./../../../global_structs/vector_struct.h"
#include "./../../../global_structs/modes_struct.h"
#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/bins_struct.h"

#include "./../../../global_functions/vector/vector.h"

void generate_logarithmic_bins(vector_struct *bins_vector,
		modes_struct *indexed_mode_modulus, config_struct *conf) {

	double max_of_first_bin = indexed_mode_modulus[18].modulus;
	double jump = sqrt(max_of_first_bin);

	int tot_num_of_grids = pow(conf->params.numOfAxisGrids, 3);
	double largest_mode = indexed_mode_modulus[tot_num_of_grids - 1].modulus;

	bins_struct bin;
	int i = 0;
	do {
		bin.k_min = pow(jump, i);
		bin.k     = pow(jump, i+1);
		bin.k_max = pow(jump, i+2);

		vector_push(bins_vector, &bin);

		i += 2;
	} while (bin.k_max < largest_mode);
}
