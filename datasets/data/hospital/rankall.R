
rankall <- function(outcome, num = "best") {
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

	d[,out.col] = as.numeric(d[,out.col])
	d <- d[complete.cases(d[,c(2,out.col)]),]
	d.splt <- split(d, as.factor(d[,7]))
	
	if (num %in% c("best", "worst")) {
		if (num == "best") {
			num = 1
		}
	} else {
		num = as.numeric(num)
	}

	#print(head(d.sub[,c(2,out.col)]))
	#print(class(d.sub[num,2]))
	if (num != "worst") {
		res <- sapply(d.splt, function(x) x[order(x[,out.col], x[,2])[num], 2])
	} else {
		res <- sapply(d.splt, function(x) x[tail(order(x[,out.col], x[,2]),1), 2])
	}
	#res <- sapply(res, function(x) x[num,])
	#colnames(res) = c("hospital", "state")
	data.frame(
		hospital=res,
		state=names(res)
	)
}
