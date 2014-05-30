
best <- function(state, outcome) {
	## Read outcome data
	d <- read.csv("outcome-of-care-measures.csv", colClasses="character")
	d[,11] <- as.numeric(d[,11])

	## Check that state and outcome are valid
	out.list <- c("heart attack", "heart failure", "pneumonia")
	state.list <- c()
	if (!(outcome %in% outlist) || !(state %in% state.list)) {
	}
}
