#include <stdio.h>
#include <libconfig.h>

#include "./../config_file/my_libconfig.h"
#include "./../io/open_file.h"

#include "./../../global_structs/info_strcut.h"

void write_info_to (FILE *file, info_struct *info) {

	config_t cfg;
	config_setting_t *root, *info_node, *num_of_parts, *box_len;

	libconfig_init(&cfg);
	root = config_root_setting(&cfg);

	info_node = libconfig_setting_add(root, "info", CONFIG_TYPE_GROUP);

	num_of_parts = libconfig_setting_add(info_node, "number_of_particles", CONFIG_TYPE_INT);
	libconfig_setting_set_int(num_of_parts, info->numOfParts);

	box_len = libconfig_setting_add(info_node, "box_length", CONFIG_TYPE_FLOAT);
	libconfig_setting_set_float(box_len, info->boxLength);

	config_write(&cfg, file);

	libconfig_destroy(&cfg);
}
