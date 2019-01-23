import matplotlib.pyplot as plt
from random_walk import RandomWalk

while True:
    rw = RandomWalk(500000)
    rw.fill_walk()
    plt.figure(dpi = 140,figsize=(10,6))
    point_numbers = list(range(rw.num_points))
    # plt.scatter(rw.x_values,rw.y_values,s = 1,c = point_numbers,cmap = plt.cm.hot,edgecolors= 'none')
    # plt.scatter(0,0,s = 10,c = 'green',edgecolors= 'none')
    # plt.scatter(rw.x_values[-1],rw.y_values[-1],s = 10,c = 'red',edgecolors= 'none')
    plt.plot(rw.x_values,rw.y_values,linewidth = 1)
    plt.plot(0,0,linewidth = 35,)
    plt.plot(rw.x_values[-1],rw.y_values[-1],linewidth = 35)
    plt.axes().get_xaxis().set_visible(False)
    plt.axes().get_yaxis().set_visible(False)
    plt.show()
    run = input('another? y/n\n')
    if run == 'n':
        break