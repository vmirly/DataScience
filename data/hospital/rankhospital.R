
rankhospital <- function(state, outcome, num = "best") {
	## Read outcome data
	d <- read.csv("outcome-of-care-measures.csv")

	## Check that state and outcome are valid
	out.list <- c("heart attack", "heart failure", "pneumonia")
	if (!(outcome %in% out.list)) {
		stop("invalid outcome")
	} else {
		#out.col <- match(outcome, out.list)
		#print(out.col)
		if (outcome == "heart attack") {
			out.col = 11
		} else if (outcome == "heart failure"){
			out.col = 17
		} else {
			out.col = 23
		}
	}

	state.list <- c('AL', 'AK', 'AZ', 'AR', 'CA', 'CO', 'CT', 'DE', 'DC', 'FL', 'GA', 'HI', 'ID', 'IL', 'IN', 'IA', 'KS', 'KY', 'LA', 'ME', 'MD', 'MA', 'MI', 'MN', 'MS', 'MO', 'MT', 'NE', 'NV', 'NH', 'NJ', 'NM', 'NY', 'NV', 'ND', 'OH', 'OK', 'OR', 'PA', 'RI', 'SC', 'SD', 'TN', 'TX', 'UT', 'VT', 'VA', 'WA', 'WV', 'WI', 'WY')
	if (!(state %in% state.list)) {
		stop("invalid state")
	}

	d.sub <- d[d[,7] == state,]
	#d.sub[which.min(d.sub[,out.col]),2]
	d.sub <- order(d.sub[,out.col], d.sub[,2])

}
