#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <fftw3.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "./../configurations.h"
#include "./../global_functions/clock.h"
#include "./../global_functions/choosing.h"
#include "./../global_functions/config_file.h"
#include "./../global_functions/filenames.h"
#include "./../global_functions/grid.h"
#include "./../global_functions/memory_allocation.h"
#include "./../global_functions/file_handling.h"
#include "./../global_functions/length.h"

#include "./include/select_modes_with_length.h"
#include "./include/load_indexed_modes.h"
#include "./include/checkif_triangle_then_fill.h"

int main () {

  char load_indexed_modes_msg[256] = "Loading input data... ";
  clock_t start_loading = start(load_indexed_modes_msg);

  size_t total_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);
  allocate_struct_modes_array(&M, total_num_grid);

  load_indexed_modes(&M);

  done(start_loading);

  char finding_triangles_msg[256] = "Finding and saving triangles... ";
  clock_t ft_start = start(finding_triangles_msg);

  int * equi_tmp_indices;
  allocate_int_array(&equi_tmp_indices, total_num_grid);

  FILE * equi_file;
  char equi_file_path[256] = "./outputs/";
  append_equilateral_triangles_filename(equi_file_path);
  open_file(&equi_file, equi_file_path, "ab");

  struct triangles * equi_tmp_triangles;
  allocate_struct_triangles_array(&equi_tmp_triangles, total_num_grid);

  int * iso_tmp_indices;
  allocate_int_array(&iso_tmp_indices, total_num_grid);

  FILE * iso_file;
  char iso_file_path[256] = "./outputs/";
  append_isosceles_triangles_filename(iso_file_path);
  open_file(&iso_file, iso_file_path, "ab");

  struct triangles * iso_tmp_triangles;
  allocate_struct_triangles_array(&iso_tmp_triangles, total_num_grid);

  int * scal_tmp_indices;
  allocate_int_array(&scal_tmp_indices, total_num_grid);

  FILE * scal_file;
  char scal_file_path[256] = "./outputs/";
  append_scalene_triangles_filename(scal_file_path);
  open_file(&scal_file, scal_file_path, "ab");

  struct triangles * scal_tmp_triangles;
  allocate_struct_triangles_array(&scal_tmp_triangles, total_num_grid);

  unsigned int index1, index2;
  int vec1[3], vec2[3], sum_vec[3];
  double vec1_length, vec2_length, vec3_length;
  int equi_cntr = 0, iso_cntr = 0, scal_cntr = 0;
  int equi_hldr = 0, iso_hldr = 0, scal_hldr = 0;
  int i;

  for (index1 = 1; index1 < total_num_grid; index1++) {
    for (index2 = 1; index2 < total_num_grid; index2++) {

      one_to_three(index1, vec1);
      one_to_three(index2, vec2);

      sum_vec[0] = vec1[0] + vec2[0];
      sum_vec[1] = vec1[1] + vec2[1];
      sum_vec[2] = vec1[2] + vec2[2];

      if (sum_vec[0] == 0 || sum_vec[1] == 0 || sum_vec[2] == 0) {
        continue;
      }

      vec1_length = vec_length(vec1);
      vec2_length = vec_length(vec2);
      vec3_length = vec_length(sum_vec);

      if (vec1_length == vec2_length && vec2_length == vec3_length) {
        select_modes_with_length(&M, vec3_length, equi_tmp_indices);
        if (equi_tmp_indices[0] > 0){
          for (i = 1; i <= equi_tmp_indices[0]; i++) {
            equi_cntr += checkif_triangle_then_fill(&M[equi_tmp_indices[i]],
                                                    vec1, vec2, sum_vec,
                                                    &equi_tmp_triangles[equi_cntr]);
          }
        }
      } else if (vec1_length == vec2_length || vec2_length == vec3_length
                 || vec1_length == vec3_length) {
        select_modes_with_length(&M, vec3_length, iso_tmp_indices);
        if (iso_tmp_indices[0] > 0) {
          for (i = 1; i <= iso_tmp_indices[0]; i++) {
            iso_cntr += checkif_triangle_then_fill(&M[iso_tmp_indices[i]],
                                                   vec1, vec2, sum_vec,
                                                   &iso_tmp_triangles[iso_cntr]);
          }
        }
      } else {
        select_modes_with_length(&M, vec3_length, scal_tmp_indices);
        if (scal_tmp_indices[0] > 0) {
          for (i = 1; i < scal_tmp_indices[0]; i++) {
            scal_cntr += checkif_triangle_then_fill(&M[scal_tmp_indices[i]],
                                                    vec1, vec2, sum_vec,
                                                    &scal_tmp_triangles[scal_cntr]);
          }
        }
      }
    }

    if (equi_cntr != 0) {
      write_struct_triangle_to_file(equi_tmp_triangles, equi_cntr, equi_file,
                                    equi_file_path);
      equi_hldr += equi_cntr;
      equi_cntr = 0;
    }

    if (iso_cntr != 0) {
      write_struct_triangle_to_file(iso_tmp_triangles, iso_cntr, iso_file,
                                    iso_file_path);
      iso_hldr += iso_cntr;
      iso_cntr = 0;
    }

    if (scal_cntr != 0) {
      write_struct_triangle_to_file(scal_tmp_triangles, scal_cntr, scal_file,
                                    scal_file_path);
      scal_hldr += scal_cntr;
      scal_cntr = 0;
    }

    if (index1 % (int)pow(NUM_GRID_IN_EACH_AXIS, 2) == 0) {
      fflush(stdout);
      printf("\nequilateral: %d \t isosceles: %d \t scalene: %d",
             equi_hldr, iso_hldr, scal_hldr);
    }
  }

  fclose(equi_file);
  fclose(iso_file);
  fclose(scal_file);

  done(ft_start);

  return 0;
}
