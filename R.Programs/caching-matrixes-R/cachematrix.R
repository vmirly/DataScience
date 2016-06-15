## Matrix inverse calculations can be computationally 
##  expensive for large matrices.
## This is a special matrix that can store its inverse
## As a result, once the inverse of this special matrix
## is calculated, it can be used for future needs

## Example usage:
#  myMat$set(matrix(c(2,0,0,1), nrow=2))
#  myMat$get()
##        [,1] [,2]
##  [1,]    2    0
##  [2,]    0    1
#  cacheSolve(myMat)
##       [,1] [,2]
##  [1,]  0.5    0
##  [2,]  0.0    1
#  cacheSolve(myMat)
##  getting cached data
##       [,1] [,2]
## [1,]  0.5    0
## [2,]  0.0    1



## This function returns a list of 4 functions to
## 1. set the matrix
## 2. get the matrix
## 3. set the inverse matrix
## 4. get the inverse matrix

makeCacheMatrix <- function(x = matrix()) {
	inv <- NULL
	set <- function(y) {
		x <<- y
		inv <<- NULL
	}
	get <- function() x

	setInverse <- function(inverse) inv <<- inverse
	getInverse <- function() inv

	list(set=set, get = get,
	     setInverse = setInverse,
	     getInverse = getInverse)
}


## This function returns the inverse of our special matrix
## if it has already been calculated, otherwise it will 
## compute the inverse, store and return it

cacheSolve <- function(x, ...) {
        ## Return a matrix that is the inverse of 'x'
	inv <- x$getInverse()
	if (!is.null(inv)) {
		message("getting cached data")
		return (inv)
	}
	data <- x$get()
	inv <- solve(data, ...)
	x$setInverse(inv)
	inv
}
