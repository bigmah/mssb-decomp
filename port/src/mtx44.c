// 4x4 matrix routines that aurora's MTX library doesn't provide (from strikers).
#include <dolphin/types.h>
#include <dolphin/mtx.h>
#include <string.h>
#include <math.h>

void C_MTX44Identity(f32 m[4][4])
{
    memset(m, 0, sizeof(f32) * 16);
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
}

void C_MTX44Copy(const f32 src[4][4], f32 dst[4][4])
{
    if (src != dst)
        memcpy(dst, src, sizeof(f32) * 16);
}

void C_MTX44Concat(const f32 a[4][4], const f32 b[4][4], f32 ab[4][4])
{
    f32 tmp[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            tmp[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + a[i][3] * b[3][j];
    memcpy(ab, tmp, sizeof(tmp));
}

void C_MTX44Transpose(const f32 src[4][4], f32 xPose[4][4])
{
    f32 tmp[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            tmp[i][j] = src[j][i];
    memcpy(xPose, tmp, sizeof(tmp));
}

void C_MTX44Scale(f32 m[4][4], f32 xS, f32 yS, f32 zS)
{
    C_MTX44Identity(m);
    m[0][0] = xS;
    m[1][1] = yS;
    m[2][2] = zS;
}

void C_MTX44Trans(f32 m[4][4], f32 xT, f32 yT, f32 zT)
{
    C_MTX44Identity(m);
    m[0][3] = xT;
    m[1][3] = yT;
    m[2][3] = zT;
}

// Gauss-Jordan elimination with partial pivoting; returns 0 if singular.
u32 C_MTX44Inverse(const f32 src[4][4], f32 inv[4][4])
{
    f32 a[4][8];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            a[i][j] = src[i][j];
            a[i][j + 4] = (i == j) ? 1.0f : 0.0f;
        }
    }
    for (int c = 0; c < 4; c++)
    {
        int pivot = c;
        for (int r = c + 1; r < 4; r++)
            if (fabsf(a[r][c]) > fabsf(a[pivot][c]))
                pivot = r;
        if (a[pivot][c] == 0.0f)
            return 0;
        if (pivot != c)
        {
            for (int j = 0; j < 8; j++)
            {
                f32 t = a[c][j];
                a[c][j] = a[pivot][j];
                a[pivot][j] = t;
            }
        }
        f32 d = 1.0f / a[c][c];
        for (int j = 0; j < 8; j++)
            a[c][j] *= d;
        for (int r = 0; r < 4; r++)
        {
            if (r == c)
                continue;
            f32 f = a[r][c];
            for (int j = 0; j < 8; j++)
                a[r][j] -= f * a[c][j];
        }
    }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            inv[i][j] = a[i][j + 4];
    return 1;
}

void C_MTX44RotRad(f32 m[4][4], char axis, f32 rad)
{
    f32 s = sinf(rad);
    f32 c = cosf(rad);
    memset(m, 0, sizeof(f32) * 16);
    m[3][3] = 1.0f;
    switch (axis)
    {
    case 'x':
    case 'X':
        m[0][0] = 1.0f;
        m[1][1] = c;
        m[1][2] = -s;
        m[2][1] = s;
        m[2][2] = c;
        break;
    case 'y':
    case 'Y':
        m[0][0] = c;
        m[0][2] = s;
        m[1][1] = 1.0f;
        m[2][0] = -s;
        m[2][2] = c;
        break;
    case 'z':
    case 'Z':
        m[0][0] = c;
        m[0][1] = -s;
        m[1][0] = s;
        m[1][1] = c;
        m[2][2] = 1.0f;
        break;
    }
}

void PSMTX44MultVec(const f32 m[4][4], const Vec* src, Vec* dst)
{
    Vec v = *src;
    f32 w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3];
    dst->x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
    dst->y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
    dst->z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
    if (w != 0.0f)
    {
        w = 1.0f / w;
        dst->x *= w;
        dst->y *= w;
        dst->z *= w;
    }
}

void PSMTX44MultVecArray(const f32 m[4][4], const Vec* src, Vec* dst, u32 count)
{
    for (u32 i = 0; i < count; i++)
        PSMTX44MultVec(m, &src[i], &dst[i]);
}
