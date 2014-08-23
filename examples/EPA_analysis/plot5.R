############################################
### To plot Total Emission for each year ###

d <- readRDS("../../data/EPA_fineparticlematter/summarySCC_PM25.rds")
ds <- readRDS("../../data/EPA_fineparticlematter/Source_Classification_Code.rds")

d <- d[d$fips == "24510",]

motor <- sapply(ds$Short.Name, function(x) grepl('Motor', x))
print(c("num_motor: ", sum(motor)))

scc.motor <- ds[motor,]$SCC

print(str(scc.motor))

d.sub <- d[d$SCC %in% scc.motor,]
print(str(d.sub))

emis_year <- tapply(d.sub$Emissions, factor(d.sub$year), sum)
print(emis_year)

print(unique(d$year))


png("plot5.png")
par(mar=c(4.7, 4.7, 0.6, 0.6))
plot(names(emis_year), emis_year, type="b", pch=19, cex=1.6,
        col="steelblue", lwd=5, cex.axis=1.7, cex.lab=1.7,
        xlab="Year", ylab=expression(paste("Total ",  PM[2.5], " Emission", sep="")), axes=F)

axis(side=1, at=unique(d$year), cex.axis=1.6)
axis(side=2, cex.axis=1.6)

#ggplot(res, aes(x=year, y=emission, col=type)) + geom_point(size=6)  +geom_line(aes(group=type), lwd=2)


dev.off()
