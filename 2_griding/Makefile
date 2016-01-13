CC     = gcc
PYTHON = python2
CFLAGS = -Wall

S_DIR   = ./src
I_DIR   = ./src/include
G_DIR   = ./../global_functions

TEST_DIR    = ./tests
TEST_IDIR   = ./tests/include

LIBS      = -lm -lconfig
TEST_LIBS = -lm -lcgreen -lconfig

_DEPS = load_input.o \
        density_contrast.o \
        cic.o \
        tsc.o \
        ngp.o
DEPS  = $(patsubst %,$(I_DIR)/%,$(_DEPS))

_TEST_DEPS = density_contrast_test.o
TEST_DEPS  = $(patsubst %,$(TEST_IDIR)/%,$(_TEST_DEPS))

_G_DEPS = config_file/my_libconfig.o \
          config_file/get_config.o \
          io/get_algorithm_alias.o \
          io/get_input_filename_alias.o \
          io/read_particle_data_struct_from.o \
          io/write_double_to.o \
          clock/start.o \
          clock/done.o \
          memory/allocation_failing_message.o \
          memory/allocate_particle_data_struct.o \
          memory/allocate_double_array.o \
          filenames/str_concat.o \
          filenames/append_input_infos_name.o \
          filenames/append_input_name.o \
          filenames/append_density_contrast_filename.o \
          info_file/read_input_file_infos.o \
          grid/grid_boundry_checker.o \
          grid/three_to_one.o \
          grid/move_along_grid_axis.o \
          open_file.o
G_DEPS  = $(patsubst %,$(G_DIR)/%,$(_G_DEPS))

all : $(S_DIR)/main.o $(TEST_DIR)/all_tests.tst

$(S_DIR)/main.o : $(S_DIR)/main.c $(G_DEPS) $(DEPS)
	$(CC) -o $@ $(CFLAGS) $< $(G_DEPS) $(DEPS) $(LIBS)

main : test $(S_DIR)/main.o
	cd ./src; ./main.o

$(TEST_DIR)/all_tests.tst : $(TEST_DIR)/all_tests.c $(TEST_DEPS) $(G_DEPS) $(DEPS)
	$(CC) -o $@ $< $(TEST_DEPS) $(G_DEPS) $(DEPS) $(TEST_LIBS)

test : $(TEST_DIR)/all_tests.tst
	cd ./tests; ./all_tests.tst

plot :
	$(PYTHON) ./PlotDensity.py


clean:
	rm -f $(TEST_DEPS) $(G_DEPS) $(DEPS)

$(DEPS)      : %.o : %.c
$(G_DEPS)    : %.o : %.c
$(TEST_DEPS) : %.o : %.c
