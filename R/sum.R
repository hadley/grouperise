#' Compute a grouped sum
#'
#' @param x A numeric vector
#' @param g A vector defining grouping levels
#' @export
#' @examples
#' group_sum(mtcars$cyl, mtcars$vs)
#' group_sum(mtcars$cyl, mtcars[c("vs", "am")])
group_sum1 <- function(x, g) {
  g <- vec_group(g)
  .Call(grouped_sum1, x, g, attr(g, "n"))
}

group_sum_rle1 <- function(x, g) {
  g <- group_rle(g)
  .Call(grouped_sum_rle1, x, g$x, g$l, attr(g, "n"))
}

# Grouping ----------------------------------------------------------------


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

group_rle <- function(x) {
  if (inherits(x, "group_rle")) {
    return(x)
  }

  rle <- vec_group_rle(x)

  group <- field(rle, "group")
  length <- field(rle, "length")
  n <- attr(rle, "n")

  new_group_rle(group, length, n)
}

new_group_rle <- function(x, l, n) {
  structure(
    list(x = x, l = l),
    n = n,
    class = "group_rle"
  )
}


