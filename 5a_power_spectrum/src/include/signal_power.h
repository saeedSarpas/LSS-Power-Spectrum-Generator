#include <fftw3.h>
#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/modes_struct.h"

#include "./../struct/signal_power_result.h"

signal_power_result_struct signal_power (double, double,
		fftw_complex *, modes_struct *, config_struct *);
