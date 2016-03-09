#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/info_strcut.h"
#include "./../../global_structs/filenames_struct.h"

#include "./str_concat.h"

filenames_struct generate_filenames(config_struct *conf, info_struct *info,
                                    int count, ...) {
  filenames_struct filenames;
  bool all = (count < 1) ? true : false;

  char num_of_grids_in_each_axis[32];
  sprintf(num_of_grids_in_each_axis, "%d", conf->params.numOfAxisGrids);
  char num_of_parts[32];
  sprintf(num_of_parts, "%d", info->numOfParts);

  filenames.structuredInput = strdup("");
  filenames.inputInfo = strdup("");
  filenames.densityContrast = strdup("");
  filenames.fourierTransformed = strdup("");
  filenames.indexedModes = strdup("");
  filenames.powerSpectrum = strdup("");

  va_list args;
  va_start(args, count);

  char *module_name;

  do {
    if (!all) module_name = va_arg(args, char*);

    if (all || strcmp("structuredInput", module_name) == 0) {
      char *strings[] = {
        conf->files[conf->params.fileIndex].alias,
        ".dat"
      };
      str_concat(strings, 2, &filenames.structuredInput);
    }

    if (all || strcmp("inputInfo", module_name) == 0) {
      char *strings[] = {
        conf->files[conf->params.fileIndex].alias,
        ".info"
      };
      str_concat(strings, 2, &filenames.inputInfo);
    }

    if (all || strcmp("densityContrast", module_name) == 0) {
      char *strings[] = {
        "density-contrast-grid-",
        conf->massFunctions[conf->params.massAssignmentIndex].alias, "-",
        num_of_grids_in_each_axis, "-",
        conf->files[conf->params.fileIndex].alias, "-",
        num_of_parts,
        ".dat"
      };
      str_concat(strings, 9, &filenames.densityContrast);
    }

    if (all || strcmp("fourierTransformed", module_name) == 0) {
      char *strings[] = {
        "fourier-transformed-grid-",
        conf->massFunctions[conf->params.massAssignmentIndex].alias, "-",
        num_of_grids_in_each_axis, "-",
        conf->files[conf->params.fileIndex].alias, "-",
        num_of_parts,
        ".dat"
      };
      str_concat(strings, 9, &filenames.fourierTransformed);
    }

    if (all || strcmp("indexedModes", module_name) == 0) {
      char *strings[] = {
        "indexed-modes-",
        num_of_grids_in_each_axis,
        ".dat"
      };
      str_concat(strings, 3, &filenames.indexedModes);
    }

    if (all || strcmp("powerSpectrum", module_name) == 0) {
      char *strings[] = {
        "power-spectrum-",
        conf->massFunctions[conf->params.massAssignmentIndex].alias, "-",
        num_of_grids_in_each_axis, "-",
        conf->files[conf->params.fileIndex].alias, "-",
        num_of_parts,
        ".dat"
      };
      str_concat(strings, 9, &filenames.powerSpectrum);
    }
  } while (0 <-- count);

  va_end(args);

  return filenames;
}
