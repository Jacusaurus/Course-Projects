import csv
import Tkinter, tkFileDialog
import numpy as np
#from iPython import embed
#embed()
root = Tkinter.Tk()
root.withdraw()
results = []
file_path = tkFileDialog.askopenfilename()
with open(file_path) as csvfile:
    creader = csv.reader(csvfile)
    skip = next(creader)
    data = [map(float, l) for l in creader]
# [{k:float(d[k]) for k in d} for d in data] #convert values to floats
    # data = np.genfromtxt(csvfile, dtype = None, delimiter = ',')
    # reader = csv.DictReader(csvfile, quotechar=',',
    #                     quoting=csv.QUOTE_MINIMAL)

                        
#print data
for i in range(len(data)):
	homework_array = np.array(data[i][0])
	for a in range(1,12):
		homework_array = np.append(homework_array, data[i][a])
	quiz_array = np.array(data[i][12])
	for a in range(13,21):
		quiz_array = np.append(quiz_array, data[i][a])
	exam_array = (np.array(data[i][21]))
	exam_array = np.append(exam_array, data[i][22])
	exam_array = np.append(exam_array, data[i][23])
	final = data[i][24]
	hw_total = 0
	quiz_total = 0
	exam_total = 0
	for j in range(0,12):
		hw_total += homework_array[j]
	quiz_array = np.sort(quiz_array)
	for j in range(2,9):
		quiz_total += quiz_array[j]
	exam_array = np.sort(exam_array)
	hw_percent = hw_total / 240
	quiz_percent = quiz_total / 70
	#print "Average homework percentage: "
	#print hw_percent
	#print homework_array
	#print "Average quiz percentage:"
	#print quiz_percent
	#print quiz_array
	exam1_percentage = exam_array[0] / 50
	exam2_percentage = exam_array[1] / 50
	#print exam_array
	exam3_percentage = exam_array[2] / 50
	final_percentage = final / 50
	final_grade = 25 * hw_percent + 15 * quiz_percent + exam1_percentage * 10 + exam2_percentage * 15 + exam3_percentage * 15 + final_percentage * 20
	print ('Final grade: ')
	print final_grade


#print homework_array
#print quiz_array
#print exam_array
#print final
    