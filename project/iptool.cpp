/************************************************************
 *															*
 * This sample project include three functions:				*
 * 1. Add intensity for gray-level image.					*
 *    Input: source image, output image name, value			*
 *															*
 * 2. Image thresholding: pixels will become black if the	*
 *    intensity is below the threshold, and white if above	*
 *    or equal the threhold.								*
 *    Input: source image, output image name, threshold		*
 *															*
 * 3. Image scaling: reduction/expansion of 2 for 			*
 *    the width and length. This project uses averaging 	*
 *    technique for reduction and pixel replication			*
 *    technique for expansion.								*
 *    Input: source image, output image name, scale factor	*
 *															*
 ************************************************************/

#include "../iptools/core.h"
#include <strings.h>
#include <string.h>
#include "../iptools/utility/utility.h"

using namespace std;

#define MAXLEN 256


vector<vector<int> > isFunction(char *pch, int i, vector<vector<int> > param, vector<int> &func){
	printf("is function pch:%s\n", pch);
	printf("function i=%d\n",i);

	int temp = 0;

	printf("about to parse\n");
	if(strncasecmp(pch,"add",MAXLEN)==0){
	//if(pch == "add"){
		pch = strtok(NULL, " ");
		//printf("add param: %s\n", pch);
		//adjList[x].push_back();
		temp = atoi(pch);
		//param[i].push_back(temp);
		param[i][0]=temp;
		
		func[i]=0;
		//return 1;
	}
	if(strncasecmp(pch,"binarize",MAXLEN)==0){
		pch = strtok(NULL, " ");
		temp = atoi(pch);
		param[i][0]=temp;

		func[i]=1;

	}
	if(strncasecmp(pch,"scale",MAXLEN)==0){
		pch = strtok(NULL, " ");
		temp = atoi(pch);
		param[i][0]=temp;
		
		func[i]=0;
	}
	if(strncasecmp(pch,"colorvisual",MAXLEN)==0){

		pch = strtok(NULL, " ");
		param[i][0]=atoi(pch);
		pch = strtok(NULL, " ");
		param[i][1]=atoi(pch);

		func[i]=3;


	}
	if(strncasecmp(pch,"dualthres",MAXLEN)==0){
		//tokenize
		pch = strtok(NULL, " ");
		param[i][0]=atoi(pch);
		pch = strtok(NULL, " ");
		param[i][1]=atoi(pch);

		pch = strtok(NULL, " ");
		param[i][2]=atoi(pch);

		func[i]=4;

	}
	if(strncasecmp(pch,"histostretch",MAXLEN)==0){

		pch = strtok(NULL, " ");
		
		param[i][0]=atoi(pch);
		
		pch = strtok(NULL, " ");
		param[i][1]=atoi(pch);

		func[i]=5;

	}	
	if(strncasecmp(pch,"althistostretch",MAXLEN)==0){

		pch = strtok(NULL, " ");
		
		param[i][0]=atoi(pch);
		
		pch = strtok(NULL, " ");
		param[i][1]=atoi(pch);

		func[i]=6;

	}
	if(strncasecmp(pch,"histothres",MAXLEN)==0){

		//thresh
		pch = strtok(NULL, " ");
		param[i][0]=atoi(pch);
		
		//background or foreground
		pch = strtok(NULL, " ");
		param[i][1]= *pch;
		
		//a
		pch = strtok(NULL, " ");
		param[i][2]=atoi(pch);

		//b
		pch = strtok(NULL, " ");
		param[i][3]=atoi(pch);

		func[i]=7;

	}
	if(strncasecmp(pch,"colorstretch",MAXLEN)==0){
		//tokenize
		//printf("int i = %d", i);
		pch = strtok(NULL, " ");
		//printf("color visual param 1: %s\n", pch);
		param[i][0]= *pch;
		//param[i][1] = atoi(pch);
		pch = strtok(NULL, " ");
		param[i][1]=atoi(pch);

		pch = strtok(NULL, " ");
		param[i][2]=atoi(pch);

		func[i]=8;
	}

	printf("finsihing parsing\n");
	return param;
}

