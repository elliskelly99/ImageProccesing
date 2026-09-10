#include "utility.h"

#define MAXRGB 255
#define MINRGB 0

std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}
/*-----------------------------------------------------------------------**/

void utility::copy(image &src, image &tgt, int value)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,RED,(src.getPixel(i,j,RED)));
			tgt.setPixel(i,j,GREEN,(src.getPixel(i,j,GREEN)));
			tgt.setPixel(i,j,BLUE,(src.getPixel(i,j,BLUE)));

		}
}
/*-----------------------------------------------------------------------**/
void utility::addGrey(image &src, image &tgt, int value)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value)); 
		}
}

/*-----------------------------------------------------------------------**/
void utility::binarize(image &src, image &tgt, int threshold)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if (src.getPixel(i,j) < threshold)
				tgt.setPixel(i,j,MINRGB);
			else
				tgt.setPixel(i,j,MAXRGB);
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::scale(image &src, image &tgt, float ratio)
{
	int rows = (int)((float)src.getNumberOfRows() * ratio);
	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
	tgt.resize(rows, cols);
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{	
			/* Map the pixel of new image back to original image */
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				/* Directly copy the value */
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
				/* Average the values of four pixels */
				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
				tgt.setPixel(i,j,checkValue(value/4));
			}
		}
	}
}
/*-----------------------------------------------------------------------**/
void utility::dualthres(image &src, image &tgt, int threshold, int V1, int V2)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{	
			if (src.getPixel(i,j) > threshold){
				
				if(checkValue(src.getPixel(i,j) + V1) >= MAXRGB){
					tgt.setPixel(i,j,MAXRGB);
				}
				
				else
					tgt.setPixel(i,j,checkValue(src.getPixel(i,j) + V1));
			}
			else if(src.getPixel(i,j) < threshold){
			
				if(checkValue(src.getPixel(i,j) - V2) <= MINRGB){
					tgt.setPixel(i,j,MINRGB);
				}
				
				else 
					tgt.setPixel(i,j,checkValue(src.getPixel(i,j) - V2));
			}
			
			else if(src.getPixel(i,j) == threshold){
				tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
			}
		
		}
	}
}
/*-----------------------------------------------------------------------**/
void utility::colorvisual(image &src, image &tgt, int threshold,int value)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			// |V1  –  I(I,j)|  <  T1
			if(abs((value-src.getPixel(i,j)))< threshold){
		//	if (src.getPixel(i,j) < threshold){
					//tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
					tgt.setPixel(i,j,RED,255);
					//tgt.setPixel(i,j,GREEN,0);
					//tgt.setPixel(i,j,BLUE,0);


			}
			else{
				tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
			}
			// tgt.setPixel(i,j,GREEN,0); 
			// tgt.setPixel(i,j,BLUE,0); 


			//tgt.setPixel(i,j,1,checkValue(src.getPixel(i,j,1)+value)); 
			//tgt.setPixel(i,j,2,checkValue(src.getPixel(i,j,2)+value)); 


			//tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value)); 

		}
	}
}


/*-----------------------------------------------------------------------**/
//asignment 2
///

int histochange(int pixel, int a, int b, int minInt, int maxInt){
	int dynamic;

	dynamic = b - a;

	
	if (dynamic == 0){
		return minInt;
	}
	else if (pixel <= a){
		return minInt;
	}
	else if (pixel >= b){
		return maxInt;
	}
	else
	{
		//OUTVAL = (INVAL - INLO) * ((OUTUP-OUTLO)/(INUP-INLO)) + OUTLO from http://spatial-analyst.net/ILWIS/htm/ilwisapp/stretch_algorithm.htm
		return ((((pixel - a) * (maxInt - minInt)) / (b - a)) + minInt);
		

	}

}

void utility::histostretch(image &src, image &tgt, int a,int b)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	
	int iMax = -1;
	int iMin = 2000;

	//finding iMin and iMax 
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if(src.getPixel(i, j) > iMax) iMax = src.getPixel(i, j);
			else if(src.getPixel(i, j) < iMin) iMin = src.getPixel(i, j);
		}//j loop
	}//i loop
	
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			int pixel = src.getPixel(i, j);
			int hsChange = histochange(pixel, iMin, iMax, a, b);
			tgt.setPixel(i, j, checkValue(hsChange));
		}//j loop
	}//i loop

}


