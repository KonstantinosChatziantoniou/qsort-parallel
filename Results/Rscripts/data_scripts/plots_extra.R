## @knitr plotextra
library(ggplot2)
library(reshape)
library(gridExtra)
library(cowplot)
data1 <- read.csv('../../outExtraPth.csv', header = TRUE, sep = ',')
data2 <- read.csv('../../outExtraCilk.csv', header = TRUE, sep = ',')
##data2 <- ((data2[,-7])[,-7])[,-7]
data3 <- read.csv('../../outExtraOpenmp.csv', header = TRUE, sep = ',')
data4 <- read.csv('../../outExtraPth9000.csv', header = TRUE, sep = ',')
data <- c(data1[,-2] , data2[,-2] , data3[,-2] , data4[,-2])

melted1 <- melt(data1 , id = 'N')
melted2 <- melt(data2 , id = 'N')
melted3 <- melt(data3 , id = 'N')
melted4 <- melt(data4 , id = 'N')

plot1 <- ggplot(melted1) + geom_line(aes(x = N , y = value , colour = variable)) + 
  xlab("minimum N for parallelisation" ) + ylab("Time") + 
  theme(axis.text = element_text(size = 5) , axis.title = element_text(size = 6))+
  labs(title = "Pthread" ) +
  theme(plot.title = element_text(hjust = 0.5)) +
  theme(legend.position = "none")+ theme_gray(base_size = 14) + guides(color=FALSE)


plot2 <- ggplot(melted2) + geom_line(aes(x = N , y = value , colour = variable)) + 
  xlab("minimum N for parallelisation") + ylab("Time") + 
  labs(title = "Cilk") +
  theme(plot.title = element_text(hjust = 0.5))+
  theme( legend.position = "none")+ theme_gray(base_size = 14)+ guides(color=FALSE)


plot3 <- ggplot(melted3) + geom_line(aes(x = N , y = value , colour = variable)) + 
  xlab("minimum N for parallelisation") + ylab("Time") + 
  labs(title = "Openmp" ) +
  theme(plot.title = element_text(hjust = 0.5))+
  theme(legend.position = "none")+ theme_gray(base_size = 14)+ guides(color=FALSE)


plot4 <- ggplot(melted4) + geom_line(aes(x = N , y = value , colour = variable)) + 
  xlab("minimum N for parallelisation") + ylab("Time") + 
  labs(title = "Pthread9000" ) +
  theme(plot.title = element_text(hjust = 0.5))+
  theme(legend.position = "none") + theme_gray(base_size = 14)+ guides(color=FALSE)

plot5 <- ggplot(melted4) + geom_line(aes(x = N , y = value , colour = variable)) + 
  xlab("minimum N for parallelisation") + ylab("Time") + 
  labs(title = "Pthread9000" , color = "Number of threads") +
  scale_color_hue(labels = c('1','2' , '3' , '4' , '5' , '6' , '7' , '8')) + 
  scale_fill_manual("Number of threads") +
  theme(legend.direction = "horizontal", legend.position = "right") + 
  theme(plot.title = element_text(hjust = 0.5))
pltleg <- get_legend(plot5)
gl <- ggdraw(pltleg)
gd <- ggdraw(plot_grid(plot_grid(plot1 , plot2 , plot3 , plot4 ,  ncol = 2) , 
                       plot_grid(pltleg) , nrow = 2 , rel_heights = c(1,0.1)))
##print(gd)

gobl1 <- arrangeGrob(plot1 , plot4 , ncol = 2)
gobl2 <- arrangeGrob(plot2 , plot3 , ncol = 2)
grid.arrange(gobl1 , gobl2 , pltleg, heights = c(1,1,0.2))