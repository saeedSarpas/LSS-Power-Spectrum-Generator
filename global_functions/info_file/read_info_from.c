#include <stdlib.h>
#include <libconfig.h>

#include "./../config_file/my_libconfig.h"

#include "./../../global_structs/info_strcut.h"

void read_info_from (char *info_file_path, info_struct *info) {
	config_t cfg;
	config_setting_t *info_setting;

	libconfig_init(&cfg);
	libconfig_read_file(&cfg, info_file_path);

	info_setting = libconfig_lookup(&cfg, "info");

	info->numOfParts = libconfig_setting_lookup_int(info_setting,
			"number_of_particles");
	info->boxLength = libconfig_setting_lookup_double(info_setting,
			"box_length");

	libconfig_destroy(&cfg);
}