void utility::althistostretch(image &src, image &tgt, int a,int b)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	
	double iMax = -1;
	double iMin = 2000;

	//finding iMin and iMax 
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if(src.getPixel(i, j) > iMax) iMax = src.getPixel(i, j);
			else if(src.getPixel(i, j) < iMin) iMin = src.getPixel(i, j);
		}//j loop
	}//i loop
	
	//alterntative utilizing 
	iMax = 1.05 * iMax;
	iMin = 1.05 * iMin;

	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			int pixel = src.getPixel(i, j);
			//int hsChange = histochange(pixel, a, b, iMin, iMax);
			int hsChange = histochange(pixel, iMin, iMax, a, b);
	
			tgt.setPixel(i, j, checkValue(hsChange));
		}//j loop
	}//i loop

}

//void utility::histothres(image &src, image &tgt, int T, int a1, int b1, int a2, int b2){
void utility::histothres(image &src, image &tgt, int t, char bg, int a, int b){	
	 	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
		
		int hsChange;
		int iMax;
		int iMin;
		int isBG = -1; //false 
		
		vector<int>bgPix;
		vector<int>fgPix;

		//THRESHOLDING 
		for (int i=0; i<src.getNumberOfRows(); i++){
			for (int j=0; j<src.getNumberOfColumns(); j++)
			{
				int pixel = src.getPixel(i, j);
	
				if (src.getPixel(i,j) < t){
					//BACKGROUND
					bgPix.push_back(pixel);
				} 
				else{
					//FOREGROUND
					fgPix.push_back(pixel);
				} 
			}//j loop
		}
		
		if(bg == 'B'){
			iMin = *min_element(bgPix.begin(),bgPix.end());
			iMax = *max_element(bgPix.begin(),bgPix.end());
		}
		else{
			iMin = *min_element(fgPix.begin(),fgPix.end());
			iMax = *max_element(fgPix.begin(),fgPix.end());
		}
		

		for (int i=0; i<src.getNumberOfRows(); i++){
			for (int j=0; j<src.getNumberOfColumns(); j++)
			{
				//THRESHOLDING 
				if (src.getPixel(i,j) < t){
					isBG = 0;//BACKGROUND
				} 
				else{
					isBG = 1;//FOREGROUND
				} 
				
				int pixel = src.getPixel(i, j);
				
				if(isBG == 0 && bg == 'B'){
					 hsChange = histochange(pixel, iMin, iMax, a, b);
					 tgt.setPixel(i, j, checkValue(hsChange));
				}
				else if(isBG == 1 && bg == 'F'){
					 hsChange = histochange(pixel, a, b, iMin, iMax);
					 tgt.setPixel(i, j, checkValue(hsChange));
				}
				else{
					tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
				}
				
				//tgt.setPixel(i,j,checkValue(src.getPixel(i,j)));
			}//j loop
		}
	
}

void utility::colorstretch(image &src, image &tgt, int c, int a,int b)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	if(c == int('R')){
		printf(" in r ");
		c = 1;
	}
	else if(c == int('G')){
	printf(" in g ");

		c = 2;
	}
	else if(c == int('B')){
		printf(" in b ");

		c = 3;
	}

	printf("   c = %d ", c);
	int iMax = -1;
	int iMin = 2000;

	//finding iMin and iMax 
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if(src.getPixel(i, j,c) > iMax) iMax = src.getPixel(i, j,c);
			else if(src.getPixel(i, j,c) < iMin) iMin = src.getPixel(i, j,c);
		}//j loop
	}//i loop
	
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			int pixel = src.getPixel(i, j, c);

			int hsChange = histochange(pixel, a, b, iMin, iMax);
			//tgt.setPixel(i, j, c, checkValue(hsChange));
			tgt.setPixel(i, j, c, checkValue(hsChange));

			
			for (int rgb = 0; rgb <= 2; rgb++)
			{
					if (rgb != c){
						tgt.setPixel(i, j, rgb, checkValue(src.getPixel(i, j, rgb)));
					}
			}
			
			
		}//j loop
	}//i loop
}
