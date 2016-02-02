CC        = gcc
CFLAGS    = -Wall -std=gnu11
TEST_LIBS = -lcgreen
LIBS      = -lm -lconfig -lfftw3

PYTHON = python2

.PHONY: tests
tests : gtest pstest imtest fttest grtest

.PHONY: clean
clean :
	rm -f $(G_TEST) $(G_FUNC) \
          $(PS_INCLUDE) $(PS_TEST) $(PSDIR)/tests.tst $(PSDIR)/src/main.o \
          $(IM_INCLUDE) $(IM_TEST) $(IMDIR)/tests.tst $(IMDIR)/src/main.o \
          $(FT_INCLUDE) $(FT_TEST) $(FTDIR)/tests.tst $(FTDIR)/src/main.o \
          $(GR_INCLUDE) $(GR_TEST) $(GRDIR)/tests.tst $(GRDIR)/src/main.o \
          $(LH_INCLUDE) $(LH_TEST) $(LHDIR)/tests.tst $(LHDIR)/src/main.o \
          $(GIDIR)/src/main.o

.PHONY: plot
plot :
	cd $(PSDIR); $(PYTHON) ./plotPowerSpectra.py
	cd $(GRDIR); $(PYTHON) ./PlotDensity.py


.PHONY: cleanPlots
cleanPlots :
	rm -f $(GRDIR)/plots/*.png
	rm -f $(PSDIR)/plots/*.png

#------------------------------------------------------------------------------
# GLOBAL FUNCTIONS
#
  GDIR = ./global_functions
#------------------------------------------------------------------------------
_G_FUNC = clock/done.o \
          clock/start.o \
          config_file/get_config.o \
          config_file/my_libconfig.o \
          filenames/append_density_contrast_filename.o \
          filenames/append_fourier_transformed_filename.o \
          filenames/append_indexed_modes_filename.o \
          filenames/append_input_info_name.o \
          filenames/append_input_name.o \
          filenames/append_power_spectrum_filename.o \
          filenames/str_concat.o \
          grid/grid_boundry_checker.o \
          grid/move_along_grid_axis.o \
          grid/one_to_three.o \
          grid/three_to_one.o \
          info_file/read_input_file_info.o \
          info_file/write_input_file_info_to.o \
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
          memory/allocate_input_file_info_struct.o \
          memory/allocate_modes_struct.o \
          memory/allocate_particle_data_struct.o \
          memory/allocation_failing_message.o \
          modes/get_modes_in_range.o \
          vector/vector.o \
          open_file.o
G_FUNC  = $(patsubst %,$(GDIR)/%,$(_G_FUNC))

_G_TEST = modes/get_modes_in_range_test.o
G_TEST  = $(patsubst %,$(GDIR)/%,$(_G_TEST))

$(G_FUNC) : %.o : %.c
$(G_TEST) : %.o : %.c

$(GDIR)/tests.tst : $(GDIR)/tests.c $(G_FUNC) $(G_TEST)
	$(CC) $< $(G_FUNC) $(G_TEST) $(LIBS) $(TEST_LIBS) $(CFLAGS) -o $@

.PHONY: gtest
gtest : $(GDIR)/tests.tst
	cd $(GDIR); ./tests.tst

#------------------------------------------------------------------------------
# GENERATE RANDOM INPUT
#
  GIDIR = ./1a_generate_random_input
#------------------------------------------------------------------------------
$(GIDIR)/src/main.o : $(GIDIR)/src/main.c $(G_FUNC)
	$(CC) $< $(G_FUNC) $(LIBS) $(CFLAGS) -o $@

.PHONY: gimain
gimain : $(GIDIR)/src/main.o
	cd $(GIDIR)/src; ./main.o

#------------------------------------------------------------------------------
# LOAD INPUT
#
  LHDIR = ./1b_load_halotab
#------------------------------------------------------------------------------
_LH_INCLUDE = get_number_of_lines.o \
              load_halotab_from_file.o
LH_INCLUDE  = $(patsubst %,$(LHDIR)/src/include/%,$(_LH_INCLUDE))

_LH_TEST = get_number_of_lines_test.o \
           load_halotab_from_file_test.o
LH_TEST  = $(patsubst %,$(LHDIR)/src/include/%,$(_LH_TEST))

$(LH_INCLUDE) : %.o : %.c
$(LH_TEST)    : %.o : %.c

$(LHDIR)/tests.tst : $(LHDIR)/tests.c $(G_FUNC) $(LH_INCLUDE) $(LH_TEST)
	$(CC) $< $(G_FUNC) $(LH_INCLUDE) $(LH_TEST) $(LIBS) $(TEST_LIBS) $(CFLAGS) -o $@

.PHONY: lhtest
lhtest : $(LHDIR)/tests.tst
	cd $(LHDIR); ./tests.tst

$(LHDIR)/src/main.o : $(LHDIR)/src/main.c $(G_FUNC) $(LH_INCLUDE)
	$(CC) $< $(LH_INCLUDE) $(G_FUNC) $(LIBS) $(CFLAGS) -o $@

.PHONY: lhmain
lhmain : lhtest $(LHDIR)/src/main.o
	cd $(LHDIR)/src; ./main.o

#------------------------------------------------------------------------------
# GRIDING
#
  GRDIR = ./2_griding
#------------------------------------------------------------------------------
_GR_INCLUDE = load_input.o \
              density_contrast.o \
              cic.o \
              tsc.o \
              ngp.o
GR_INCLUDE  = $(patsubst %,$(GRDIR)/src/include/%,$(_GR_INCLUDE))

_GR_TEST = density_contrast_test.o
GR_TEST  = $(patsubst %,$(GRDIR)/src/include/%,$(_GR_TEST))

$(GR_INCLUDE) : %.o : %.c
$(GR_TEST)    : %.o : %.c

$(GRDIR)/tests.tst : $(GRDIR)/tests.c $(G_FUNC) $(GR_INCLUDE) $(GR_TEST)
	$(CC) $< $(G_FUNC) $(GR_INCLUDE) $(GR_TEST) $(LIBS) $(TEST_LIBS) $(CFLAGS) -o $@

.PHONY: grtest
grtest : $(GRDIR)/tests.tst
	cd $(GRDIR); ./tests.tst

$(GRDIR)/src/main.o : $(GRDIR)/src/main.c $(G_FUNC) $(GR_INCLUDE)
	$(CC) $< $(GR_INCLUDE) $(G_FUNC) $(LIBS) $(CFLAGS) -o $@

.PHONY: grmain
grmain : grtest $(GRDIR)/src/main.o
	cd $(GRDIR)/src; ./main.o

#------------------------------------------------------------------------------
# FAST FOURIER TRANSFORM
#
  FTDIR = ./3_fftw
#------------------------------------------------------------------------------
_FT_INCLUDE = load_density_contrast_grid.o \
              convert_real_delta_to_complex.o \
              reordering_fourier_input.o
FT_INCLUDE  = $(patsubst %,$(FTDIR)/src/include/%,$(_FT_INCLUDE))

_FT_TEST = reordering_fourier_input_test.o \
           convert_real_delta_to_complex_test.o
FT_TEST  = $(patsubst %,$(FTDIR)/src/include/%,$(_FT_TEST))

$(FT_INCLUDE) : %.o : %.c
$(FT_TEST)    : %.o : %.c

$(FTDIR)/tests.tst : $(FTDIR)/tests.c $(G_FUNC) $(FT_INCLUDE) $(FT_TEST)
	$(CC) $< $(G_FUNC) $(FT_INCLUDE) $(FT_TEST) $(LIBS) $(TEST_LIBS) $(CFLAGS) -o $@

.PHONY: fttest
fttest : $(FTDIR)/tests.tst
	cd $(FTDIR); ./tests.tst

$(FTDIR)/src/main.o : $(FTDIR)/src/main.c $(G_FUNC) $(FT_INCLUDE)
	$(CC) $< $(FT_INCLUDE) $(G_FUNC) $(LIBS) $(CFLAGS) -o $@

.PHONY: ftmain
ftmain : fttest $(FTDIR)/src/main.o
	cd $(FTDIR)/src; ./main.o

#------------------------------------------------------------------------------
# INDEXING FOURIER MODES
#
  IMDIR = ./4_indexing_k_modulus
#------------------------------------------------------------------------------
_IM_INCLUDE = load_modes_into.o \
              sort.o
IM_INCLUDE  = $(patsubst %,$(IMDIR)/src/include/%,$(_IM_INCLUDE))

_IM_TEST = load_modes_into_test.o \
           sort_test.o
IM_TEST  = $(patsubst %,$(IMDIR)/src/include/%,$(_IM_TEST))

$(IM_INCLUDE) : %.o : %.c
$(IM_TEST)    : %.o : %.c

$(IMDIR)/tests.tst : $(IMDIR)/tests.c $(G_FUNC) $(IM_INCLUDE) $(IM_TEST)
	$(CC) $< $(G_FUNC) $(IM_INCLUDE) $(IM_TEST) $(LIBS) $(TEST_LIBS) $(CFLAGS) -o $@

.PHONY: imtest
imtest : $(IMDIR)/tests.tst
	cd $(IMDIR); ./tests.tst

$(IMDIR)/src/main.o : $(IMDIR)/src/main.c $(G_FUNC) $(IM_INCLUDE)
	$(CC) $< $(IM_INCLUDE) $(G_FUNC) $(LIBS) $(CFLAGS) -o $@

.PHONY: immain
immain : imtest $(IMDIR)/src/main.o
	cd $(IMDIR)/src; ./main.o

#------------------------------------------------------------------------------
# POWER SPECTRUM
#
  PSDIR = ./5a_power_spectrum
#------------------------------------------------------------------------------
_PS_INCLUDE = load_fourier_transformed_data.o \
              single_mode_power.o \
              generate_logarithmic_bins.o
PS_INCLUDE  = $(patsubst %,$(PSDIR)/src/include/%,$(_PS_INCLUDE))

_PS_TEST = single_mode_power_test.o \
           generate_logarithmic_bins_test.o
PS_TEST  = $(patsubst %,$(PSDIR)/src/include/%,$(_PS_TEST))

$(PS_INCLUDE) : %.o : %.c
$(PS_TEST)    : %.o : %.c

$(PSDIR)/tests.tst : $(PSDIR)/tests.c $(G_FUNC) $(PS_INCLUDE) $(PS_TEST) $(IM_INCLUDE)
	$(CC) $< $(G_FUNC) $(PS_INCLUDE) $(PS_TEST) $(IM_INCLUDE) $(LIBS) $(TEST_LIBS) $(CFLAGS) -o $@

.PHONY: pstest
pstest : $(PSDIR)/tests.tst
	cd $(PSDIR); ./tests.tst

$(PSDIR)/src/main.o : $(PSDIR)/src/main.c $(G_FUNC) $(PS_INCLUDE)
	$(CC) $< $(PS_INCLUDE) $(G_FUNC) $(LIBS) $(CFLAGS) -o $@

.PHONY: psmain
psmain : pstest $(PSDIR)/src/main.o
	cd $(PSDIR)/src; ./main.o
