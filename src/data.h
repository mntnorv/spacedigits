#include "math.h"

//
// 0--1--2
// |  |  |
// 3--4--5
// |  |  |
// 6--7--8
//

Vec3 vertices[] = {
  {0, 0, 0},
  {0.5, 0, 0},
  {1, 0, 0},
  {0, 0.5, 0},
  {0.5, 0.5, 0},
  {1, 0.5, 0},
  {0, 1, 0},
  {0.5, 1, 0},
  {1, 1, 0}
};

int indexes_0[] = {0, 2, 8, 6, 0, 0};
int indexes_1[] = {2, 8, 8};
int indexes_2[] = {0, 2, 5, 3, 6, 8, 8};
int indexes_3[] = {0, 2, 5, 4, 4, 5, 8, 6, 6};
int indexes_4[] = {0, 3, 5, 5, 2, 8, 8};
int indexes_5[] = {2, 0, 3, 5, 8, 6, 6};
int indexes_6[] = {2, 0, 6, 8, 5, 3, 3};
int indexes_7[] = {0, 2, 8, 8};
int indexes_8[] = {0, 2, 8, 6, 0, 0, 3, 5, 5};
int indexes_9[] = {6, 8, 2, 0, 3, 5, 5};

int index_lengths[] = {
  6, 3, 7, 9, 7, 7, 7, 4, 9, 7
};

int *indexes[] = {
  indexes_0,
  indexes_1,
  indexes_2,
  indexes_3,
  indexes_4,
  indexes_5,
  indexes_6,
  indexes_7,
  indexes_8,
  indexes_9
};

//
//     4
//     5
// 0 1   2 3
//     6
//     7
//

Mat4 transform_0 = {.m = {0, 0, 0.5, 0, 0, 1.8, 0, 0, -1, 0, 0, 0, -1, -0.9, 1.01, 1}};
Mat4 transform_1 = {.m = {0, 0, 0.5, 0, 0, 1.8, 0, 0, -1, 0, 0, 0, -1, -0.9, 1.65, 1}};
Mat4 transform_2 = {.m = {0, 0, -0.5, 0, 0, 1.8, 0, 0, 1, 0, 0, 0, 1, -0.9, 2.15, 1}};
Mat4 transform_3 = {.m = {0, 0, -0.5, 0, 0, 1.8, 0, 0, 1, 0, 0, 0, 1, -0.9, 1.51, 1}};
Mat4 transform_4 = {.m = {1.8, 0, 0, 0, 0, 0, 0.5, 0, 0, -1, 0, 0, -0.9, -1, 1.01, 1}};
Mat4 transform_5 = {.m = {1.8, 0, 0, 0, 0, 0, 0.5, 0, 0, -1, 0, 0, -0.9, -1, 1.65, 1}};
Mat4 transform_6 = {.m = {1.8, 0, 0, 0, 0, 0, -0.5, 0, 0, 1, 0, 0, -0.9, 1, 2.15, 1}};
Mat4 transform_7 = {.m = {1.8, 0, 0, 0, 0, 0, -0.5, 0, 0, 1, 0, 0, -0.9, 1, 1.51, 1}};
