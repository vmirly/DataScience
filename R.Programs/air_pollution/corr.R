corr <- function(directory, threshold = 0) {
        ## 'directory' is a character vector of length 1 indicating
        ## the location of the CSV files

        ## 'threshold' is a numeric vector of length 1 indicating the
        ## number of completely observed observations (on all
        ## variables) required to compute the correlation between
        ## nitrate and sulfate; the default is 0

        ## Return a numeric vector of correlations

        flist <- list.files(path=directory, pattern="*.csv", full.names=T)
        dlist <- lapply(flist, read.csv)

	accept <- complete(directory=directory)$nobs > threshold

	calCorr <- function(x) {
		cor(x[complete.cases(x), c("sulfate", "nitrate")])[1,2]
	}

	sapply(dlist[accept], calCorr)
}
