#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./../../global_structs/particle_struct.h"
#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/info_strcut.h"
#include "./../../global_structs/filenames_struct.h"

#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/memory/allocate.h"
#include "./../../global_functions/io/open_file.h"
#include "./../../global_functions/io/write_to.h"
#include "./../../global_functions/config_file/load_config_from.h"
#include "./../../global_functions/info_file/write_info_to.h"
#include "./../../global_functions/filenames/generate_filenames.h"
#include "./../../global_functions/strings/append.h"

#include "./../../1b_load_halotab/src/include/get_number_of_lines.h"
#include "./include/load_z07to08_from_file.h"

int main() {

  clock_t _r_h_f_ = start("Reading z0.7to0.8 file... ");

  FILE *z08to07_file;
  open_file(&z08to07_file, "./../input/z0.7to0.8.dat", "r");

  int num_of_lines = get_number_of_lines(z08to07_file);
  rewind(z08to07_file);

  particle_struct *P;
  allocate((void **)&P, num_of_lines, sizeof(struct particle));
  load_z07to08_from_file(z08to07_file, P);
  fclose(z08to07_file);

  done(_r_h_f_);


  clock_t _s_o_f_ = start("Saving output file...");

  config_struct conf = load_config_from("./../../configurations.cfg");
  info_struct info = {.numOfParts = num_of_lines, .boxLength = 200.0};
  filenames_struct filenames = generate_filenames(&conf, &info, 2,
                                                  "structuredInput",
                                                  "inputInfo");

  char *output_path = append("./../../0_structured_input/",
                             filenames.structuredInput);

  FILE *output_file;
  open_file(&output_file, output_path, "wb");
  write_to(output_file, P, num_of_lines, sizeof(struct particle));
  fclose(output_file);

  done(_s_o_f_);


  clock_t _s_i_f_ = start("Saving info file... ");

  char *info_path = append("./../../0_structured_input/", filenames.inputInfo);

  FILE *info_file;
  open_file(&info_file, info_path, "w+");
  write_info_to(info_file, &info);
  fclose(info_file);

  done(_s_i_f_);

  free(P);
  free(output_path);
  free(info_path);
  return 0;
}
