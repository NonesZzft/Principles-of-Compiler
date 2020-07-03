import tkinter as tk
from tkinter import messagebox

index = 0
err = 0

def hit():
	global index
	global err
	index = 0
	err = 0
	cd = e.get()
	result = exp(cd)
	if index!=len(cd):
		error()
	if err == 0:
		var.set(cd + " = " + str(result))

def error():
	global err
	err = 1
	tk.messagebox.showinfo(title='error', message='表达式有错，请重新输入')

def match(expectedToken, cd):
	global index
	if cd[index] == expectedToken:
		index += 1
	else :
		error()

def exp(cd):
	global index
	temp = term(cd)
	if index==len(cd):
		return temp
	if cd[index]=='+':
		match('+', cd)
		temp += exp(cd)
	elif cd[index]=='-':
		match('-', cd)
		temp -= exp(cd)
	return temp

def term(cd):
	global index
	temp = factor(cd)
	if index==len(cd):
		return temp
	if cd[index]=='*':
		match('*', cd)
		temp *= term(cd)
	elif cd[index]=='/':
		match('/', cd)
		temp /= term(cd)
	return temp

def factor(cd):
	global index
	temp = 0
	if index==len(cd):
		error()
	elif cd[index]=='(':
		match('(', cd)
		temp = exp(cd)
		match(')', cd)
	else :
		if cd[index].isdigit():
			while cd[index].isdigit():
				temp = temp * 10 + int(cd[index])
				index += 1
				if index==len(cd):
					return temp
		else :
			error()
	return temp




top = tk.Tk()
top.title("右结合")

label = tk.Label(top, text = "计算一个表达式\n支持 + - * / ( )\n请不要输入任何空格\n", width=50, height=8, fg = "blue", font=("Arial", 12))
label.pack()

e = tk.Entry(top, text = "0", width=30)
e.pack()

label = tk.Label(top, text = "", width=40, height=2, fg = "blue")
label.pack()

bt = tk.Button(top, text = "Calculate", width=20, height=3,command=hit)
bt.pack()

var = tk.StringVar()
label_output = tk.Label(top, textvariable=var, width=30, height=7, fg = "blue", font=("Arial", 12))
label_output.pack()

top.mainloop()