#include <fftw3.h>
#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/modes_struct.h"

#include "./../struct/single_mode_power_result.h"

single_mode_power_result_struct single_mode_power (double, double,
		fftw_complex *, modes_struct *, config_struct *);
