
rankhospital <- function(state, outcome, num = "best") {
	## Read outcome data
	d <- read.csv("outcome-of-care-measures.csv", colClasses="character")

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

	state.list <- c('AL', 'AK', 'AZ', 'AR', 'CA', 'CO', 'CT', 'DE', 'DC', 'FL', 'GA', 'HI', 'ID', 'IL', 'IN', 'IA', 'KS', 'KY', 'LA', 'ME', 'MD', 'MA', 'MI', 'MN', 'MS', 'MO', 'MT', 'NE', 'NV', 'NH', 'NJ', 'NM', 'NY', 'NV', 'NC', 'ND', 'OH', 'OK', 'OR', 'PA', 'RI', 'SC', 'SD', 'TN', 'TX', 'UT', 'VT', 'VA', 'WA', 'WV', 'WI', 'WY')
	if (!(state %in% state.list)) {
		stop("invalid state")
	}

	d.sub <- d[d[,7] == state,]
	#d.sub[which.min(d.sub[,out.col]),2]
	d.sub[,out.col] = as.numeric(d.sub[,out.col])
	d.sub <- d.sub[complete.cases(d.sub[,c(2,out.col)]),]
	
	d.sub <- d.sub[order(d.sub[,out.col], d.sub[,2]),]
	if (num %in% c("best", "worst")) {
		if (num == "best") {
			num = 1
		} else {
			num = length(d.sub[,2])
		}
	} else {
		num = as.numeric(num)
	}

	#print(head(d.sub[,c(2,out.col)]))
	#print(class(d.sub[num,2]))
	return(d.sub[num,2])
}
