import csv
from matplotlib import pyplot as plt
from datetime import datetime

filename = 'death_valley_2014.csv'
with open(filename) as f:
    reader = csv.reader(f)
    header_row = next(reader)
    highs = []
    dates = []
    lows = []
    for row in reader:
        try:
            high = int(row[1])
            low = int(row[3])
            date = datetime.strptime(row[0],'%Y-%m-%d')
        except ValueError:
            print(date,'missing data')
        else:
            highs.append(high)
            lows.append(low)
            dates.append(date)

    fig = plt.figure(dpi = 140,figsize = (10,6))
    plt.plot(dates,highs,c = 'red',alpha = 0.5)
    plt.plot(dates,lows,c = 'blue',alpha = 0.5)
    plt.fill_between(dates,highs,lows,facecolor = 'blue',alpha = 0.1)
    plt.title("Daily High And Low Temperature-2014",fontsize = 24)
    plt.xlabel('',fontsize = 14)
    fig.autofmt_xdate()
    plt.ylabel("Temperature(F)",fontsize = 14)
    plt.tick_params(axis = 'both',which = 'major',labelsize = 14)
    plt.show()
    # plt.savefig('11.png')