#include <cgreen/cgreen.h>
#include <string.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/info_strcut.h"
#include "./../../global_structs/filenames_struct.h"

#include "./../strings/concat.h"
#include "./generate_filenames.h"

Describe (generate_filenames);

#define NUM_OF_PARTS 1000
#define FILENAME "filename"
#define ALIAS "alias"
#define NOG 64
#define STRING_ARRAY_LENGTH 9 

static config_struct conf;
static info_struct info;
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

  info.numOfParts = NUM_OF_PARTS;

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

  filenames_struct filenames = generate_filenames(&conf, &info);

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
  char num_of_parts[32];
  sprintf(num_of_parts, "%d", info.numOfParts);

  structuredInput = concat(2,
    conf.files[conf.params.fileIndex].alias,
    ".dat"
  );

  inputInfo = concat(2,
    conf.files[conf.params.fileIndex].alias,
    ".info"
  );

  densityContrast = concat(9,
    "density-contrast-grid-",
    conf.massFunctions[conf.params.massAssignmentIndex].alias, "-",
    num_of_grids_in_each_axis, "-",
    conf.files[conf.params.fileIndex].alias, "-",
    num_of_parts,
    ".dat"
  );

  fourierTransformed = concat(9,
    "fourier-transformed-grid-",
    conf.massFunctions[conf.params.massAssignmentIndex].alias, "-",
    num_of_grids_in_each_axis, "-",
    conf.files[conf.params.fileIndex].alias, "-",
    num_of_parts,
    ".dat"
  );

  indexedModes = concat(3,
    "indexed-modes-",
    num_of_grids_in_each_axis,
    ".dat"
  );

  powerSpectrum = concat(9,
    "power-spectrum-",
    conf.massFunctions[conf.params.massAssignmentIndex].alias, "-",
    num_of_grids_in_each_axis, "-",
    conf.files[conf.params.fileIndex].alias, "-",
    num_of_parts,
    ".dat"
  );
}
