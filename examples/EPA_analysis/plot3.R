############################################
### To plot Total Emission for each year ###

d <- readRDS("../../data/EPA_fineparticlematter/summarySCC_PM25.rds")

d <- d[d$fips == "24510",]

d.spl <- split(d, factor(d$type))

emis_year_type <- sapply(d.spl, function(x) tapply(x$Emissions, factor(x$year), sum))

print(unique(d$year))

emis_year_type <- as.data.frame(emis_year_type)
colnames(emis_year_type) = c("POINT", "NONPOINT", "ONROAD", "NONROAD")

res <- data.frame( 
  year=rownames(emis_year_type),
  emission=c(emis_year_type$POINT, emis_year_type$NONPOINT, emis_year_type$ONROAD, emis_year_type$NONROAD),
  type=as.factor(rep(c("Point", "Non-point", "On-road", "Non-road"), each=4))
)

library(ggplot2)


png("plot3.png")

#ggplot(res, x=year, y=emission, col=type) + geom_line()
ggplot(res, aes(x=year, y=emission, col=type)) + geom_point(size=6)  +geom_line(aes(group=type), lwd=2)


dev.off()
