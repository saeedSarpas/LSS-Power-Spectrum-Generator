#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>
#include <string.h>
#include <time.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/filenames_struct.h"
#include "./../../global_structs/particle_struct.h"
#include "./../../global_structs/info_strcut.h"
#include "./../../global_structs/vector_struct.h"
#include "./../../global_structs/modes_struct.h"
#include "./../../global_structs/bins_struct.h"

#include "./../../global_functions/config_file/load_config_from.h"
#include "./../../global_functions/info_file/get_info_from.h"
#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/io/open_file.h"
#include "./../../global_functions/io/read_from.h"
#include "./../../global_functions/memory/allocate.h"
#include "./../../global_functions/vector/vector.h"
#include "./../../global_functions/filenames/generate_filenames.h"
#include "./../../global_functions/strings/concat.h"

#include "./struct/signal_power_result.h"

#include "./include/load_fourier_transformed_data.h"
#include "./include/signal_power.h"
#include "./include/generate_logarithmic_bins.h"
#include "./include/generate_linear_bins.h"
#include "./include/smearing_and_anisotropy_correction_for_ngp.h"
#include "./include/smearing_and_anisotropy_correction_for_cic.h"
#include "./include/smearing_and_anisotropy_correction_for_tsc.h"

int main() {
	config_struct conf = load_config_from("./../../configurations.cfg");
  filenames_struct filenames = generate_filenames(&conf);

	char *info_path = concat(2,
    "./../../0_structured_input/", filenames.inputInfo);
	info_struct info = get_info_from(info_path);


	clock_t _l_f_t_d_ = start("Load Fourier transformed data... ");

	size_t tot_num_of_grids = pow(conf.params.numOfAxisGrids, 3);

	fftw_complex *delta_fourier;
	allocate((void **)&delta_fourier, tot_num_of_grids, sizeof(fftw_complex));

	char *input_path = concat(2,
    "./../../3_fftw/output/", filenames.fourierTransformed);
	load_fourier_transformed_data(input_path, delta_fourier, &conf);

	done(_l_f_t_d_);


	clock_t _a_m_a_w_f_ = start("Smearing and anisotropy correction... ");

	char *alg_alias = conf.massFunctions[conf.params.massAssignmentIndex].alias;

	if (strcmp(alg_alias, "ngp") == 0)
      smearing_and_anisotropy_correction_for_ngp(delta_fourier, &conf);
	else if (strcmp(alg_alias, "cic") == 0)
      smearing_and_anisotropy_correction_for_cic(delta_fourier, &conf);
	else if (strcmp(alg_alias, "tsc") == 0)
      smearing_and_anisotropy_correction_for_tsc(delta_fourier, &conf);
	else {
      printf("[Unknown mass assignment algorithm]\n");
      exit(0);
	}

	done(_a_m_a_w_f_);


	clock_t _n_ = start("Normalizing... ");

	unsigned int i;
	double sqrt_tot_num_of_grids = sqrt(tot_num_of_grids);
	for (i = 0; i < tot_num_of_grids; i++)
      delta_fourier[i] /=  sqrt_tot_num_of_grids;

	done(_n_);


	clock_t _g_b_a_ = start("Generate bins array...");

	FILE *indexed_mode_modulus_file;
	char *indexed_mode_modulus_file_path = concat(2,
    "./../../4_indexing_k_modulus/output/", filenames.indexedModes);
	open_file(&indexed_mode_modulus_file, indexed_mode_modulus_file_path, "rb");

	modes_struct *indexed_mode_modulus;
	allocate((void **)&indexed_mode_modulus, tot_num_of_grids,
			 sizeof(modes_struct));
	read_from(indexed_mode_modulus_file, tot_num_of_grids, sizeof(modes_struct),
			  (void *)indexed_mode_modulus);

	fclose(indexed_mode_modulus_file);

	vector_struct bins_vector;
	vector_new(&bins_vector, sizeof(struct bins), conf.params.numOfAxisGrids);

	if (strcmp(conf.binning[conf.params.binningIndex].alias, "lin") == 0) {
		printf("[Using linear bins] ");
		generate_linear_bins(&bins_vector, &conf);
	} else if (strcmp(conf.binning[conf.params.binningIndex].alias, "log") == 0) {
		printf("[Using logarithmic bins] ");
		generate_logarithmic_bins(&bins_vector, indexed_mode_modulus, &conf);
	} else {
		printf("[Unknown binning mode]\n");
		exit(0);
	}

	done(_g_b_a_);


	clock_t _g_a_s_p_s_ = start("Generating and saving power spectrum... ");

	char *output_path = concat(2,
    "./../output/", filenames.powerSpectrum);

	FILE * output_file;
	open_file(&output_file, output_path, "wb");

	fprintf(output_file,
			"Mode     \tShell min\tShell max\tPower   \tPower err\tFound modes\n");

	bins_struct bin;
	signal_power_result_struct result;

	while (bins_vector.log_length > 0) {
		vector_pop(&bins_vector, &bin);
		result = signal_power(bin.k_min, bin.k_max, delta_fourier,
								   indexed_mode_modulus, &conf);

		double scale_factor = (2 * M_PI) / info.boxLength;
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

	free(info_path);
	free(input_path);
	free(indexed_mode_modulus_file_path);
	free(output_path);
	fftw_free(delta_fourier);
	free(indexed_mode_modulus);
	vector_dispose(&bins_vector);
	return 0;
}
