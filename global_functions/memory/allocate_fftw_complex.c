#include <complex.h>
#include <fftw.h>

#include "./allocation_failing_message.h"

void allocate_fftw_complex(fftw_complex **f, size_t size) {
  if (!(*f = calloc(size, sizeof(fftw_complex)))) {
    allocation_failing_message("fftw_complex", size);
    exit(0);
  }
}
