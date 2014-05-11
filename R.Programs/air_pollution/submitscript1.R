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

getOutput <- function(sid) {
        ## JUST FOR TESTING
        ### sid <- sub("-dev", "", sid, fixed = TRUE)
        if(sid == "pollutantmean-1") {
                source("pollutantmean.R")
                pollutantmean("specdata", "sulfate", 1:10)
        }
        else if(sid == "pollutantmean-2") {
                source("pollutantmean.R")
                pollutantmean("specdata", "nitrate", 70:72)
        }
        else if(sid == "pollutantmean-3") {
                source("pollutantmean.R")
                pollutantmean("specdata", "sulfate", 34)
        }
        else if(sid == "pollutantmean-4") {
                source("pollutantmean.R")
                pollutantmean("specdata", "nitrate")
        }
        else if(sid == "complete-1") {
                source("complete.R")
                cc <- complete("specdata", c(6, 10, 20, 34, 100, 200, 310))
                paste(cc$nobs, collapse = "\n")
        }
        else if(sid == "complete-2") {
                source("complete.R")
                cc <- complete("specdata", 54)
                cc$nobs
        }
        else if(sid == "complete-3") {
                source("complete.R")
                set.seed(42)
                cc <- complete("specdata", 332:1)
                use <- sample(332, 10)
                paste(cc[use, "nobs"], collapse = "\n")                
        }
        else if(sid == "corr-1") {
                source("corr.R")
                cr <- corr("specdata")
                cr <- sort(cr)
                set.seed(868)
                out <- round(cr[sample(length(cr), 5)], 4)
                paste(out, collapse = "\n")
        }
        else if(sid == "corr-2") {
                source("corr.R")
                cr <- corr("specdata", 129)
                cr <- sort(cr)
                n <- length(cr)
                set.seed(197)
                out <- c(n, round(cr[sample(n, 5)], 4))
                paste(out, collapse = "\n")
                
        }
        else if(sid == "corr-3") {
                source("corr.R")
                cr <- corr("specdata", 2000)
                n <- length(cr)
                cr <- corr("specdata", 1000)
                cr <- sort(cr)
                paste(c(n, round(cr, 4)), collapse = "\n")
        }
        else {
                stop("invalid part number")
        }
}

partPrompt <- function() {
        sid <- c("pollutantmean-1",
                 "pollutantmean-2",
                 "pollutantmean-3",
                 "pollutantmean-4",
                 "complete-1",
                 "complete-2",
                 "complete-3",
                 "corr-1",
                 "corr-2",
                 "corr-3"
                 )
        ## JUST FOR TESTING
        ## sid <- paste(sid, "dev", sep = "-")
        
        sidname <- c("'pollutantmean' part 1",
                     "'pollutantmean' part 2",
                     "'pollutantmean' part 3",
                     "'pollutantmean' part 4",
                     "'complete' part 1",
                     "'complete' part 2",
                     "'complete' part 3",
                     "'corr' part 1",
                     "'corr' part 2",
                     "'corr' part 3"                     
                     )
        numparts <- length(sid)
        cat(paste(paste("[", seq_len(numparts), "]", sep = ""), sidname),
            sep = "\n")
        partnum <- readline(sprintf("Which part are you submitting [1-%d]? ",
                                    numparts))
        partnum <- as.integer(partnum)
        if(is.na(partnum))
                stop("please specify part number")
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
