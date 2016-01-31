#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>
#include <string.h>
#include <time.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/particle_data_struct.h"
#include "./../../global_structs/input_file_infos.h"
#include "./../../global_structs/vector_struct.h"
#include "./../../global_structs/modes_struct.h"
#include "./../../global_structs/bins_struct.h"

#include "./../../global_functions/config_file/get_config.h"
#include "./../../global_functions/io/get_algorithm_alias.h"
#include "./../../global_functions/io/get_input_filename_alias.h"
#include "./../../global_functions/filenames/append_input_infos_name.h"
#include "./../../global_functions/info_file/read_input_file_infos.h"
#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/memory/allocate_fftw_complex.h"
#include "./../../global_functions/filenames/append_fourier_transformed_filename.h"
#include "./../../global_functions/filenames/append_power_spectrum_filename.h"
#include "./../../global_functions/open_file.h"
#include "./../../global_functions/memory/allocate_double_array.h"
#include "./../../global_functions/vector/vector.h"
#include "./../../global_functions/filenames/append_indexed_modes_filename.h"
#include "./../../global_functions/memory/allocate_modes_struct.h"
#include "./../../global_functions/io/read_modes_struct_from.h"

#include "./struct/single_mode_power_result.h"

#include "./include/load_fourier_transformed_data.h"
#include "./include/single_mode_power.h"
#include "./include/generate_logarithmic_bins.h"

#define PI (3.141592653589793)

int main() {

	config conf;
	get_config(&conf);

	char *input_filename_alias;
	input_filename_alias = get_input_filename_alias(&conf);

	char *algorithm_alias;
	algorithm_alias = get_algorithm_alias(&conf);

	input_file_infos info;
	char *input_info_path = strdup("./../../0_structured_input/");
	append_input_infos_name(input_filename_alias, &input_info_path);
	read_input_file_infos(&info, input_info_path);


	clock_t _l_f_t_d_ = start("Load Fourier transformed data... ");

	size_t tot_num_of_grids = pow(conf.num_of_grids_in_each_axis, 3);

	fftw_complex *delta_fourier;
	allocate_fftw_complex(&delta_fourier, tot_num_of_grids);

	char *input_path = strdup("./../../3_fftw/output/");
	append_fourier_transformed_filename(input_filename_alias, algorithm_alias,
										&info, &conf, &input_path);
	load_fourier_transformed_data(input_path, delta_fourier, &conf);

	done(_l_f_t_d_);

	clock_t _g_b_a_ = start("Generate bins array...");

	char *indexed_mode_modulus_file_path = strdup("./../../4_indexing_k_modulus/output/");
	append_indexed_modes_filename(&conf, &indexed_mode_modulus_file_path);

	FILE *indexed_mode_modulus_file;
	open_file(&indexed_mode_modulus_file, indexed_mode_modulus_file_path, "rb");

	modes *indexed_mode_modulus;
	allocate_modes_struct(&indexed_mode_modulus, tot_num_of_grids);
	read_modes_struct_from(indexed_mode_modulus_file, indexed_mode_modulus_file_path,
			indexed_mode_modulus, tot_num_of_grids, &conf);

	fclose(indexed_mode_modulus_file);

	vector bins_vector;
	vector_new(&bins_vector, sizeof(bins), 20);

	generate_logarithmic_bins(&bins_vector, indexed_mode_modulus, &conf);

	done(_g_b_a_);


	clock_t _g_a_s_p_s_ = start("Generating and saving power spectrum... ");

	char *output_path = strdup("./../output/");
	append_power_spectrum_filename(input_filename_alias, algorithm_alias,
			&conf, &info, &output_path);

	FILE * output_file;
	open_file(&output_file, output_path, "wb");

	fprintf(output_file, "Mode     \tShell min\tShell max\tPower   \tPower err\tFound modes\n");

	bins bin;
	single_mode_power_result result;

	while (bins_vector.log_length > 0) {
		vector_pop(&bins_vector, &bin);
		result = single_mode_power(bin.k_min, bin.k, bin.k_max, delta_fourier,
				indexed_mode_modulus, &conf);

		fprintf(output_file, "%f\t%f\t%f\t%f\t%f\t%d\n", bin.k, bin.k_min,
				bin.k_max, result.mode_power, result.error, result.num_of_found_modes);
	}

	done(_g_a_s_p_s_);

	fclose(output_file);

	free(input_info_path);
	free(input_path);
	free(indexed_mode_modulus_file_path);
	free(output_path);
	fftw_free(delta_fourier);
	free(indexed_mode_modulus);
	vector_dispose(&bins_vector);
	return 0;
}
