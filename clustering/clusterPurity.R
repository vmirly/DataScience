

clustPurity <- function(y) {
        ## Calculates the purity of a single cluster, 
        ## w.r.t. true cluster/class labels given in y
        y.list <- split(y, factor(y))
        max(sapply(y.list, length)) / length(y)
}
