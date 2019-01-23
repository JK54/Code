import json
import pygal
import math
from itertools import groupby

def draw_line(x_data,y_data,title,y_legend):
    xy_map = []
    for x,y in groupby(sorted(zip(x_data,y_data)),key = lambda a:a[0]):
        y_list = [v for _, v in y]
        xy_map.append([x,sum(y_list) / len(y_list)])
    x_unique,y_mean = [*zip(*xy_map)]
    line_chart = pygal.Line()
    line_chart._title = title
    line_chart.x_labels = x_unique
    line_chart.add(y_legend,y_mean)
    line_chart.render_to_file(title + ".svg")
    return line_chart

filename = 'btc_close_2017.json'
with open(filename) as fs:
    data = json.load(fs)
dates,months,weeks,weekdays,close_set = [],[],[],[],[]
for daily in data:
    date = daily['date']
    month = int(daily['month'])
    week = int(daily['week'])
    weekday = daily['weekday']
    close = int((float(daily['close'])))
    dates.append(date)
    months.append(month)
    weeks.append(week)
    weekdays.append(weekday)
    close_set.append(close)

idx_month = dates.index('2017-12-01')
line_chart_month = draw_line(months[:idx_month],close_set[:idx_month],'收盘价月日均值(￥)','月日均值')
line_chart_month

idx_week = dates.index('2017-12-10')
line_chart_week = draw_line(weeks[1:idx_week],close_set[:idx_month],'收盘价周日均值(￥)','周日均值')
line_chart_week
