CC     = gcc
CFLAGS = -Wall

S_DIR   = ./src
I_DIR   = ./src/include
G_DIR   = ./../global_functions

TEST_DIR    = ./tests
TEST_IDIR   = ./tests/include

LIBS      = -lm -lconfig -lfftw3
TEST_LIBS = -lcgreen

_G_DEPS = config_file/my_libconfig.o \
          config_file/get_config.o \
          clock/start.o \
          clock/done.o \
          memory/allocation_failing_message.o \
          memory/allocate_modes_struct.o \
          grid/grid_boundry_checker.o \
          grid/three_to_one.o \
          filenames/str_concat.o \
          filenames/append_indexed_modes_filename.o \
          open_file.o \
          io/write_modes_struct_to.o
G_DEPS  = $(patsubst %,$(G_DIR)/%,$(_G_DEPS))

all : $(S_DIR)/main.o

$(S_DIR)/main.o : $(S_DIR)/main.c $(G_DEPS)
	$(CC) $< $(G_DEPS) $(LIBS) -o $@

main : $(S_DIR)/main.o
	cd ./src; ./main.o

clean:
	rm -f $(TEST_DEPS) $(G_DEPS_OF_DEPS) $(G_DEPS) $(DEPS)

$(G_DEPS)         : %.o : %.c
$(TEST_DEPS)      : %.o : %.c
$(G_DEPS_OF_TEST) : %.o : %.c
