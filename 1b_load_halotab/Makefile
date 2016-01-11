CC     = gcc
CFLAGS = -Wall

S_DIR   = ./src
I_DIR   = ./src/include
G_DIR   = ./../global_functions

TEST_DIR    = ./tests
TEST_IDIR   = ./tests/include

LIBS      = -lconfig
TEST_LIBS = -lcgreen -lconfig

_DEPS = get_number_of_lines.o \
        load_halotab_from_file.o
DEPS  = $(patsubst %,$(I_DIR)/%,$(_DEPS))

_TEST_DEPS = get_number_of_lines_test.o \
             load_halotab_from_file_test.o
TEST_DEPS  = $(patsubst %,$(TEST_IDIR)/%,$(_TEST_DEPS))

_G_DEPS = clock/start.o \
          clock/done.o \
          open_file.o \
          memory/allocation_failing_message.o \
          memory/allocate_particle_data_struct.o \
          filenames/str_concat.o \
          filenames/append_input_name.o \
          filenames/append_input_infos_name.o \
          io/write_particle_data_struct_to.o \
          config_file/my_libconfig.o \
          config_file/get_config.o \
          info_file/write_input_file_infos_to.o
G_DEPS  = $(patsubst %,$(G_DIR)/%,$(_G_DEPS))

all : $(S_DIR)/main.o $(TEST_DIR)/all_tests.tst

$(S_DIR)/main.o : $(S_DIR)/main.c $(G_DEPS) $(DEPS)
	$(CC) -o $@ $(CFLAGS) $< $(G_DEPS) $(DEPS) $(LIBS)

main : $(S_DIR)/main.o
	cd ./src; ./main.o

$(TEST_DIR)/all_tests.tst : $(TEST_DIR)/all_tests.c $(TEST_DEPS) $(G_DEPS) $(DEPS)
	$(CC) -o $@ $< $(TEST_DEPS) $(G_DEPS) $(DEPS) $(TEST_LIBS)

test : $(TEST_DIR)/all_tests.tst
	cd ./tests; ./all_tests.tst

clean:
	rm -f $(TEST_DEPS) $(G_DEPS) $(DEPS)

$(DEPS)      : %.o : %.c
$(G_DEPS)    : %.o : %.c
$(TEST_DEPS) : %.o : %.c
