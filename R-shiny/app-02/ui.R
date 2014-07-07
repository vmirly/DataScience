## ui.R
## example for user input and output:

library(shiny)

shinyUI(fluidPage(
    titlePanel("Input/output functionality in Shiny!"),

    sidebarLayout( position="left",
        numericInput("id1", "label1", 40, min=10, max=100, step=5),
        checkboxGroupInput("id2", "Number of Dimensions:", c("v1"="1", "v2"="2", "v3"="3"))
    ),

    mainPanel(
        h2('Output: '),
        h3('Distance between class means:')
#        verbatimTextOutput("oid1")
    )
))
