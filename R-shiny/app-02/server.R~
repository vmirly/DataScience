## server.R 
## example for user input and output:

library(shiny)

makeRandomDF <- function(mean, n) {
	## generate a random dataframe of size n
	## with the same number of columns as mean vector
	sapply(mean, function(x) rnorm(mean=x, n))
}

shinyServer(
    function(input, output) {
	output$outputId1 <- renderPrint({input$id1})
	output$outputId2 <- renderPrint({as.numeric(input$id2)})

	mean.diff <- reactive({
		df.1 <- makeRandomDF(c(0,0,0), n=input$id1)
		df.2 <- makeRandomDF(c(1,1,1), n=input$id1)

		mean.1 <- colMeans(df.1)
		mean.2 <- colMeans(df.2)

		sqrt(sum((mean.1 - mean.2)^2))
	})

	output$outputId3 <- renderPrint(mean.diff)
    }
)
