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
  filenames_struct filenames = generate_filenames(&conf, &info, -1);

  assert_true(strcmp(filenames.structuredInput, structuredInput) == 0);
  assert_true(strcmp(filenames.inputInfo, inputInfo) == 0);
  assert_true(strcmp(filenames.densityContrast, densityContrast) == 0);
  assert_true(strcmp(filenames.fourierTransformed, fourierTransformed) == 0);
  assert_true(strcmp(filenames.indexedModes, indexedModes) == 0);
  assert_true(strcmp(filenames.powerSpectrum, powerSpectrum) == 0);
}

Ensure (generate_filenames, returns_only_structuredInput) {
  filenames_struct filenames = generate_filenames(&conf, &info, 1,
                                                 "structuredInput");

  assert_true(strcmp(filenames.structuredInput, structuredInput) == 0);
  assert_true(strcmp(filenames.inputInfo, "") == 0);
  assert_true(strcmp(filenames.densityContrast, "") == 0);
  assert_true(strcmp(filenames.fourierTransformed, "") == 0);
  assert_true(strcmp(filenames.indexedModes, "") == 0);
  assert_true(strcmp(filenames.powerSpectrum, "") == 0);
}

Ensure (generate_filenames, returns_only_powerSpectrum) {
  filenames_struct filenames = generate_filenames(&conf, &info, 1,
                                                  "powerSpectrum");

  assert_true(strcmp(filenames.structuredInput, "") == 0);
  assert_true(strcmp(filenames.inputInfo, "") == 0);
  assert_true(strcmp(filenames.densityContrast, "") == 0);
  assert_true(strcmp(filenames.fourierTransformed, "") == 0);
  assert_true(strcmp(filenames.indexedModes, "") == 0);
  assert_true(strcmp(filenames.powerSpectrum, powerSpectrum) == 0);
}

Ensure (generate_filenames, returns_4_filenames) {
  filenames_struct filenames = generate_filenames(&conf, &info, 4,
                                                  "inputInfo",
                                                  "densityContrast",
                                                  "fourierTransformed",
                                                  "indexedModes");

  assert_true(strcmp(filenames.structuredInput, "") == 0);
  assert_true(strcmp(filenames.inputInfo, inputInfo) == 0);
  assert_true(strcmp(filenames.densityContrast, densityContrast) == 0);
  assert_true(strcmp(filenames.fourierTransformed, fourierTransformed) == 0);
  assert_true(strcmp(filenames.indexedModes, indexedModes) == 0);
  assert_true(strcmp(filenames.powerSpectrum, "") == 0);
}

TestSuite *generate_filenames_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, generate_filenames,
                        returns_all_filenames_correct);
	add_test_with_context(suite, generate_filenames,
                        returns_only_structuredInput);
	add_test_with_context(suite, generate_filenames,
                        returns_only_powerSpectrum);
	add_test_with_context(suite, generate_filenames,
                        returns_4_filenames);
	return suite;
}

void fill_filenames(){
	char num_of_grids_in_each_axis[32];
	sprintf(num_of_grids_in_each_axis, "%d", conf.params.numOfAxisGrids);
	char num_of_parts[32];
	sprintf(num_of_parts, "%d", info.numOfParts);

  char *strings[STRING_ARRAY_LENGTH];
  structuredInput = strdup("");
  strings[0] = strdup(conf.files[conf.params.fileIndex].alias);
  strings[1] = strdup(".dat");
  structuredInput = concat(strings, 2);

  inputInfo = strdup("");
  strings[0] = strdup(conf.files[conf.params.fileIndex].alias);
  strings[1] = strdup(".info");
  inputInfo = concat(strings, 2);

  densityContrast = strdup("");
  strings[0] = strdup("density-contrast-grid-");
  strings[1] = strdup(conf.massFunctions[conf.params.massAssignmentIndex].alias);
  strings[2] = strdup("-");
  strings[3] = strdup(num_of_grids_in_each_axis);
  strings[4] = strdup("-");
  strings[5] = strdup(conf.files[conf.params.fileIndex].alias);
  strings[6] = strdup("-");
  strings[7] = strdup(num_of_parts);
  strings[8] = strdup(".dat");
  densityContrast = concat(strings, 9);

  fourierTransformed = strdup("");
  strings[0] = strdup("fourier-transformed-grid-");
  strings[1] = strdup(conf.massFunctions[conf.params.massAssignmentIndex].alias);
  strings[2] = strdup("-");
  strings[3] = strdup(num_of_grids_in_each_axis);
  strings[4] = strdup("-");
  strings[5] = strdup(conf.files[conf.params.fileIndex].alias);
  strings[6] = strdup("-");
  strings[7] = strdup(num_of_parts);
  strings[8] = strdup(".dat");
  fourierTransformed = concat(strings, 9);

  indexedModes = strdup("");
  strings[0] = strdup("indexed-modes-");
  strings[1] = strdup(num_of_grids_in_each_axis);
  strings[2] = strdup(".dat");
  indexedModes = concat(strings, 3);

  powerSpectrum = strdup("");
  strings[0] = strdup("power-spectrum-");
  strings[1] = strdup(conf.massFunctions[conf.params.massAssignmentIndex].alias);
  strings[2] = strdup("-");
  strings[3] = strdup(num_of_grids_in_each_axis);
  strings[4] = strdup("-");
  strings[5] = strdup(conf.files[conf.params.fileIndex].alias);
  strings[6] = strdup("-");
  strings[7] = strdup(num_of_parts);
  strings[8] = strdup(".dat");
  powerSpectrum = concat(strings, 9);

  int i;
  for (i = 0; i < STRING_ARRAY_LENGTH; i++)
    if (strings[i] != NULL)
      free(strings[i]);
}
