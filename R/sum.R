#' Compute a grouped sum
#'
#' @param x A numeric vector
#' @param g A vector defining grouping levels
#' @export
#' @examples
#' group_sum_id(mtcars$cyl, mtcars$vs)
#' group_sum_id(mtcars$cyl, mtcars[c("vs", "am")])
group_sum_id <- function(x, g) {
  g <- as_group_id(g)
  .Call(grouped_sum_id, x, g, attr(g, "n"))
}

#' @export
#' @rdname group_sum_rle
group_sum_rle <- function(x, g) {
  g <- as_group_rle(g)
  .Call(grouped_sum_rle, x, g$group, g$length, attr(g, "n"))
}
