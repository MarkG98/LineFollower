import serial
import csv
import time

arduinoComPort = '/dev/ttyACM0'

baudRate = 9600

t_list, lv_list, rv_list, ls_list, rs_list = [], [], [], [], []

# open the serial port
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

while True:
  #
  # ask for a line of data from the serial port, the ".decode()" converts the
  # data from an "array of bytes", to a string
  #
  lineOfData = serialPort.readline().decode()
  #
  # check if data was received
  #
  if len(lineOfData) > 0:
    #
    # data was received, convert it into 4 integers
    #
    time, left_val, right_val, leftspeed, rightspeed = (x for x in lineOfData.split(','))

    if (str(left_val) == "-1"):
      break

    t_list.append(time)
    lv_list.append(left_val)
    rv_list.append(right_val)
    ls_list.append(leftspeed)
    rs_list.append(rightspeed)

    print(lv_list)

with open('data1.csv', 'w', newline='') as csvfile:
  fieldnames = ['time','left_val', 'right_val', 'leftspeed', 'rightspeed']
  writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

  writer.writeheader()
  for i in range(len(lv_list)):
    writer.writerow({'time': t_list[i], 'left_val': lv_list[i], 'right_val': rv_list[i], 'leftspeed': ls_list[i], 'rightspeed': rs_list[i]})