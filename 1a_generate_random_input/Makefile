CC     = gcc
CFLAGS = -Wall

S_DIR   = ./src
G_DIR   = ./../global_functions

LIBS      = -lconfig

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

all : $(S_DIR)/main.o

$(S_DIR)/main.o : $(S_DIR)/main.c
	$(CC) -o $@ $(CFLAGS) $< $(G_DEPS) $(LIBS)

main : $(S_DIR)/main.o
	cd ./src; ./main.o

clean:
	rm -f $(G_DEPS) $(S_DIR)/main.o

$(G_DEPS)    : %.o : %.c
