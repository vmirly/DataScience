checkPkgs <- function() {
        pkg.inst <- installed.packages()
        pkgs <- c("RCurl", "digest")
        have.pkg <- pkgs %in% rownames(pkg.inst)

        if(any(!have.pkg)) {
                cat("Some packages need to be installed\n")
                r <- readline("Install necessary packages [y/n]? ")
                if(tolower(r) == "y") {
                        need <- pkgs[!have.pkg]
                        message("installing packages ",
                                paste(need, collapse = ", "))
                        install.packages(need)
                }
        }
}

checkPkgs()

CLASS <- "rprog-003"
challenge.url <- paste("http://class.coursera.org", CLASS,
                       "assignment/challenge", sep = "/")
submit.url <- paste("http://class.coursera.org", CLASS,
                       "assignment/submit", sep = "/")

loginPrompt <- function() {
        email <- readline("Submission login (email): ")
        passwd <- readline("Submission  password: ")
        r <- list(email = email, passwd = passwd)
        assign(".CourseraLogin", r, globalenv())
        invisible(r)
}

submit <- function(manual = FALSE, resetLogin = FALSE) {
        library(RCurl)
        library(digest)
        if(!manual) {
                if(exists(".CourseraLogin") && !resetLogin)
                        cred <- get(".CourseraLogin")
                else
                        cred <- loginPrompt()
                if(!is.list(cred) || !(names(cred) %in% c("email", "passwd")))
                        stop("problem with login/password")
                email <- cred$email
                password <- cred$passwd
        }
        ## Prompt Submission Part
        sid <- partPrompt()

        ## Get output
        output <- getOutput(sid)

        if(!manual) {
                ## Get challenge
                ch <- getChallenge(email)
                
                ## Attempt submission with challenge
                ch.resp <- challengeResponse(password, ch$ch.key)
                results <- submitSolution(email, ch.resp, sid, output, ch$state)
                if(!length(results))
                        results <- "Incorrect!"
                cat("Result: ", results, "\n")
        }
        else {
                outfile <- paste(sid, "output.txt", sep = "-")
                writeLines(as.character(output), outfile)
                cat(sprintf("Please upload the file '%s' to Coursera\n",
                            outfile))
        }
        invisible()
}

checkResult <- function(r, name = c("best", "rankhospital", "rankall")) {
        name <- match.arg(name)
        if(name == "best" || name == "rankhospital") {
                if(length(r) == 1L && is.na(r))
                        return(r)
                if(!is.character(r))
                        stop(sprintf("'%s' did not return a character vector",
                                     name))
                if(!length(r))
                        stop(sprintf("'%s' returned character vector of length 0", name))
                if(length(r) > 1)
                        stop(sprintf("'%s' returned a character vector of length > 1", name))
        }
        else if(name == "rankall") {
                if(!is.data.frame(r))
                        stop(sprintf("'%s' did not return a data frame", name))
                if(ncol(r) != 2L)
                        stop(sprintf("'%s' should return data frame with exactly 2 columns", name))
                if(!all(names(r) %in% c("hospital", "state")))
                        stop("column names of data frame should be 'hospital' and 'state'")
        }
        r
}

