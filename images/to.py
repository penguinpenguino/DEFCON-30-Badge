import sys, os

def main():
	if sys.argv.__len__() < 2:
		return
	if not ".bmp" in sys.argv[1]:
		os.system("convert -monochrome " + sys.argv[1] + " " + sys.argv[1] + ".bmp")
		sys.argv[1] = sys.argv[1] + ".bmp"
	out = open(sys.argv[1] + ".h", 'w')
	inp = open(sys.argv[1], 'rb')
	dat = inp.read()
	out.write("#pragma once\n\nconst unsigned long sz = ")
	out.write(str(dat.__len__()))
	out.write(";\nconst unsigned char dat[] = {")
	for i in range(dat.__len__()):
		out.write(str(int(dat[i])))
		if i < dat.__len__() - 1:
			out.write(", ")
	out.write("};")

if __name__ == "__main__":
	main()
