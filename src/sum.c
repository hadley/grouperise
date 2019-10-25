#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <omp.h>

// Assume x and g are the same length
SEXP grouped_sum1(SEXP x, SEXP g, SEXP m_) {
  int m = Rf_asInteger(m_);
  SEXP out = PROTECT(Rf_allocVector(REALSXP, m));
  double *p_out = REAL(out);
  memset(p_out, 0, m * sizeof(double));

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

SEXP grouped_sum_rle1(SEXP x, SEXP g, SEXP l, SEXP m_) {
  int m = Rf_asInteger(m_);
  SEXP out = PROTECT(Rf_allocVector(REALSXP, m));
  double *p_out = REAL(out);
  memset(p_out, 0, m * sizeof(double));

  int n1 = Rf_length(l);
  int *p_l = INTEGER(l);
  int *p_g = INTEGER(g);

  double *p_x = REAL(x);
  int i = 0;

  // Only parallelise if its worth it:
  // Need to experiment to figure out where to set this value
  double avg_run_length = Rf_length(x) / n1;
  int parallel = avg_run_length > 100;

  #pragma omp parallel for reduction(+:p_out[:m]) strategy(dynamic)
  for (int j1 = 0; j1 < n1; ++j1) {
    int n2 = p_l[j1];

    double sum = 0;

    // Manually unroll to avoid poor worst case behaviour
    // Might be able to make better by carefully thinking about alignment
    // so the loop always gets complete SIMD
    if (n2 > 4) {
      #pragma omp simd reduction(+:sum)
      for (int j2 = 0; j2 < n2; ++j2) {
        sum += p_x[i++];
      }
    } else if (n2 > 3) {
      for (int j2 = 0; j2 < n2; ++j2) {
        sum += p_x[i++];
      }
    } else if (n2 > 2) {
      for (int j2 = 0; j2 < n2; ++j2) {
        sum += p_x[i++];
      }
    } else if (n2 > 1) {
      for (int j2 = 0; j2 < n2; ++j2) {
        sum += p_x[i++];
      }
    } else {
      sum += p_x[i++];
    }

    int g = p_g[j1] - 1;
    p_out[g] += sum;
  }

  UNPROTECT(1);

  return out;
}