getOutput <- function(sid) {
        ## JUST FOR TESTING
        ## sid <- sub("-dev", "", sid, fixed = TRUE)
        if(sid == "best-1") {
                source("best.R", local = TRUE)
                cat("Running test:\n")
                cat("best(\"SC\", \"heart attack\")\n")
                r <- best("SC", "heart attack")
                checkResult(r, "best")
        }
        else if(sid == "best-2") {
                source("best.R", local = TRUE)
                cat("Running test:\n")
                cat("best(\"NY\", \"pneumonia\")\n")
                r <- best("NY", "pneumonia")
                checkResult(r, "best")
        }
        else if(sid == "best-3") {
                source("best.R", local = TRUE)
                cat("Running test:\n")
                cat("best(\"NN\", \"pneumonia\")\n")
                r <- tryCatch(best("NN", "pneumonia"), error = function(e) e)
                if(!inherits(r, "error"))
                        stop("'best' should throw an error via the 'stop' function in this case")
                tolower(conditionMessage(r))
        }
        else if(sid == "rankhospital-1") {
                source("rankhospital.R", local = TRUE)
                cat("Running test:\n")
                cat("rankhospital(\"NC\", \"heart attack\", \"worst\")\n")
                r <- rankhospital("NC", "heart attack", "worst")
                checkResult(r, "rankhospital")
        }
        else if(sid == "rankhospital-2") {
                source("rankhospital.R", local = TRUE)
                cat("Running test:\n")
                cat("rankhospital(\"WA\", \"heart attack\", 7)\n")
                r <- rankhospital("WA", "heart attack", 7)
                checkResult(r, "rankhospital")
        }
        else if(sid == "rankhospital-3") {
                source("rankhospital.R", local = TRUE)
                cat("Running test:\n")
                cat("rankhospital(\"WA\", \"pneumonia\", 1000)\n")
                rankhospital("WA", "pneumonia", 1000)
        }
        else if(sid == "rankhospital-4") {
                source("rankhospital.R", local = TRUE)
                cat("Running test:\n")
                cat("rankhospital(\"NY\", \"heart attak\", 7)\n")
                r <- tryCatch({
                        rankhospital("NY", "heart attak", 7)
                }, error = function(e) {
                        e
                })
                if(!inherits(r, "error"))
                        stop("'rankhospital' should throw an error via 'stop' in this case")
                tolower(conditionMessage(r))
        }
        else if(sid == "rankall-1") {
                source("rankall.R", local = TRUE)
                cat("Running test:\n")
                cat("rankall(\"heart attack\", 4)\n")
                r <- rankall("heart attack", 4)
                r <- checkResult(r, "rankall")
                as.character(subset(r, state == "HI")$hospital)
        }
        else if(sid == "rankall-2") {
                source("rankall.R", local = TRUE)
                cat("Running test:\n")
                cat("rankall(\"pneumonia\", \"worst\")\n")
                r <- rankall("pneumonia", "worst")
                r <- checkResult(r, "rankall")
                as.character(subset(r, state == "NJ")$hospital)
        }
        else if(sid == "rankall-3") {
                source("rankall.R", local = TRUE)
                cat("Running test:\n")
                cat("rankall(\"heart failure\", 10)\n")
                r <- rankall("heart failure", 10)
                r <- checkResult(r, "rankall")
                as.character(subset(r, state == "NV")$hospital)
        }
        else {
                stop("invalid part number")
        }
}

partPrompt <- function() {
        sid <- c("best-1",
                 "best-2",
                 "best-3",
                 "rankhospital-1",
                 "rankhospital-2",
                 "rankhospital-3",
                 "rankhospital-4",
                 "rankall-1",
                 "rankall-2",
                 "rankall-3"
                 )
        ## Just for testing
        ## sid <- paste(sid, "dev", sep = "-")

        sidname <- c("'best' part 1",
                     "'best' part 2",
                     "'best' part 3",
                     "'rankhospital' part 1",
                     "'rankhospital' part 2",
                     "'rankhospital' part 3",
                     "'rankhospital' part 4",
                     "'rankall' part 1",
                     "'rankall' part 2",
                     "'rankall' part 3"
                     )
        numparts <- length(sid)
        cat(paste(paste("[", seq_len(numparts), "]", sep = ""), sidname),
            sep = "\n")
        partnum <- readline(sprintf("Which part are you submitting [1-%d]? ",
                                    numparts))
        partnum <- as.integer(partnum)               
        if(partnum > numparts)
                stop("invalid part number")
        sid[partnum]
}

getChallenge <- function(email) {
        params <- list(email_address = email, response_encoding = "delim")
        result <- getForm(challenge.url, .params = params)
        s <- strsplit(result, "|", fixed = TRUE)[[1]]
        list(ch.key = s[5], state = s[7])
}

challengeResponse <- function(password, ch.key) {
        x <- paste(ch.key, password, sep = "")
        digest(x, algo = "sha1", serialize = FALSE)
}

submitSolution <- function(email, ch.resp, sid, output, signature, src = "",
                           http.version = NULL) {
        output <- as.character(base64(output))
        src <- as.character(base64(src))
        params <- list(assignment_part_sid = sid,
                       email_address = email,
                       submission = output,
                       submission_aux = src,
                       challenge_response = ch.resp,
                       state = signature)
        params <- lapply(params, URLencode)
        result <- postForm(submit.url, .params = params)
        s <- strsplit(result, "\\r\\n")[[1]]
        tail(s, 1)
}
