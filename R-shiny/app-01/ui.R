## ui.R
library(shiny)
shinyUI(pageWithSidebar(
    headerPanel("Hello Shiny World!"),
    sidebarPanel(
        h3('This is a sidebar created by sidebarPanel()')
    ),
    mainPanel(
        h3('This is the main panel created by mainPanel()')
    )
))
