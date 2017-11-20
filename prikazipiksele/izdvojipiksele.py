#
#
#

#
import numpy
import Image
import struct
import argparse

#
parser = argparse.ArgumentParser()
parser.add_argument('src')
parser.add_argument('dst')
args = parser.parse_args()

#
def izdvoji_piksele(im, dst):
	#
	h = im.shape[0]
	w = im.shape[1]

	#
	f = open(dst, 'wb')

	tmp = [None]*w*h
	for y in range(0, h):
		for x in range(0, w):
			tmp[y*w + x] = im[y, x]

	#
	data = struct.pack('%sB' % w*h, *tmp)
	f.write(data)

	#
	f.close()

#
src = args.src
dst = args.dst

#
try:
	im = numpy.asarray(Image.open(src).convert('L'))

	izdvoji_piksele(im, dst)
except:
	print 'Doslo je do pogreske!'