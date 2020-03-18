#!/bin/env/python3
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial
import struct

ser = serial.Serial('COM11', 9600)                         # Change to the actual com-port

adc_scale = 5/(2**24 - 1) # V/lsb

x_len = 10000

min_val = 0
max_val = 0

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = list(range(0, x_len))
ys = [0]*x_len
ax.set_ylim([0, 65535])

line, = ax.plot(xs, ys)

def animate(i, ys):
    #global min_val, max_valpython
    ch = ser.read(1)
    val = ""
    while(ch != b'\r'):
        #print(ch)
        if ch != b'\r':
            ch = ch.decode()
            val = val + ch
        ch = ser.read(1)

    val = int(val)
    if (val & 0x8000) == 0x8000:
        val = -( (val ^ 0xffff) + 1)
    print(val)

    #assert ((adval[0] & 0xc0) >> 6 == 0)
    #assert ((adval[1] & 0xc0) >> 6 == 1)
    #assert ((adval[2] & 0xc0) >> 6 == 2)
    #assert ((adval[3] & 0xc0) >> 6 == 3)

    #val = ((adval[0] & 0x3f) << 18) | ((adval[1] & 0x3f) << 12) | ((adval[2] & 0x3f) << 6) | (adval[3] & 0x3f)
    #if (val & 0x800000) == 0x800000:
    #    val = -( (val ^ 0xffffff) + 1)
    

    ys.append(int(val))
    ys = ys[-x_len:]

    line.set_ydata(ys)
    return line,


ani = animation.FuncAnimation(fig, animate, fargs=(ys,), interval=0.1, blit=True)
plt.show()
