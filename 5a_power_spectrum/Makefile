CC     = gcc
CFLAGS = -Wall

S_DIR   = ./src
I_DIR   = ./src/include
G_DIR   = ./../global_functions

TEST_DIR    = ./tests
TEST_IDIR   = ./tests/include

LIBS      = -lm -lconfig -lfftw3
TEST_LIBS = -lcgreen

_DEPS = load_fourier_transformed_data.o \
        single_mode_power.o \
        rho_tilda.o \
        generate_logarithmic_bins.o
DEPS  = $(patsubst %,$(I_DIR)/%,$(_DEPS))

_TEST_DEPS = single_mode_power_test.o \
             generate_logarithmic_bins_test.o
TEST_DEPS  = $(patsubst %,$(TEST_IDIR)/%,$(_TEST_DEPS))

_G_DEPS = config_file/my_libconfig.o \
          config_file/get_config.o \
          io/get_algorithm_alias.o \
          io/get_input_filename_alias.o \
          io/read_fftw_complex_from.o \
          io/read_modes_struct_from.o \
          filenames/append_input_infos_name.o \
          info_file/read_input_file_infos.o \
          clock/start.o \
          clock/done.o \
          memory/allocation_failing_message.o \
          memory/allocate_double_array.o \
          memory/allocate_fftw_complex.o \
          memory/allocate_modes_struct.o \
          filenames/str_concat.o \
          filenames/append_fourier_transformed_filename.o \
          filenames/append_power_spectrum_filename.o \
          filenames/append_indexed_modes_filename.o \
          open_file.o \
          vector/vector.o \
          grid/grid_boundry_checker.o \
          grid/three_to_one.o \
          modes/get_modes_in_range.o
G_DEPS  = $(patsubst %,$(G_DIR)/%,$(_G_DEPS))

all : $(S_DIR)/main.o

$(S_DIR)/main.o : $(S_DIR)/main.c $(DEPS) $(G_DEPS)
	$(CC) $< $(DEPS) $(G_DEPS) $(LIBS) -o $@

main : test $(S_DIR)/main.o
	cd ./src; ./main.o

$(TEST_DIR)/all_tests.tst : $(TEST_DIR)/all_tests.c $(DEPS) $(G_DEPS) $(TEST_DEPS) $(G_DEPS_OF_TEST)
	$(CC) $< $(DEPS) $(G_DEPS) $(TEST_DEPS) $(LIBS) $(TEST_LIBS) -o $@

test : $(TEST_DIR)/all_tests.tst
	cd ./tests; ./all_tests.tst

clean:
	rm -f $(TEST_DEPS) $(G_DEPS) $(DEPS)

$(DEPS)           : %.o : %.c
$(G_DEPS)         : %.o : %.c
$(TEST_DEPS)      : %.o : %.c
$(G_DEPS_OF_TEST) : %.o : %.c
