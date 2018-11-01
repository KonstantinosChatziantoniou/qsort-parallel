script.dir <- dirname(sys.frame(1)$ofile)
rel.loc = "/../../outP.csv"
pat = paste(script.dir, rel.loc,sep = '')
## @knitr plotbarP
library(ggplot2)
library(reshape2)
library(gridExtra)
pat = '../../outP.csv' ##path to use when report runs the chunk
data.for.p <- read.csv(pat, header = TRUE, sep = ',')
data.for.p <- data.for.p[,-1]
melted.data <- melt(data.for.p , id = 'num_threads')

plot1 <- ggplot(melted.data, aes(x = num_threads , y = value , fill = variable)) + 
  geom_bar(stat = "identity" , position = "dodge") +
  theme(legend.direction = "horizontal" , legend.position = "top")
plot1 <- ggplot(melted.data, aes(x = num_threads , y = value , color = variable )) + geom_line(stat = "identity") + 
  xlab('Number of threads 2^n') + ylab("Time (sec)") + labs(color = "Version") + scale_x_continuous(breaks = 1:8) + 
  ggtitle('figure 2' ) + theme(plot.title = element_text(face = 'italic' , size = 10 , colour = '#553146'))
print(plot1)
