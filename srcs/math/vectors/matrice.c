#include "../../../include/miniRT.h"

t_matrice3x3 matrice_rotation_x(double alpha)
{
	t_matrice3x3 rx;
	rx.m[0][0] = 1.0; 
	rx.m[0][1] = 0.0; 
	rx.m[0][2] = 0.0;

    rx.m[1][0] = 0.0; 
	rx.m[1][1] = cos(alpha); 
	rx.m[1][2] = -sin(alpha);

    rx.m[2][0] = 0.0; 
	rx.m[2][1] = sin(alpha); 
	rx.m[2][2] = cos(alpha);

	return rx;
}

// t_matrice4x4 matrice_rotation_x(double alpha)
// {
//     t_matrice4x4 m;
//     double c = cos(angle);
//     double s = sin(angle);

//     m.m[0][0] = 1.0;
//     m.m[0][1] = 0.0;
//     m.m[0][2] = 0.0;
//     m.m[0][3] = 0.0;
//     m.m[1][0] = 0.0;
//     m.m[1][1] = c;
//     m.m[1][2] = -s;
//     m.m[1][3] = 0.0;
//     m.m[2][0] = 0.0;
//     m.m[2][1] = s;
//     m.m[2][2] = c;
//     m.m[2][3] = 0.0;
//     m.m[3][0] = 0.0;
//     m.m[3][1] = 0.0;
//     m.m[3][2] = 0.0;
//     m.m[3][3] = 1.0;

//     return m;
// }

// t_matrice4x4 matrice_rotation_z(double angle)
// {
//     t_matrice4x4 m;
//     double c = cos(angle);
//     double s = sin(angle);

//     m.m[0][0] = c;   m.m[0][1] = -s;  m.m[0][2] = 0.0; m.m[0][3] = 0.0;
//     m.m[1][0] = s;   m.m[1][1] = c;   m.m[1][2] = 0.0; m.m[1][3] = 0.0;
//     m.m[2][0] = 0.0; m.m[2][1] = 0.0; m.m[2][2] = 1.0; m.m[2][3] = 0.0;
//     m.m[3][0] = 0.0; m.m[3][1] = 0.0; m.m[3][2] = 0.0; m.m[3][3] = 1.0;

//     return m;
// }


// t_matrice4x4 matrice_rotation_y(double angle)
// {
//     t_matrice4x4 m;
//     double c = cos(angle);
//     double s = sin(angle);

//     m.m[0][0] = c;   m.m[0][1] = 0.0; m.m[0][2] = s;   m.m[0][3] = 0.0;
//     m.m[1][0] = 0.0; m.m[1][1] = 1.0; m.m[1][2] = 0.0; m.m[1][3] = 0.0;
//     m.m[2][0] = -s;  m.m[2][1] = 0.0; m.m[2][2] = c;   m.m[2][3] = 0.0;
//     m.m[3][0] = 0.0; m.m[3][1] = 0.0; m.m[3][2] = 0.0; m.m[3][3] = 1.0;

//     return m;
// }


t_matrice3x3 matrice_rotation_y(double beta)
{
    t_matrice3x3 ry;

    ry.m[0][0] = cos(beta); 
	ry.m[0][1] = 0.0; 
	ry.m[0][2] = sin(beta);

    ry.m[1][0] = 0.0; 
	ry.m[1][1] = 1.0; 
	ry.m[1][2] = 0.0;

    ry.m[2][0] = -sin(beta); 
	ry.m[2][1] = 0.0; 
	ry.m[2][2] = cos(beta);

    return ry;
}

t_matrice3x3 matrice_rotation_z(double gamma)
{
	t_matrice3x3 rz;

	rz.m[0][0] = cos(gamma); 
	rz.m[0][1] = -sin(gamma); 
	rz.m[0][2] = 0.0;

    rz.m[1][0] = sin(gamma); 
	rz.m[1][1] = cos(gamma); 
	rz.m[1][2] = 0.0;

    rz.m[2][0] = 0.0; 
	rz.m[2][1] = 0.0; 
	rz.m[2][2] = 1.0;

	return(rz);
}

t_matrice3x3 multiplier_matrices(t_matrice3x3 A, t_matrice3x3 B)
{
    t_matrice3x3 R;

    R.m[0][0] = A.m[0][0] * B.m[0][0] + A.m[0][1] * B.m[1][0] + A.m[0][2] * B.m[2][0];
    R.m[0][1] = A.m[0][0] * B.m[0][1] + A.m[0][1] * B.m[1][1] + A.m[0][2] * B.m[2][1];
    R.m[0][2] = A.m[0][0] * B.m[0][2] + A.m[0][1] * B.m[1][2] + A.m[0][2] * B.m[2][2];

    R.m[1][0] = A.m[1][0] * B.m[0][0] + A.m[1][1] * B.m[1][0] + A.m[1][2] * B.m[2][0];
    R.m[1][1] = A.m[1][0] * B.m[0][1] + A.m[1][1] * B.m[1][1] + A.m[1][2] * B.m[2][1];
    R.m[1][2] = A.m[1][0] * B.m[0][2] + A.m[1][1] * B.m[1][2] + A.m[1][2] * B.m[2][2];

    R.m[2][0] = A.m[2][0] * B.m[0][0] + A.m[2][1] * B.m[1][0] + A.m[2][2] * B.m[2][0];
    R.m[2][1] = A.m[2][0] * B.m[0][1] + A.m[2][1] * B.m[1][1] + A.m[2][2] * B.m[2][1];
    R.m[2][2] = A.m[2][0] * B.m[0][2] + A.m[2][1] * B.m[1][2] + A.m[2][2] * B.m[2][2];

    return R;
}

t_3dPoint rotation_point(t_matrice3x3 M, t_3dPoint P)
{
	t_3dPoint result;

    result.x = fp_init(M.m[0][0] * to_double(P.x) + M.m[0][1] * to_double(P.y) + M.m[0][2] * to_double(P.z));
    result.y = fp_init(M.m[1][0] * to_double(P.x) + M.m[1][1] * to_double(P.y) + M.m[1][2] * to_double(P.z));
    result.z = fp_init(M.m[2][0] * to_double(P.x) + M.m[2][1] * to_double(P.y) + M.m[2][2] * to_double(P.z));

    return result;
}

t_rotation vector_to_rotation_angles(t_Vector3d orientation)
{
    t_rotation angles;

    double norm = sqrt(orientation.x * orientation.x + orientation.y * orientation.y + orientation.z * orientation.z);
    if (fabs(norm - 1.0) > 1e-6)
	{
        orientation.x /= norm;
        orientation.y /= norm;
        orientation.z /= norm;
    }

    // Calculer l'angle phi (rotation autour de l'axe X)
    angles.phi = asin(orientation.y);

    // Calculer l'angle theta (rotation autour de l'axe Y)
    angles.theta = atan2(orientation.x, orientation.z);

    // Calculer l'angle psi (rotation autour de l'axe Z)
    angles.psi = atan2(orientation.y, orientation.x);

    return angles;
}

t_matrice3x3 combine_matrice(t_matrice3x3 rx, t_matrice3x3 ry, t_matrice3x3 rz)
{
    t_matrice3x3 matrix;

    matrix = multiplier_matrices(ry, rx);
    matrix = multiplier_matrices(rz, matrix);

    return matrix;
}