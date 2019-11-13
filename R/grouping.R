#' Grouping tools
#'
#' @keywords internal
#' @export
#' @examples
#' x <- c(rep("a", 10), rep("b", 4), rep("a", 5))
#' as_group_id(x)
#' as_group_rle(x)
as_group_id <- function(x) {
  if (inherits(x, "grouped_group_id")) {
    x
  } else {
    structure(vec_group_id(x), class = "grouped_group_id")
  }
}

#' @rdname as_group_id
#' @export
as_group_rle <- function(x) {
  if (inherits(x, "grouped_group_rle")) {
    x
  } else {
    structure(vec_group_rle(x), class = "grouped_group_rle")
  }
}
