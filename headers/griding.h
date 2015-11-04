int threeToOne(int i, int j, int k) {
    if (i > numGrid - 1) {
        i = i - numGrid;
    } else if (i < 0) {
        i = i + numGrid;
    }

    if (j > numGrid - 1) {
        j = j - numGrid;
    } else if (j < 0) {
        j = j + numGrid;
    }

    if (k > numGrid - 1) {
        k = k - numGrid;
    } else if (k < 0) {
        k = k + numGrid;
    }

    return(k * numGrid * numGrid + j * numGrid + i);
}

void NGP (struct particle_data P, float * mass_grid) {
    int i, j, k;

    i = P.Pos[0] / gridSize;
    j = P.Pos[1] / gridSize;
    k = P.Pos[2] / gridSize;

    int index = threeToOne(i, j, k);

    mass_grid[index] += P.Mass;
}

void cicWeight (int index, int * delta, float overlap, float * weight) {
    float grid_half_size = gridSize / 2.0;

    if (overlap > grid_half_size) {
        *weight = 1 - (overlap / gridSize) + 0.5;
    } else {
        *weight = (overlap / gridSize) + 0.5;
    }
}

void CIC (struct particle_data P, float * mass_grid) {
    int i, j, k;
    int di, dj, dk;

    float i_weight, j_weight, k_weight;
    float overlap_temp;

    i = P.Pos[0] / gridSize;
    overlap_temp = fmodf(P.Pos[0], gridSize);
    cicWeight(i, &di, overlap_temp, &i_weight);

    j = P.Pos[1] / gridSize;
    overlap_temp = fmodf(P.Pos[1], gridSize);
    cicWeight(j, &dj, overlap_temp, &j_weight);

    k = P.Pos[2] / gridSize;
    overlap_temp = fmodf(P.Pos[2], gridSize);
    cicWeight(k, &dk, overlap_temp, &k_weight);

    int index_temp;
    index_temp = threeToOne(i, j, k);
    mass_grid[index_temp] += i_weight * j_weight * k_weight * P.Mass;

    index_temp = threeToOne(i+di, j, k);
    mass_grid[index_temp] += (1 - i_weight) * j_weight * k_weight * P.Mass;

    index_temp = threeToOne(i, j+dj, k);
    mass_grid[index_temp] += i_weight * (1 - j_weight) * k_weight * P.Mass;

    index_temp = threeToOne(i, j, k+dk);
    mass_grid[index_temp] += i_weight * j_weight * (1 - k_weight) * P.Mass;

    index_temp = threeToOne(i+di, j+dj, k);
    mass_grid[index_temp] += (1 - i_weight) * (1 - j_weight) * k_weight * P.Mass;

    index_temp = threeToOne(i, j+dj, k+dk);
    mass_grid[index_temp] += i_weight * (1 - j_weight) * (1 - k_weight) * P.Mass;

    index_temp = threeToOne(i+di, j, k+dk);
    mass_grid[index_temp] += (1 - i_weight) * j_weight * (1 - k_weight) * P.Mass;

    index_temp = threeToOne(i+di, j+dj, k+dk);
    mass_grid[index_temp] += (1 - i_weight) * (1 - j_weight) * (1 - k_weight) * P.Mass;
}
