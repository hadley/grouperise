#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP grouped_sum_id(SEXP, SEXP, SEXP);
extern SEXP grouped_sum_rle(SEXP, SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"grouped_sum_id", (DL_FUNC) &grouped_sum_id, 3},
    {"grouped_sum_rle", (DL_FUNC) &grouped_sum_rle, 4},
    {NULL, NULL, 0}
};

void R_init_grouperise(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
