#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP grouped_sum_dbl(SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"grouped_sum_dbl", (DL_FUNC) &grouped_sum_dbl, 3},
    {NULL, NULL, 0}
};

void R_init_grouperise(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
