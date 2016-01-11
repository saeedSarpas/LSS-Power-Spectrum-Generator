#include <stdio.h>
#include <libconfig.h>

#include "./../config_file/my_libconfig.h"
#include "./../open_file.h"

#include "./../../global_structs/input_file_infos.h"

void write_input_file_infos_to(FILE *file, input_file_infos *infos) {

	config_t cfg;
	config_setting_t *root, *infos_node, *num_of_parts, *box_len;

	libconfig_init(&cfg);
	root = config_root_setting(&cfg);

	infos_node = libconfig_setting_add(root, "infos", CONFIG_TYPE_GROUP);

	num_of_parts = libconfig_setting_add(infos_node, "number_of_particles", CONFIG_TYPE_INT);
	libconfig_setting_set_int(num_of_parts, infos->num_of_parts);

	box_len = libconfig_setting_add(infos_node, "box_length", CONFIG_TYPE_FLOAT);
	libconfig_setting_set_float(box_len, infos->box_length);

	config_write(&cfg, file);
}
