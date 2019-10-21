#' Compute a grouped sum
#'
#' @param x A numeric vector
#' @param g A vector defining grouping levels
#' @export
#' @examples
#' group_sum(mtcars$cyl, mtcars$vs)
#' group_sum(mtcars$cyl, mtcars[c("vs", "am")])
group_sum <- function(x, g) {
  g <- vec_group(g)
  if (vec_size(x) != vec_size(g)) {
    stop("`x` and `g` must be same size", call.  = FALSE)
  }

  .Call(grouped_sum_dbl, x, g, attr(g, "n"))
}

#' Grouping tools
#'
#' @keywords internal
#' @export
vec_group <- function(x) {
  if (inherits(x, "group")) {
    return(x)
  }

  unique <- vec_unique(x)
  id <- vec_match(x, unique)

  new_group(id, vec_size(unique))
}

#' @export
#' @rdname vec_group
new_group <- function(x, n) {
  structure(
    x,
    n = n,
    class = "group"
  )
}
