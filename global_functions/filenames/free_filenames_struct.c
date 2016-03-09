#include <stdlib.h>

#include "./../../global_structs/filenames_struct.h"

void free_filenames_struct(filenames_struct *filenames) {
  free(filenames->structuredInput);
  free(filenames->inputInfo);
  free(filenames->densityContrast);
  free(filenames->fourierTransformed);
  free(filenames->indexedModes);
  free(filenames->powerSpectrum);
}
