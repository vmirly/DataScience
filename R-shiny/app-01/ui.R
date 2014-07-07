## ui.R
library(shiny)
shinyUI(pageWithSidebar(
    ## Header 
    headerPanel("Hello Shiny World!"),


    sidebarPanel(
        h3('This is a sidebar')
    ),

    mainPanel(
        h3('This is the main panel')
    )
))
