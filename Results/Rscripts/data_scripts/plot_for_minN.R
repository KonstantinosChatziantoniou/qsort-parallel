
script.dir <- dirname(sys.frame(1)$ofile)
rel.loc = "/../../outminN.csv"
pat = paste(script.dir, rel.loc,sep = '')
## @knitr plotbarminN
library(ggplot2)
library(reshape2)
library(gridExtra)
pat = '../../outminN.csv' ##path to use when report runs the chunk
data.for.minN <- read.csv(pat, header = TRUE, sep = ',')
data.for.minN<- data.for.minN[, -1]
melted.data <- melt(data.for.minN, id = "min.N")

plot1 <- ggplot(melted.data, aes(x = min.N , y = value , color = variable )) + geom_line(stat = "identity") + 
  xlab('Minimum N for parallelisation') + ylab("Time (sec)") + labs(color = "Version") + scale_x_continuous(breaks = 10:22)+ 
  ggtitle('figure 1' ) + theme(plot.title = element_text(face = 'italic' , size = 10 , colour = '#553146'))
  
print(plot1)