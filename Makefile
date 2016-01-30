CC     = gcc
CFLAGS = -Wall -std=gnu11

GDIR   = ./global_functions

LIBS      = -lm -lconfig -lfftw3
TEST_LIBS = -lcgreen

_G_FUNC = clock/done.o \
          clock/start.o \
          config_file/get_config.o \
          config_file/my_libconfig.o \
          filenames/append_density_contrast_filename.o \
          filenames/append_fourier_transformed_filename.o \
          filenames/append_indexed_modes_filename.o \
          filenames/append_input_infos_name.o \
          filenames/append_input_name.o \
          filenames/append_power_spectrum_filename.o \
          filenames/str_concat.o \
          grid/grid_boundry_checker.o \
          grid/move_along_grid_axis.o \
          grid/one_to_three.o \
          grid/three_to_one.o \
          info_file/read_input_file_infos.o \
          info_file/write_input_file_infos_to.o \
          io/get_algorithm_alias.o \
          io/get_input_filename_alias.o \
          io/read_double_from.o \
          io/read_fftw_complex_from.o \
          io/read_modes_struct_from.o \
          io/read_particle_data_struct_from.o \
          io/write_double_to.o \
          io/write_fftw_complex_to.o \
          io/write_modes_struct_to.o \
          io/write_particle_data_struct_to.o \
          memory/allocate_config_struct.o \
          memory/allocate_double_array.o \
          memory/allocate_fftw_complex.o \
          memory/allocate_input_file_infos_struct.o \
          memory/allocate_modes_struct.o \
          memory/allocate_particle_data_struct.o \
          memory/allocation_failing_message.o \
          modes/get_modes_in_range.o \
          vector/vector.o \
          open_file.o
G_FUNC  = $(patsubst %,$(GDIR)/%,$(_G_FUNC))

_G_TEST = modes/get_modes_in_range_test.o
G_TEST  = $(patsubst %,$(GDIR)/%,$(_G_TEST))

all_tests : $(GDIR)/tests.tst

gtest : $(GDIR)/tests.tst
	cd $(GDIR); ./tests.tst

$(GDIR)/tests.tst : $(GDIR)/tests.c $(G_FUNC) $(G_TEST)
	$(CC) $< $(G_FUNC) $(G_TEST) $(LIBS) $(TEST_LIBS) -o $@

clean:
	rm -f $(G_TEST) $(G_FUNC)

$(G_FUNC) : %.o : %.c
$(G_TEST) : %.o : %.c
