#Cody Mitchell
#9/03/15
#temps.py
#
# August 2013 High Temps for Knoxville,TN
# Hwk 1 for COSC 370/Math 371 (Fall 2014)
#
from numpy import *
import matplotlib.pyplot as plt
xData = arange(1,32)    # Ranges for x and y axes must match
tData = [86,87,84,86,86,86,84,83,90,89,88,85,86,79,83,81, \
         75,80,81,85,81,88,89,87,84,85,86,88,88,90,90]
avg = [86.]  # First value for montly avg high temp is just Day 1 temp
plt.title('High Temperatures for Knoxville,TN - August 2013')

## 1) CALCULATE A RUNNING MONTHLY AVERAGE AND PRINT IT OUT IN A TABLE
##    IT DOES NOT MATTER HOW THE TABLE IS FORMATTED

sum = 86 #used for running avg comp

for i in range(1,31):#calculate running monthly avg
    sum += tData[i]#maintain running sum
    average = sum/(i+1)#calculate daily avg
    print("day:",(i+1),"average:","%.2f"%average)#print table
    avg.append(average)#add on to end of list of avgs


## 2) CREATE A GRAPH FOR THE DATA USING MATPLOTLIB
##	- PLOT RED POINTS WITH BLUE LINE FOR ORIGINAL DATA
##	- SHOW CHANGE IN AVERAGE HIGH WITH GREEN DASHED LINE
##	- SET DISPLAY RANGES FOR X AND Y AXES
##		- X SHOULD RANGE FROM 0 TO 32
##		- Y SHOULD RANGE FROM 70 TO 95
##	- ENABLE GRID DISPLAY
##	- LABEL AXES AND SET TITLE
##	- USE MATPLOTLIB.PYPLOT.TEXT() TO LABEL THE MONTHLY AVERAGE LINE

plt.grid(True)#enabling grid
plt.axis([0,32,70,95])#set x and y axes
plt.ylabel('High Temp')#y-axis label
plt.xlabel('Day')#x-axis label

plt.plot(xData,avg,'g--')#plot green dotted line for avg
plt.text(15, 86, 'Monthly Avg', color = 'green')#label avg line 

plt.plot(xData,tData,'ro',xData,tData)#plotting daily highs
#red dots and connecting blue line

plt.show()
