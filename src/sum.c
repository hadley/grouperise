#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

// Assume x and g are the same length
SEXP grouped_sum_dbl(SEXP x, SEXP g, SEXP m_) {
  int n = Rf_length(x);
  int m = Rf_asInteger(m_);

  SEXP out = PROTECT(Rf_allocVector(REALSXP, m));

  double *p_x = REAL(x);
  int *p_g = INTEGER(g);
  double *p_out = REAL(out);

  for (int j = 0; j < m; ++j) {
    p_out[j] = 0;
  }

  for (int i = 0; i < n; ++i) {
    int g = p_g[i] - 1;
    p_out[g] += p_x[i];
  }

  UNPROTECT(1);

  return out;
}
