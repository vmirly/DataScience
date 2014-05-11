pollutantmean <- function(directory, pollutant, id = 1:332) {
        ## 'directory' is a character vector of length 1 indicating
        ## the location of the CSV files

        ## 'pollutant' is a character vector of length 1 indicating
        ## the name of the pollutant for which we will calculate the
        ## mean; either "sulfate" or "nitrate".

        ## 'id' is an integer vector indicating the monitor ID numbers
        ## to be used

        ## Return the mean of the pollutant across all monitors list
        ## in the 'id' vector (ignoring NA values)

	flist <- list.files(path=directory, pattern="*.csv", full.names=T)
	dlist <- lapply(flist[id], read.csv)

	alld <- vector()
	for (i in seq_along(dlist)) {
		alld <- c(alld, dlist[[i]][,pollutant])
	}

	mean(alld, na.rm=T)
}
