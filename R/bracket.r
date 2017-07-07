bracket.spm = function(x, i, j)
{
  if (missing(i) && missing(j))
    return(x)
  
  if (missing(i))
    i = 1:nrow(x)
  if (missing(j))
    j = 1:ncol(x)
  
  ptr = .Call(R_bracket_spm, x@ptr, i, j)
  new("spm", ptr=ptr)
}

#' @rdname bracket
#' @export
setMethod("[", signature(x="spm"), bracket.spm)