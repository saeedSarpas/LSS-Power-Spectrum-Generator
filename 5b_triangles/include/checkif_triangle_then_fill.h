int checkif_triangle_then_fill(struct modes * M, int * vec1, int * vec2,
                                int * sum_vec, struct triangles * tmp) {
  int i;

  if (M->kx + sum_vec[0] == 0) {
    if (M->ky + sum_vec[1] == 0) {
      if (M->kz + sum_vec[2] == 0) {

        for (i = 0; i < 3; i++) {
          tmp->k1[i] = vec1[i];

          tmp->k2[i] = vec2[i];
          tmp->k3[i] = - sum_vec[i];
        }

        return 1;
      }
    }
  }

  return 0;
}
