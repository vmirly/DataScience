###########################################
### To plot Totalemission for each year ###

d <- readRDS("../../data/EPA_fineparticlematter/summarySCC_PM25.rds")

emis_year <- tapply(d$Emissions, factor(d$year), sum)

print(unique(d$year))

png("plot1.png")
par(mar=c(4.7, 4.7,0.6,0.6))
plot(names(emis_year), emis_year, type="b", pch=19, cex=1.6,
	col="steelblue", lwd=5, cex.axis=1.7, cex.lab=1.7, 
	xlab="Year", ylab=expression(paste("Total ",  PM[2.5], " Emission", sep="")), axes=F)

axis(side=1, at=unique(d$year), cex.axis=1.6)
axis(side=2, cex.axis=1.6)

dev.off()
