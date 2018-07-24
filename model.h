#ifndef MODEL_H
#define MODEL_H

void set_init_cond(double y[]);
void normalize_quaternion(double y[]);
point get_vector_lab(point v, double y[]);
matrix get_I_bff();
matrix get_inv_I_bff();
matrix sym_part(point r);
point antisym_part(point r);
point flow(point r);

#endif
