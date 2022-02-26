#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include <sstream>
#include <math.h>

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);
		static void addGrey(image &src, image &tgt, int value);
		static void binarize(image &src, image &tgt, int threshold);
		static void scale(image &src, image &tgt, float ratio);
		static void dualthres(image &src, image &tgt, int threshold, int V1, int V2);
		static void colorvisual(image &src, image &tgt, int threshold,int value);
		static void createRoi(int x, int y, int sx, int sy ,vector <image> &roi,image &src,int i, string isColor);
		static void histostretch(image &src, image &tgt, int a,int b);
		static void althistostretch(image &src, image &tgt, int a,int b);
		static void histothres(image &src, image &tgt, int t, char bg, int a, int b);
		static void colorstretch(image &src, image &tgt, int c, int a,int b);
		static void copy(image &src, image &tgt, int value);



};

#endif

