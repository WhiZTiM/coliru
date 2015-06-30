Matrix33 Matrix33::inverted() const
{
  Matrix33 _m;
  float d = det();
  assert(d > VERY_SMALL_NUMBER);

  _m._11 = _22 * _33 - _23 * _32;
  _m._12 = -(_21 * _33 - _23 * _31);
  _m._13 = _21 * _32 - _22 * _31;
  _m._21 = -(_12 * _33 - _13 * _32);
  _m._22 = _11 * _33 - _13 * _31;
  _m._23 = -(_11 * _32 - _12 * _31);
  _m._31 = _12 * _23 - _13 * _22;
  _m._32 = -(_11 * _23 - _13 * _21);
  _m._33 = _11 * _22 - _12 * _21;

  Matrix33 result;
  for (int i = 0; i < 3; i++)
  for (int j = 0; j < 3; j++)
    result.m[i][j] = _m.m[j][i] / d;

  return result;
}
