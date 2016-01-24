#include <stdlib.h>
#include <math.h>

#include "./../../../global_structs/modes_struct.h"
#include "./../../../global_structs/config_struct.h"

int compare(const void*, const void*);

void sort(modes *modes_array, config *conf) {
	int tot_num_of_grids = pow(conf->num_of_grids_in_each_axis, 3);

	qsort((void *) modes_array,
			tot_num_of_grids,
			sizeof(modes),
			compare);

}

int compare(const void *p1, const void *p2)
{
	const modes *elem1 = p1;
	const modes *elem2 = p2;

	if ( elem1->length < elem2->length)
		return -1;
	else if (elem1->length > elem2->length)
		return 1;
	else
		return 0;
}

