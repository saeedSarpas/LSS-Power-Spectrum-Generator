CC        = gcc
CFLAGS    = -Wall -std=gnu11
TEST_LIBS = -lcgreen
LIBS      = -lm -lconfig -lfftw3

PYTHON = python
IMAGE_VIEWER = open

.PHONY: ps
ps : clean lemain lhmain grmain ftmain immain psmain

.PHONY: tests
tests : gtest pstest imtest fttest grtest

.PHONY: clean
clean :
	rm -f $(PS_INCLUDE) $(PS_TEST) $(PSDIR)/tests.tst $(PSDIR)/src/main.o \
          $(IM_INCLUDE) $(IM_TEST) $(IMDIR)/tests.tst $(IMDIR)/src/main.o \
          $(FT_INCLUDE) $(FT_TEST) $(FTDIR)/tests.tst $(FTDIR)/src/main.o \
          $(GR_INCLUDE) $(GR_TEST) $(GRDIR)/tests.tst $(GRDIR)/src/main.o \
          $(LE_INCLUDE) $(LE_TEST) $(LHDIR)/tests.tst $(LHDIR)/src/main.o \
          $(LH_INCLUDE) $(LH_TEST) $(LHDIR)/tests.tst $(LHDIR)/src/main.o \
          $(G_TEST) $(G_FUNC)

.PHONY: plot
plot : cleanPlots
	cd $(PSDIR); $(PYTHON) ./plotPowerSpectra.py
	cd $(PSDIR)/plots; $(IMAGE_VIEWER) *.png
	cd $(GRDIR); $(PYTHON) ./PlotDensity.py

.PHONY: cleanPlots
cleanPlots :
	rm -f $(GRDIR)/plots/*.png
	rm -f $(PSDIR)/plots/*.png

.PHONY: cleanOutput
cleanOutput :
	rm -f $(PSDIR)/output/*.dat $(IMDIR)/output/*.dat $(FTDIR)/output/*.dat \
	$(GRDIR)/output/*.dat $(LHDIR)/output/*.dat $(GIDIR)/output/*.dat


#------------------------------------------------------------------------------
# GLOBAL FUNCTIONS
#
  GDIR = ./global_functions
#------------------------------------------------------------------------------
_G_FUNC = clock/done.o \
          clock/start.o \
          config_file/load_config_from.o \
          config_file/my_libconfig.o \
          filenames/generate_filenames.o \
          filenames/free_filenames_struct.o \
          strings/concat.o \
          grid/grid_boundry_checker.o \
          grid/move_along_grid_axis.o \
          grid/one_to_three.o \
          grid/three_to_one.o \
          info_file/get_info_from.o \
          info_file/write_info_to.o \
          io/open_file.o \
          io/read_from.o \
          io/write_to.o \
          memory/allocate.o \
          modes/find_first_mode_with_modulus.o \
          modes/find_last_mode_with_modulus.o \
          modes/sort_modes.o \
          vector/vector.o
G_FUNC  = $(patsubst %,$(GDIR)/%,$(_G_FUNC))

_G_TEST = modes/find_first_mode_with_modulus_test.o \
          modes/find_last_mode_with_modulus_test.o \
          modes/sort_modes_test.o \
          grid/three_to_one_test.o \
          config_file/load_config_from_test.o \
          filenames/generate_filenames_test.o \
          strings/concat_test.o
G_TEST  = $(patsubst %,$(GDIR)/%,$(_G_TEST))

$(G_FUNC) : %.o : %.c
$(G_TEST) : %.o : %.c

$(GDIR)/tests.tst : $(GDIR)/tests.c $(G_FUNC) $(G_TEST)
	$(CC) $< $(G_FUNC) $(G_TEST) $(LIBS) $(TEST_LIBS) $(CFLAGS) -o $@

.PHONY: gtest
gtest : $(GDIR)/tests.tst
	cd $(GDIR); ./tests.tst

#------------------------------------------------------------------------------
# LOAD INPUT HALOTAB
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
# LOAD INPUT z0.7to0.8
#
  LEDIR = ./1a_euclid
#------------------------------------------------------------------------------
_LE_INCLUDE = load_z07to08_from_file.o
LE_INCLUDE  = $(patsubst %,$(LEDIR)/src/include/%,$(_LE_INCLUDE))

$(LE_INCLUDE) : %.o : %.c

$(LEDIR)/src/main.o : $(LEDIR)/src/main.c $(G_FUNC) $(LH_INCLUDE) $(LE_INCLUDE)
	$(CC) $< $(LH_INCLUDE) $(LE_INCLUDE) $(G_FUNC) $(LIBS) $(CFLAGS) -o $@

.PHONY: lemain
lemain : $(LEDIR)/src/main.o
	cd $(LEDIR)/src; ./main.o

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

_GR_TEST = density_contrast_test.o \
           cic_test.o
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
              reordering_fourier_input.o \
              smearing_and_anisotropy_correction_for_ngp.o \
              smearing_and_anisotropy_correction_for_cic.o \
              smearing_and_anisotropy_correction_for_tsc.o
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
_IM_INCLUDE = load_modes_into.o
IM_INCLUDE  = $(patsubst %,$(IMDIR)/src/include/%,$(_IM_INCLUDE))

_IM_TEST = load_modes_into_test.o
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
              signal_power.o \
              generate_logarithmic_bins.o \
              generate_linear_bins.o
PS_INCLUDE  = $(patsubst %,$(PSDIR)/src/include/%,$(_PS_INCLUDE))

_PS_TEST = signal_power_test.o \
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
psmain : $(PSDIR)/src/main.o pstest
	cd $(PSDIR)/src; ./main.o
