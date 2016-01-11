#include <stdio.h>
#include <string.h>
#include <libconfig.h>

#include "./my_libconfig.h"
#include "./../../global_structs/config_struct.h"

void get_config (struct config_tag *C) {
	config_t cfg;
	config_setting_t *setting, *filename_setting;

	libconfig_init(&cfg);
	libconfig_read_file(&cfg, "./../../configurations.cfg");
	setting = libconfig_lookup(&cfg, "input.files");

	const char *file_name, *file_alias;
	int i, l = libconfig_setting_length(setting);
	for (i = 0; i < l; i++) {
		filename_setting = libconfig_setting_get_elem(setting, i);
		file_name = libconfig_setting_lookup_string(filename_setting, "filename");
		strcpy(C->inputs[i][0], file_name);
		file_alias = libconfig_setting_lookup_string(filename_setting, "alias");
		strcpy(C->inputs[i][1], file_alias);
	}

	libconfig_destroy(&cfg);
}
