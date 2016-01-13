#include <stdlib.h>
#include <libconfig.h>

#include "./../config_file/my_libconfig.h"

#include "./../../global_structs/input_file_infos.h"

void read_input_file_infos(input_file_infos *info, char *info_file_path) {
	config_t cfg;
	config_setting_t *infos_setting;

	libconfig_init(&cfg);
	libconfig_read_file(&cfg, info_file_path);

	infos_setting = libconfig_lookup(&cfg, "infos");

	info->num_of_parts = libconfig_setting_lookup_int(infos_setting, "number_of_particles");
	info->box_length = libconfig_setting_lookup_double(infos_setting, "box_length");
}
