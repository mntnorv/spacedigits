#ifndef INCLUDED_SD_MATH_H
#define INCLUDED_SD_MATH_H

#define HALF_WIDTH  72
#define HALF_HEIGHT 84

//==============================================================================

typedef struct Vec3 {
  float x, y, z;
} Vec3;

#define Vec3(x, y, z) ((Vec3){(x), (y), (z)})

//==============================================================================

void vec3_project(GPoint *out_v, const Vec3 *v) {
  out_v->x = (int) (((v->x / v->z) + 1) * HALF_WIDTH);
  out_v->y = (int) (((v->y / v->z) + 1) * HALF_HEIGHT);
}

//==============================================================================

typedef struct Mat4 {
  float m[16];
} Mat4;

enum Mat4RowCol  // column-major
{
  _00 = 0,
  _10,
  _20,
  _30,
  
  _01,
  _11,
  _21,
  _31,
  
  _02,
  _12,
  _22,
  _32,
  
  _03,
  _13,
  _23,
  _33
};

void mat4_multiply_vec3(Vec3* out_v, const Mat4* m, const Vec3* v) {
  float inv_w = 1.0f / (m->m[_30] * v->x + m->m[_31] * v->y + m->m[_32] * v->z + m->m[_33]);
  
  out_v->x = (m->m[_00] * v->x + m->m[_01] * v->y + m->m[_02] * v->z + m->m[_03]) * inv_w;
  out_v->y = (m->m[_10] * v->x + m->m[_11] * v->y + m->m[_12] * v->z + m->m[_13]) * inv_w;
  out_v->z = (m->m[_20] * v->x + m->m[_21] * v->y + m->m[_22] * v->z + m->m[_23]) * inv_w;
}

#endif
