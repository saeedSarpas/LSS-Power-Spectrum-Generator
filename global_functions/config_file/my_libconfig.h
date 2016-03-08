#include <libconfig.h>

void libconfig_init (config_t *);

void libconfig_read_file (config_t *, const char *);

config_setting_t* libconfig_lookup (config_t *, char *);

config_setting_t* libconfig_setting_get_elem (config_setting_t *, int);

const char* libconfig_setting_lookup_string (config_setting_t *, const char *);

int libconfig_setting_lookup_int (config_setting_t *, const char *);

double libconfig_setting_lookup_double (config_setting_t *, const char *);

int libconfig_setting_length (config_setting_t *);

config_setting_t* libconfig_setting_add (config_setting_t *, const char *, int);

void libconfig_setting_set_int (config_setting_t *, int);

void libconfig_setting_set_float (config_setting_t *, double);

void libconfig_setting_set_string (config_setting_t *, const char *);

void libconfig_destroy (config_t *);
