x <- seq(0, 5, by=0.01)
y <- 1.5+x + rnorm(n=length(x), mean=0, sd=1)

lm(y ~ x)
