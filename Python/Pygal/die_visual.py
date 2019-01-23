from die import Die
import pygal

die_1 = Die()
die_2 = Die(10)
results = []
for roll_num in range(1000000):
    results.append(die_1.roll() + die_2.roll())
freq = []
min = 2
max = die_1.num_sides + die_2.num_sides + 1
for value in range(min,max):
    frequency = results.count(value)
    freq.append(frequency)

hist = pygal.Bar()
hist.title = "D6"
hist.x_labels = list(range(min,max))
hist_x_title = "Result"
hist.y_title = "Freq"
hist.add('D6',freq)
hist.render_to_file("11.svg")
print(freq)