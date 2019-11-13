#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

// Assume x and g are the same length
SEXP grouped_sum_id(SEXP x, SEXP g, SEXP m_) {
  int m = Rf_asInteger(m_);
  SEXP out = PROTECT(Rf_allocVector(REALSXP, m));
  double *p_out = REAL(out);
  memset(p_out, 0, m * sizeof(int));

  int n = Rf_length(x);
  double *p_x = REAL(x);
  int *p_g = INTEGER(g);
  for (int i = 0; i < n; ++i) {
    int g = p_g[i] - 1;
    p_out[g] += p_x[i];
  }

  UNPROTECT(1);

  return out;
}

SEXP grouped_sum_rle(SEXP x, SEXP g, SEXP l, SEXP n_out_) {
  int n_out = Rf_asInteger(n_out_);
  SEXP out = PROTECT(Rf_allocVector(REALSXP, n_out));
  double *p_out = REAL(out);
  memset(p_out, 0, n_out * sizeof(int));

  double *p_x = REAL(x);
  int i_x = 0;

  int n_g = Rf_length(g);
  int *p_g = INTEGER(g);
  int *p_l = INTEGER(l);

  for (int i_g = 0; i_g < n_g; ++i_g) {
    int sum = 0;
    int m = p_l[i_g];
    for (int j = 0; j < m; ++j) {
      sum += p_x[i_x++];
    }
    p_out[p_g[i_g] - 1] += sum;
  }

  UNPROTECT(1);

  return out;
}
