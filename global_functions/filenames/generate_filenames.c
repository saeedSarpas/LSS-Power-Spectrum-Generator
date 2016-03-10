#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/info_strcut.h"
#include "./../../global_structs/filenames_struct.h"

#include "./../strings/concat.h"

filenames_struct generate_filenames(config_struct *conf, info_struct *info) {
  filenames_struct filenames;

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

  filenames.structuredInput = concat(2,
    conf->files[conf->params.fileIndex].alias,
    ".dat"
  );

  filenames.inputInfo = concat(2,
    conf->files[conf->params.fileIndex].alias,
    ".info"
  );

  filenames.densityContrast = concat(9,
    "density-contrast-grid-",
    conf->massFunctions[conf->params.massAssignmentIndex].alias, "-",
    num_of_grids_in_each_axis, "-",
    conf->files[conf->params.fileIndex].alias, "-",
    num_of_parts,
    ".dat"
  );

  filenames.fourierTransformed = concat(9,
    "fourier-transformed-grid-",
    conf->massFunctions[conf->params.massAssignmentIndex].alias, "-",
    num_of_grids_in_each_axis, "-",
    conf->files[conf->params.fileIndex].alias, "-",
    num_of_parts,
    ".dat"
  );

  filenames.indexedModes = concat(3,
    "indexed-modes-",
    num_of_grids_in_each_axis,
    ".dat"
  );

  filenames.powerSpectrum = concat(9,
    "power-spectrum-",
    conf->massFunctions[conf->params.massAssignmentIndex].alias, "-",
    num_of_grids_in_each_axis, "-",
    conf->files[conf->params.fileIndex].alias, "-",
    num_of_parts,
    ".dat"
  );

  return filenames;
}
