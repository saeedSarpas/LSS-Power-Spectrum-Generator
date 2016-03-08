#include <stdlib.h>
#include <libconfig.h>

void libconfig_init (config_t *cfg) {
	config_init(cfg);
}

void libconfig_read_file (config_t *cfg, const char *file_path) {
	if (!config_read_file(cfg, file_path)) {
		printf("[%s:%d - %s]\n", config_error_file(cfg),
				config_error_line(cfg), config_error_text(cfg));
		config_destroy(cfg);
		exit(EXIT_FAILURE);
	}
}

config_setting_t* libconfig_lookup (config_t *cfg, char *path) {
	config_setting_t * setting = config_lookup(cfg, path);
	if (setting != NULL) {
		return setting;
	} else {
		printf("[Did not find '%s' in config file]\n", path);
		config_destroy(cfg);
		exit(EXIT_FAILURE);
	}
}

config_setting_t* libconfig_setting_get_elem (config_setting_t *setting,
                                              int index) {
	config_setting_t *elem = config_setting_get_elem(setting, index);
	if (elem != NULL) {
		return elem;
	} else {
		printf("[Can not find the element]\n");
		exit(EXIT_FAILURE);
	}
}

const char* libconfig_setting_lookup_string (config_setting_t *setting,
                                             const char *field) {
	const char *value;
	if (config_setting_lookup_string(setting, field, &value)) {
		return value;
	} else {
		printf("[Unable to find field: %s]\n", field);
		exit(EXIT_FAILURE);
	}
}

int libconfig_setting_lookup_int (config_setting_t *setting,
                                  const char *field) {
	int value;
	if (config_setting_lookup_int(setting, field, &value)) {
		return value;
	} else {
		printf("[Unable to find field: %s]\n", field);
		exit(EXIT_FAILURE);
	}
}

double libconfig_setting_lookup_double (config_setting_t *setting,
                                        const char *field) {
	double value;
	if (config_setting_lookup_float(setting, field, &value)) {
		return value;
	} else {
		printf("[Unable to find field: %s]\n", field);
		exit(EXIT_FAILURE);
	}
}

int libconfig_setting_length (config_setting_t *setting) {
	int len = config_setting_length(setting);
	if (len) {
		return len;
	} else {
		printf("[The length of the setting is zero]\n");
		exit(EXIT_FAILURE);
	}
}

config_setting_t* libconfig_setting_add (config_setting_t *parent,
                                         const char *name, int type) {
	config_setting_t *added_setting = config_setting_add(parent, name, type);
	if (added_setting) {
		return added_setting;
	} else {
		printf("[Unable to add new setting]\n");
		exit(EXIT_FAILURE);
	}
}

void libconfig_setting_set_int (config_setting_t *setting, int value) {
	if (!config_setting_set_int(setting, value)) {
		printf("[Unable to set integer value]\n");
		exit(EXIT_FAILURE);
	}
}

void libconfig_setting_set_float (config_setting_t *setting, double value) {
	if (!config_setting_set_float(setting, value)) {
		printf("[Unable to set float/double value]\n");
		exit(EXIT_FAILURE);
	}
}

void libconfig_setting_set_string (config_setting_t *setting,
                                   const char *value) {
	if (config_setting_set_string(setting, value) != CONFIG_TRUE) {
		printf("[Unable to set string value]\n");
		exit(EXIT_FAILURE);
	}
}

void libconfig_destroy (config_t *cfg) {
	config_destroy(cfg);
}