void utility::createRoi(int x, int y, int sx, int sy ,vector <image> &roi,image &src,int i, string isColor){
//void utility::createRoi(int x, int y, int sx, int sy ,vector <image> &roi,image src){
	image tempRoi;
	int iMax = x + sx;
	int jMax = y + sy;


	tempRoi.resize(sx, sy);

		for(int i = 0; i < (x+sx); i++){
		for (int j=0; j<(y+sy); j++)
		{
			if (isColor.find(".ppm") == string::npos) {
				tempRoi.setPixel(i-x,j-y,checkValue(src.getPixel(i,j)));
			
			}
			else{
			tempRoi.setPixel(i-x, j-y, RED, checkValue(src.getPixel(i, j, RED)));
			tempRoi.setPixel(i-x, j-y, GREEN, checkValue(src.getPixel(i, j, GREEN)));
			tempRoi.setPixel(i-x, j-y, BLUE, checkValue(src.getPixel(i, j, BLUE)));
			}
		}
		}
	

	roi[i] = tempRoi;
	
}




int main (int argc, char** argv)
{
	image src, tgt,tempImg;
	FILE *fp;
	char str[MAXLEN];
	char outfile[MAXLEN];
	char *pch;
	char t[MAXLEN], v1[MAXLEN], v2[MAXLEN];
	char numRoi[MAXLEN];

	char funcName[MAXLEN];
	
	string isPPM; 
	

	


	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}
	

	//white reads line by line
	while(fgets(str,MAXLEN,fp) != NULL) {
		vector<vector<int> > param;
	
		pch = strtok(str, " ");
		src.read(pch);
		
	

		pch = strtok(NULL, " ");
		strcpy(outfile, pch);

		isPPM = outfile;

		//preparing to create ROIs

		//resize tempImg to source size will be used to overlap other images
		tempImg.resize(src.getNumberOfRows(), src.getNumberOfColumns());
		tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());

		//upto 3 ROIs
		vector<image> roi(3);
		roi[0]=src;
		roi[1]=src;
		roi[2]=src;

		//1.) read number of ROIs
		pch = strtok(NULL, " ");
		strcpy(numRoi, pch);

		//testing if parsing num of ROIs worked

		int numDim = atoi(numRoi);
		int x[numDim], y[numDim], sx[numDim], sy[numDim];
		
		//will store the function name for each ROI
		vector<int> func(numDim, 0); 
		
		

		//token the rest of the string in a for loop with #roi as iterations 
		for(int i = 0; i < atoi(numRoi); i++){
			
			//creating matrix 
			if(i==0){
				//upto 4 paramters for each function so setting it 4 and 0
			 	param.resize(atoi(numRoi), std::vector<int>(4,0));

			}


			//loading x			
			pch = strtok(NULL, " ");
			//printf("pch = %s", pch);
			//strcpy(x[i], pch);
			x[i] = atoi(pch);
			//printf("x: %d i:%d\n",  atoi(x[1]),i);
			//("x: %d i:%d\n",  x[i],i);

			//loading y
			pch = strtok(NULL, " ");
			//strcpy(y[i], pch);
			y[i] = atoi(pch);
			//printf("y: %d i:%d\n",  atoi(y[1]),i);
			//printf("y: %d i:%d\n",  y[i],i);

			//loading sx
			pch = strtok(NULL, " ");
			//strcpy(sx[i], pch);
			sy[i] = atoi(pch);





			//loading sy
			pch = strtok(NULL, " ");
			sx[i] = atoi(pch);

			//strcpy(sy[i], pch);


			//create roi image
			utility::createRoi(x[i],y[i], sx[i],sy[i], roi, src, i, isPPM);
			
			//if next token is function then check how many parameters needed then tokenize those parameters 
			pch = strtok(NULL, " ");
			strcpy(funcName, pch);
			param = isFunction(funcName, i, param, func);

			

		}
		printf("finsihing loop and parsing\n");

		//printf("\n------------end for----------\n");


	//utility::addGrey(src,tgt,0);
	utility::copy(src,tgt,0);

	for(int i = atoi(numRoi); i >= 1; i--){

		int iMax = x[i-1] + sx[i-1];
		int jMax = y[i-1] +  sy[i-1];
		printf("before going into function %d\n",func[i-1]==0);

		if(func[i-1]==0){
				utility::addGrey(roi[i-1],tempImg,param[i-1][0]);

        }
		else if(func[i-1]==1){
			utility::binarize(roi[i-1],tempImg,param[i-1][0]);
		}
		else if(func[i-1]==2){
			utility::scale(roi[i-1],tempImg,param[i-1][0]);
		}
		else if(func[i-1]==3){

			utility::colorvisual(roi[i-1],tempImg,param[i-1][0],param[i-1][1]);

        }
		else if(func[i-1]==4){
			utility::dualthres(roi[i-1],tempImg,param[i-1][0],param[i-1][1],param[i-1][2]);

		}
		else if(func[i-1]==5){

			utility::histostretch(roi[i-1],tempImg,param[i-1][0],param[i-1][1]);

		}
		else if(func[i-1]==6){
			utility::althistostretch(roi[i-1],tempImg,param[i-1][0],param[i-1][1]);

		}
		else if(func[i-1]==7){
			//printf("0: %d, 1: %d, 2: %d, 3:%d \n",param[i-1][0], param[i-1][1], param[i-1][2], param[i-1][3]);
			utility::histothres(roi[i-1],tempImg,param[i-1][0],param[i-1][1],param[i-1][2], param[i-1][3]);

		}
		else if(func[i-1]==8){
			printf("0: %d, 1: %d, 2: %d \n",param[i-1][0], param[i-1][1], param[i-1][2]);
			utility::colorstretch(roi[i-1],tempImg,param[i-1][0],param[i-1][1],param[i-1][2]);
		}
		else {
			printf("No function: %s\n", pch);
			continue;
		}
		
		printf("finished proccesing image \n");
		//tempImg.save("diditwork.ppm");
		//x40,y30
		
		
		//overlapping ROI images together 
		string temp; 
		temp = outfile;
		
		//if not .ppm then only print grey scale
		if (temp.find(".ppm") == string::npos) {
			for (int h=0; h<src.getNumberOfRows(); h++){
				for (int n=0; n<src.getNumberOfColumns(); n++){
					if(h >= x[i-1] && h  <= iMax){
						if(n >= y[i-1] && n <= jMax){
							//printf("in first if\n");
							tgt.setPixel(h,n,utility::checkValue(tempImg.getPixel(h-x[i-1],n- x[i-1]))); //may be wrong 
					
						}
					}
				}
			}
		}
		else{
			printf("in else\n");
			for (int h=0; h<src.getNumberOfRows(); h++){
				for (int n=0; n<src.getNumberOfColumns(); n++){
					if(h >= x[i-1] && h  <= iMax){
						if(n >= y[i-1] && n <= jMax){
							for (int rgb = 0; rgb <= 2; rgb++){
								tgt.setPixel(h,n,rgb,utility::checkValue(tempImg.getPixel(h-x[i-1],n- y[i-1],rgb))); 
							}
		
					
						}
					}
					else{
						for (int rgb = 0; rgb <= 2; rgb++){
								tgt.setPixel(h,n,rgb,utility::checkValue(src.getPixel(h,n,rgb))); 
							}
							
					}
				}
			}
		}
		


		
		//printf("fin overlap\n");

	}//end for 


		tgt.save(outfile);
	}


	return 0;
}

