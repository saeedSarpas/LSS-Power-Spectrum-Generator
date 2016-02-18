#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>
#include <string.h>
#include <time.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/particle_data_struct.h"
#include "./../../global_structs/input_file_info.h"
#include "./../../global_structs/vector_struct.h"
#include "./../../global_structs/modes_struct.h"
#include "./../../global_structs/bins_struct.h"

#include "./../../global_functions/config_file/get_config.h"
#include "./../../global_functions/filenames/append_input_info_name.h"
#include "./../../global_functions/info_file/read_info_from.h"
#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/filenames/append_fourier_transformed_filename.h"
#include "./../../global_functions/filenames/append_power_spectrum_filename.h"
#include "./../../global_functions/io/open_file.h"
#include "./../../global_functions/io/read_from.h"
#include "./../../global_functions/memory/allocate.h"
#include "./../../global_functions/vector/vector.h"
#include "./../../global_functions/filenames/append_indexed_modes_filename.h"

#include "./struct/single_mode_power_result.h"

#include "./include/load_fourier_transformed_data.h"
#include "./include/single_mode_power.h"
#include "./include/generate_logarithmic_bins.h"
#include "./include/generate_linear_bins.h"

#define PI (3.141592653589793)

int main() {

	config_struct conf;
	get_config(&conf, "./../../configurations.cfg");

	char *input_filename_alias;
	input_filename_alias = conf.input_files[conf.run_params.file_index][1];

	char *algorithm_alias;
	algorithm_alias =
		conf.mass_assignment_functions[conf.run_params.mass_assignment_index][1];

	input_info_struct info;
	char *input_info_path = strdup("./../../0_structured_input/");
	append_input_info_name(input_filename_alias, &input_info_path);
	read_info_from(input_info_path, &info);


	clock_t _l_f_t_d_ = start("Load Fourier transformed data... ");

	size_t tot_num_of_grids = pow(conf.run_params.num_of_axis_grids, 3);

	fftw_complex *delta_fourier;
	allocate((void **)&delta_fourier, tot_num_of_grids, sizeof(fftw_complex));

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

	modes_struct *indexed_mode_modulus;
	allocate((void **)&indexed_mode_modulus, tot_num_of_grids,
			 sizeof(modes_struct));
	read_from(indexed_mode_modulus_file, tot_num_of_grids, sizeof(modes_struct),
			  (void *)indexed_mode_modulus);

	fclose(indexed_mode_modulus_file);

	vector_struct bins_vector;
	vector_new(&bins_vector, sizeof(struct bins_struct_tag),
			   conf.run_params.num_of_axis_grids);

	if (strcmp(conf.binning[conf.run_params.binning_index][1], "lin") == 0) {
		printf("[Using linear bins] ");
		generate_linear_bins(&bins_vector, &conf);
	} else if (strcmp(conf.binning[conf.run_params.binning_index][1], "log") == 0) {
		printf("[Using logarithmic bins] ");
		generate_logarithmic_bins(&bins_vector, indexed_mode_modulus, &conf);
	} else {
		printf("[Unknown binning mode]\n");
		exit(0);
	}

	done(_g_b_a_);


	clock_t _g_a_s_p_s_ = start("Generating and saving power spectrum... ");

	char *output_path = strdup("./../output/");
	append_power_spectrum_filename(input_filename_alias, algorithm_alias,
								   &conf, &info, &output_path);

	FILE * output_file;
	open_file(&output_file, output_path, "wb");

	fprintf(output_file,
			"Mode     \tShell min\tShell max\tPower   \tPower err\tFound modes\n");

	bins_struct bin;
	single_mode_power_result_struct result;

	while (bins_vector.log_length > 0) {
		vector_pop(&bins_vector, &bin);
		result = single_mode_power(bin.k_min, bin.k_max, delta_fourier,
								   indexed_mode_modulus, &conf);

		double scale_factor = (2 * PI) / info.box_length;
		double scaled_k = bin.k * scale_factor;
		double scaled_k_min = bin.k_min * scale_factor;
		double scaled_k_max = bin.k_max * scale_factor;
		double scaled_mode_power = result.mode_power;
		double scaled_error = result.error;

		fprintf(output_file, "%f\t%f\t%f\t%f\t%f\t%d\n", scaled_k, scaled_k_min,
				scaled_k_max, scaled_mode_power, scaled_error,
				result.num_of_found_modes);
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
