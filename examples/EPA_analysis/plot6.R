############################################
### To plot Total Emission for each year ###

d <- readRDS("../../data/EPA_fineparticlematter/summarySCC_PM25.rds")
ds <- readRDS("../../data/EPA_fineparticlematter/Source_Classification_Code.rds")

d.bm <- d[d$fips == "24510",]
d.la <- d[d$fips == "06037",]

motor <- sapply(ds$Short.Name, function(x) grepl('Motor', x))
print(c("num_motor: ", sum(motor)))

scc.motor <- ds[motor,]$SCC

print(str(scc.motor))

d.bm.motor <- d.bm[d.bm$SCC %in% scc.motor,]
d.la.motor <- d.la[d.la$SCC %in% scc.motor,]
print(str(d.bm.motor))
print(str(d.la.motor))


emis_year.bm <- tapply(d.bm.motor$Emissions, factor(d.bm.motor$year), sum)
emis_year.la <- tapply(d.la.motor$Emissions, factor(d.la.motor$year), sum)
print(emis_year.bm)
print(emis_year.la)


png("plot6.png")
par(mar=c(4.7, 4.7, 0.6, 0.6))
plot(names(emis_year.bm), emis_year.bm, type="b", pch=19, cex=1.6,
        col="steelblue", lwd=5, cex.axis=1.7, cex.lab=1.7, ylim=c(0, 88),
        xlab="Year", ylab=expression(paste("Total ",  PM[2.5], " Emission", sep="")), axes=F)

lines(names(emis_year.la), emis_year.la, lwd=5,
        col="darkred")
points(names(emis_year.la), emis_year.la, 
        col="darkred", pch=17, cex=1.6)

axis(side=1, at=unique(d$year), cex.axis=1.6)
axis(side=2, cex.axis=1.6)

legend(x=2002, y=60, pch=c(19,17), lwd=c(5,5), col=c("steelblue", "darkred"), cex=1.6, legend=c("Baltimore", "Los Angeles"))

#ggplot(res, aes(x=year, y=emission, col=type)) + geom_point(size=6)  +geom_line(aes(group=type), lwd=2)


dev.off()
