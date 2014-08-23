############################################
### To plot Total Emission for each year ###

d <- readRDS("../../data/EPA_fineparticlematter/summarySCC_PM25.rds")

d <- d[d$fips == "24510",]

d.spl <- split(d, factor(d$type))

emis_year_type <- sapply(d.spl, function(x) tapply(x$Emissions, factor(x$year), sum))

print(unique(d$year))

colnames(emis_year_type) = c("POINT", "NONPOINT", "ONROAD", "NONROAD")

res <- data.frame( 
  year=rownames(emis_year_type),
  emiss=c(emis_year_type$POINT, emis_year_type$NONPOINT, emis_year_type$ONROAD, emis_year_type$NONROAD),
  type=as.factor(rep(c("Point", "Non-point", "On-road", "Non-road"), each=4))
)

library(ggplot2)
png("plot3.png")

plot(names(emis_year), emis_year, type="b", pch=19, cex=1.6,
	col="steelblue", lwd=5, cex.axis=1.7, cex.lab=1.7, 
	xlab="Year", ylab=expression(paste("Total ",  PM[2.5], " Emission", sep="")), axes=F)

axis(side=1, at=unique(d$year), cex.axis=1.6)
axis(side=2, cex.axis=1.6)

dev.off()
