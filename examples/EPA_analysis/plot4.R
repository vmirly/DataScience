############################################
### To plot Total Emission for each year ###

d <- readRDS("../../data/EPA_fineparticlematter/summarySCC_PM25.rds")
ds <- readRDS("../../data/EPA_fineparticlematter/Source_Classification_Code.rds")


coal <- sapply(ds$Short.Name, function(x) grepl('Coal', x))

scc.coal <- ds[coal,]$SCC

d.sub <- d[d$SCC %in% scc.coal,]

emis_year <- tapply(d.sub$Emissions, factor(x$year), sum)

print(unique(d$year))

png("plot4.png")
par(mar=c(4.7, 4.7, 0.6, 0.6))
plot(names(emis_year), emis_year, type="b", pch=19, cex=1.6,
        col="steelblue", lwd=5, cex.axis=1.7, cex.lab=1.7,
        xlab="Year", ylab=expression(paste("Total ",  PM[2.5], " Emission", sep="")), axes=F)

axis(side=1, at=unique(d$year), cex.axis=1.6)
axis(side=2, cex.axis=1.6)

#ggplot(res, aes(x=year, y=emission, col=type)) + geom_point(size=6)  +geom_line(aes(group=type), lwd=2)


dev.off()
