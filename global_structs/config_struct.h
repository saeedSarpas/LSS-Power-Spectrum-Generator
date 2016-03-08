#ifndef CONFIG_STRUCT_H
#define CONFIG_STRUCT_H

typedef struct params {
  int fileIndex;
  int massAssignmentIndex;
  int binningIndex;
  int numOfAxisGrids;
} params_struct;

typedef struct files {
  const char *filename;
  const char *alias;
} files_struct;

typedef struct mass_functions {
  const char *name;
  const char *alias;
} mass_functions_struct;

typedef struct binning {
  const char *name;
  const char *alias;
} binning_struct;

typedef struct config_struct_tag {
  files_struct files[2];
  mass_functions_struct massFunctions[3];
  binning_struct binning[2];
  params_struct params;
} config_struct;

#endif
