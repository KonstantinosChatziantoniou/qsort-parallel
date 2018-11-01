## @knitr plotbarN
library(ggplot2)
library(reshape2)
library(gridExtra)
##script.dir <- dirname(sys.frame(1)$ofile)
rel.loc = "/../../outN.csv"
##pat = paste(script.dir, rel.loc,sep = '')
data.for.n <- read.csv('../../outN.csv', header = TRUE, sep = ',')
half.data = data.for.n
##print(half.data)
melted.data <- melt(half.data, id = "elements")
##print(melted.data)
a <- 12:24
table_log <- a*2^a / 200000000
Colors <- c( '#336B87', '#2A3132', '#46211A' , '#693D3D' , '#BA5536' , '#A43820')

plot1 <- ggplot(NULL)+ geom_line(aes(x = 12:24 , y = table_log ) , color = 'yellow' ) + geom_line(data = melted.data ,aes(x = elements , y = value , color = variable)) + 
  scale_color_manual("Version" ,values = c("seq.stdlib" = Colors[1],
                                          "sequential" = Colors[2] ,
                                          "pthread" = Colors[3],
                                          "cilk" = Colors[4],
                                          "openmp" = Colors[5],
                                          "pthread.9000" = Colors[6],
                                          "log2", "yellow"))+ ylab("Time") + xlab("elements") + scale_x_continuous(breaks = 12:24) +
  ggtitle('figure 3.1' ) + theme(plot.title = element_text(face = 'italic' , size = 10 , colour = '#553146'))
                                                                                      

half.data <- data.for.n[10:13,-2]
half.data <- half.data[,-2]
melted.data <- melt(half.data , id = "elements")


plot2 <- ggplot(melted.data, aes(x = elements , y = value ,fill = variable)) +
  geom_bar( stat = "identity" , ,position = "dodge") + 
  ylab("Time") + 
  scale_x_continuous(breaks = 21:24) +
  scale_fill_manual("Version" ,values = c("pthread" = Colors[3],
                                          "cilk" = Colors[4],
                                          "openmp" = Colors[5],
                                          "pthread.9000" = Colors[6]))+ 
  theme(legend.direction = "horizontal", legend.position = "bottom" , legend.text  = element_text(size = rel(0.5))) +
  ggtitle('figure 3.2' ) + theme(plot.title = element_text(face = 'italic' , size = 10 , colour = '#553146'))

grid.arrange(plot1 , plot2 , nrow = 2)