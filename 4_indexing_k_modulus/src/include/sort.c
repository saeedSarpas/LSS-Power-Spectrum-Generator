#include <stdlib.h>
#include <math.h>

#include "./../../../global_structs/modes_struct.h"
#include "./../../../global_structs/config_struct.h"

int compare(const void*, const void*);

void sort(modes_struct *modes_array, config_struct *conf) {
	int tot_num_of_grids = pow(conf->params.numOfAxisGrids, 3);

	qsort((void *) modes_array, tot_num_of_grids, sizeof(struct modes), compare);
}

int compare(const void *p1, const void *p2)
{
	const modes_struct *elem1 = p1;
	const modes_struct *elem2 = p2;

	if ( elem1->modulus < elem2->modulus)
		return -1;
	else if (elem1->modulus > elem2->modulus)
		return 1;
	else
		return 0;
}

