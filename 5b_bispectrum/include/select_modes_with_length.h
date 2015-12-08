void get_mode_length (struct modes * M[], int * index, double * m_length) {
  if (*index < 0) {
    *m_length = -1.0;
    *index = 0;
  } else if (*index >= pow(NUM_GRID_IN_EACH_AXIS, 3)) {
    *m_length = pow(NUM_GRID_IN_EACH_AXIS, 3);
    *index = pow(NUM_GRID_IN_EACH_AXIS, 3);
  } else {
    *m_length = (*M)[*index].length;
  }
}

void select_modes_with_length (struct modes * M[], double length, int * indices) {

  double m_length;
  int total_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);
  int temp_index = total_num_grid / 2;
  int jump = temp_index, jump_dir = 0;

  while (jump > 4) {
    jump /= 2;

    get_mode_length(M, &temp_index, &m_length);

    if (m_length > length) {
      temp_index -= jump;
      jump_dir = -1;
    } else if (m_length < length) {
      temp_index += jump;
      jump_dir = 1;
    } else {
      jump = 0;
    }
  }

  bool on = true;

  while (on) {
    temp_index -= 4;

    get_mode_length(M, &temp_index, &m_length);

    if (m_length < length) {
      on = false;
    }
  }

  double epsilon = 1e-7;
  indices[0] = 0;

  do {
    temp_index++;
    get_mode_length(M, &temp_index, &m_length);
    if (fabs(m_length - length) < epsilon) {
      indices[0]++;
      indices[indices[0]] = temp_index;
    }
  } while (m_length <= length);
}
