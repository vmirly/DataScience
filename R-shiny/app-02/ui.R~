## ui.R
## example for user input and output:

library(shiny)

shinyUI(pageWithSidebar(
    headerPanel("Input/output functionality in Shiny!"),

    sidebarPanel( #position="left",
        numericInput("id1", "Number of Samples:", 40, min=10, max=100, step=5),
        #checkboxGroupInput("id2", "Number of Dimensions:", c("1"="1", "2"="2", "3"="3")),
	radioButtons("id2", "Number of Dimensions:", c(1, 2, 3), selected = NULL),
	submitButton("submit")
    ),

    mainPanel(
        h2('Output: '),
        h3('Number of random samples:'),
        verbatimTextOutput("outputId1"),

        h3('Number of dimensions:'),
        verbatimTextOutput("outputId2"),

        h3('Distance between class means:'),
        verbatimTextOutput("outputId3")
    )
))
