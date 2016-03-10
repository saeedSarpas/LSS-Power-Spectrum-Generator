#include <cgreen/cgreen.h>
#include <string.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/filenames_struct.h"

#include "./../strings/concat.h"
#include "./generate_filenames.h"

Describe (generate_filenames);

#define STRING_ARRAY_LENGTH 8
#define FILENAME "filename"
#define ALIAS "alias"
#define NOG 64

static config_struct conf;
static char* structuredInput;
static char* inputInfo;
static char* densityContrast;
static char* fourierTransformed;
static char* indexedModes;
static char* powerSpectrum;

void fill_filenames();

BeforeEach (generate_filenames) {
  conf.params.fileIndex = 0;
  conf.params.massAssignmentIndex = 0;
  conf.params.numOfAxisGrids = NOG;
  conf.files[conf.params.fileIndex].alias = ALIAS;
  conf.massFunctions[conf.params.massAssignmentIndex].alias = ALIAS;

  fill_filenames();
}

AfterEach (generate_filenames) {
  free(structuredInput);
  free(inputInfo);
  free(densityContrast);
  free(fourierTransformed);
  free(indexedModes);
  free(powerSpectrum);
}

Ensure (generate_filenames, returns_all_filenames_correct) {

  filenames_struct filenames = generate_filenames(&conf);

  assert_true(strcmp(filenames.structuredInput, structuredInput) == 0);
  assert_true(strcmp(filenames.inputInfo, inputInfo) == 0);
  assert_true(strcmp(filenames.densityContrast, densityContrast) == 0);
  assert_true(strcmp(filenames.fourierTransformed, fourierTransformed) == 0);
  assert_true(strcmp(filenames.indexedModes, indexedModes) == 0);
  assert_true(strcmp(filenames.powerSpectrum, powerSpectrum) == 0);
}

TestSuite *generate_filenames_tests() {
  TestSuite *suite = create_test_suite();
  add_test_with_context(suite, generate_filenames,
                        returns_all_filenames_correct);
  return suite;
}

void fill_filenames(){
  char num_of_grids_in_each_axis[32];
  sprintf(num_of_grids_in_each_axis, "%d", conf.params.numOfAxisGrids);

  structuredInput = concat(2,
    conf.files[conf.params.fileIndex].alias,
    ".dat"
  );

  inputInfo = concat(2,
    conf.files[conf.params.fileIndex].alias,
    ".info"
  );

  densityContrast = concat(8,
    "density-contrast-grid-",
    conf.massFunctions[conf.params.massAssignmentIndex].alias, "-",
    num_of_grids_in_each_axis, "-",
    conf.files[conf.params.fileIndex].alias, "-",
    ".dat"
  );

  fourierTransformed = concat(8,
    "fourier-transformed-grid-",
    conf.massFunctions[conf.params.massAssignmentIndex].alias, "-",
    num_of_grids_in_each_axis, "-",
    conf.files[conf.params.fileIndex].alias, "-",
    ".dat"
  );

  indexedModes = concat(3,
    "indexed-modes-",
    num_of_grids_in_each_axis,
    ".dat"
  );

  powerSpectrum = concat(8,
    "power-spectrum-",
    conf.massFunctions[conf.params.massAssignmentIndex].alias, "-",
    num_of_grids_in_each_axis, "-",
    conf.files[conf.params.fileIndex].alias, "-",
    ".dat"
  );
}
