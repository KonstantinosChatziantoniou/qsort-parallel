setwd("~/Documents/Repos/qsort-parellel/Results")
library(tinytex)
library(ggplot2)
library(reshape2)

Names <- c("sequential", "pthread" , "cilk", "openmp")

MyData <- read.csv(file="outN.csv", header=TRUE, sep=",")
md <-data.frame(MyData)

size <- md[,1]
time <- md[,2]
plot <- ggplot(md , aes(x = size , y = time)) + geom_line(position = "dodge" , stat = "identity" )

plot2 <- ggplot(md , aes(x = size))
counter <- 0
for(i in 2:5){
  plot2 <- plot2 + geom_line(aes(y = md[,i]))
  counter <- counter + 1
}
print(plot2)
Colors <- c('#90AFC5', '#336B87', '#2A3132', '#763626')
plot3 <- ggplot(md , aes(x = size)) + geom_bar(aes(y = md[, 2]) , color = "blue") + geom_bar(aes(y = md[, 3]), color="red")
mlt <- melt(md , id = "elements")
plot4 <-ggplot(mlt ) + geom_bar(aes(x = elements , y = value , fill = variable ), 
                                                               position = "dodge",
                                stat = "identity"
                                , lwd = 0.4) + scale_x_continuous(breaks = 12:17) +scale_fill_manual("library" 
                                                                                                     ,values = c("sequential" = Colors[1] ,
                                                                                                                                    "pthread" = Colors[2],
                                                                                                                                    "cilk" = Colors[3],
                                                                                                                                    "openmp" = Colors[4])) + xlab("Size 2^") + ylab("Time")
    


print(plot4)

plot5 = ggplot(mlt , aes(x = elements, y = value)) + geom_line(aes(colour = variable, group = variable))+scale_color_manual("impl" ,values = c("sequential" = Colors[1] ,
                                                                                                                 "pthread" = Colors[2],
                                                                                                                 "cilk" = Colors[3],
                                                                                                                 "openmp" = Colors[4])) + xlab("Size 2^") + ylab("Time") + guides(colour = guide_legend(override.aes = list(alpha = 1, size = 9)))                                                                                                                                                                            
print(plot5)