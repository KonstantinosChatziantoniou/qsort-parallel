## @knitr plotbarN
library(ggplot2)
library(reshape2)
library(gridExtra)
##script.dir <- dirname(sys.frame(1)$ofile)
rel.loc = "/../../outN.csv"
##pat = paste(script.dir, rel.loc,sep = '')
data.for.n <- read.csv('../../outN.csv', header = TRUE, sep = ',')
half.data = data.for.n[1:6,]
##print(half.data)
melted.data <- melt(half.data, id = "elements")
##print(melted.data)

Colors <- c( '#336B87', '#2A3132', '#46211A' , '#693D3D' , '#BA5536' , '#A43820')
plot1 <- ggplot(melted.data, aes(x = elements , y = value ,fill = variable)) +
  geom_bar( stat = "identity" , ,position = "dodge") + 
  scale_x_continuous(breaks = 12:24) +
  scale_fill_manual("Version" ,values = c("seq.stdlib" = Colors[1],
                                    "sequential" = Colors[2] ,
                                    "pthread" = Colors[3],
                                    "cilk" = Colors[4],
                                    "openmp" = Colors[5],
                                    "pthread.9000" = Colors[6])) + 
  theme(legend.position = "none")

half.data = data.for.n[7:12,]
melted.data <- melt(half.data, id = "elements")

Colors <- c( '#336B87', '#2A3132', '#46211A' , '#693D3D' , '#BA5536' , '#A43820')
plot2 <- ggplot(melted.data, aes(x = elements , y = value ,fill = variable)) +
  geom_bar( stat = "identity" , ,position = "dodge") + 
  scale_x_continuous(breaks = 12:24) +
  scale_fill_manual("Version" ,values = c("seq.stdlib" = Colors[1],
                                          "sequential" = Colors[2] ,
                                          "pthread" = Colors[3],
                                          "cilk" = Colors[4],
                                          "openmp" = Colors[5],
                                          "pthread.9000" = Colors[6]))+ 
  theme(legend.position = "none")
half.data = data.for.n[13,]
melted.data <- melt(half.data, id = "elements")

Colors <- c( '#336B87', '#2A3132', '#46211A' , '#693D3D' , '#BA5536' , '#A43820')
plot3 <- ggplot(melted.data, aes(x = elements , y = value ,fill = variable)) +
  geom_bar( stat = "identity" , ,position = "dodge") + 
  scale_x_continuous(breaks = 12:24) +
  scale_fill_manual("Version" ,values = c("seq.stdlib" = Colors[1],
                                          "sequential" = Colors[2] ,
                                          "pthread" = Colors[3],
                                          "cilk" = Colors[4],
                                          "openmp" = Colors[5],
                                          "pthread.9000" = Colors[6]))+ 
  theme(legend.direction = "horizontal", legend.position = "bottom" , legend.text  = element_text(size = rel(0.5))) 
  

grid.arrange(arrangeGrob(plot1 , plot2),plot3 ,  widths = c(6,6,0.4))
