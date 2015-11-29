# include <windows.h>
# include <GL/glut.h>
# include <math.h>
# include <stdio.h>
# include <GL/GLAUX.H>
# include <stdlib.h>
# include <iostream>
using namespace std;
#define PI 3.1415926
#define chassis1 5,0.5,5
#define chassis2 5,0,5
#define chassis3 -5,0,5
#define chassis4 -5,0.5,5
#define chassis5 -5,0.5,-5
#define chassis6 -5,0,-5
#define chassis7 5,0.5,-5
#define chassis8 5,0,-5
#define human1 -0.2,0,0.15
#define human2 0.2,0,0.15
#define human3 0.2,0,-0.15
#define human4 -0.2,0,-0.15
#define human5 -0.2,0.9,0.15
#define human6 0.2,0.9,0.15
#define human7 0.2,0.9,-0.15
#define human8 -0.2,0.9,-0.15
#define human9 -0.3,0.9,0.15
#define human10 0.3,0.9,0.15
#define human11 0.3,0.9,-0.15
#define human12 -0.3,0.9,-0.15
#define human13 -0.2,1.5,0.15
#define human14 0.2,1.5,0.15
#define human15 0.2,1.5,-0.15
#define human16 -0.2,1.5,-0.15

const GLfloat n=100;
const GLfloat Pi=3.1415926536f;
static int mode = 1;
static int light = 1;
static int xangle = -17;
static int yangle = 0;
static int zangle = 0;
static GLfloat xcamera = -30.0f;
static GLfloat ycamera = 5.0f;
static GLfloat zcamera = -30.0f;
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };  
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };  
GLfloat mat_ambient_color[] = { 1.0,1.0,1.0, 1.0 };  
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };  
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  
GLfloat no_shininess[] = { 0.5 };  
GLfloat low_shininess[] = { 10.0 };  
GLfloat high_shininess[] = {200.0 };  
GLfloat mat_emission[] = {1.0, 0.0, 1.0, 1.0};  
GLfloat ambient[] = { 0.01, 0.01, 0.01, 1.0 };  
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  
GLfloat position[] = { 1.0, 1.0, 1.0, 0.0 };  
GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };  
GLfloat local_view[] = { 0.0 };  
GLuint texture[9];
class color
{
private:
	GLfloat R;
	GLfloat G;
	GLfloat B;
public:
	color(GLfloat rr=0,GLfloat gg=0,GLfloat bb=0)
	{
		R=rr;
		G=gg;
		B=bb;
	}
	~color(){}
	GLfloat getR(){return R;}
	GLfloat getG(){return G;}
	GLfloat getB(){return B;}
};
bool LoadTexture(LPTSTR szFileName, GLuint &texid) // Creates Texture From A Bitmap File
{
	HBITMAP hBMP; // Handle Of The Bitmap
	BITMAP BMP; // Bitmap Structure

	glGenTextures(1, &texid); // Create The Texture
	hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (!hBMP) // Does The Bitmap Exist?
	return FALSE; // If Not Return False

	GetObject(hBMP, sizeof(BMP), &BMP); // Get The Object
	// hBMP: Handle To Graphics Object
	// sizeof(BMP): Size Of Buffer For Object Information
	// &BMP: Buffer For Object Information
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Pixel Storage Mode (Word Alignment / 4 Bytes)
	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texid); // Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE,   BMP.bmBits);

	DeleteObject(hBMP); // Delete The Object

	return TRUE; // Loading Was Successful
}
void LoadGLTextures()
{
	LoadTexture("E:\\lego\\humanFace.bmp",texture[0]);
	LoadTexture("E:\\lego\\shirtFront.bmp",texture[1]);
	LoadTexture("E:\\lego\\shirtLeft.bmp",texture[2]);
	LoadTexture("E:\\lego\\shirtBack.bmp",texture[3]);
	LoadTexture("E:\\lego\\shirtRight.bmp",texture[4]);
	LoadTexture("E:\\lego\\trousersFront.bmp",texture[5]);
	LoadTexture("E:\\lego\\trousersLeft.bmp",texture[6]);
	LoadTexture("E:\\lego\\trousersBack.bmp",texture[7]);
	LoadTexture("E:\\lego\\trousersRight.bmp",texture[8]);
}
void init()			             
{
	glEnable(GL_TEXTURE_2D);
	LoadGLTextures();
	glClearColor(0.0, 0.1, 0.1, 0.0);  
	glEnable(GL_DEPTH_TEST);  
	glShadeModel(GL_SMOOTH);  
  
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);  
	glLightfv(GL_LIGHT0, GL_POSITION, position);  
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);  
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);  
  
	glEnable(GL_LIGHTING);  
	glEnable(GL_LIGHT0);  
	glEnable(GL_DEPTH_TEST);
	glOrtho(40.0,-40.0,40.0,-40.0,-70.0,70.0);
}
void reshape (int w, int h)
{
	glViewport(30, 30, w, h);  
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();  
	glOrtho(40.0,-40.0,40.0,-40.0,-70.0,70.0);
	glMatrixMode(GL_MODELVIEW);  
	glLoadIdentity();  
}
void drawHorizontalCircle(GLfloat radius,GLfloat height,color colors)
{
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE); 
	glColor3f(colors.getR(),colors.getG(),colors.getB());
	glBegin(GL_POLYGON);
	for(int i=0;i<n;i++)	glVertex3f(radius*cos(2*PI/n*i),radius*sin(2*PI/n*i),height);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
}
void drawCylinder(GLdouble radius,GLdouble height,GLdouble verticalCut,GLdouble horizontalCut,color cylinderBottomColor)
{
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glColor3f(cylinderBottomColor.getR(),cylinderBottomColor.getG(),cylinderBottomColor.getB());
	glRotatef(90,1,0,0);
	drawHorizontalCircle((GLfloat)radius,0,cylinderBottomColor);
	drawHorizontalCircle((GLfloat)radius,(GLfloat)height,cylinderBottomColor);
	GLUquadricObj *cannon;
	cannon = gluNewQuadric();
	gluCylinder(cannon,radius,radius,height,verticalCut,horizontalCut);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}
void drawGroundPiece(color groundColor)
{
	glPushMatrix();
	//using this function to draw the chassis, the point and color of the chassis has been defined in start
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glBegin(GL_QUADS);
	glColor3f(groundColor.getR(),groundColor.getG(),groundColor.getB());
    glVertex3f(chassis1);    glVertex3f(chassis2);    glVertex3f(chassis3);    glVertex3f(chassis4);
	glColor3f(groundColor.getR(),groundColor.getG(),groundColor.getB());
	glVertex3f(chassis1);    glVertex3f(chassis4);    glVertex3f(chassis5);    glVertex3f(chassis7);
	glColor3f(groundColor.getR(),groundColor.getG(),groundColor.getB());
	glVertex3f(chassis2);    glVertex3f(chassis3);    glVertex3f(chassis6);    glVertex3f(chassis8);
	glColor3f(groundColor.getR(),groundColor.getG(),groundColor.getB());
	glVertex3f(chassis5);    glVertex3f(chassis6);    glVertex3f(chassis8);    glVertex3f(chassis7);
	glColor3f(groundColor.getR(),groundColor.getG(),groundColor.getB());
	glVertex3f(chassis1);    glVertex3f(chassis2);    glVertex3f(chassis8);    glVertex3f(chassis7);
	glColor3f(groundColor.getR(),groundColor.getG(),groundColor.getB());
	glVertex3f(chassis3);    glVertex3f(chassis4);    glVertex3f(chassis5);    glVertex3f(chassis6);
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	for(int i=-4;i<=4;i=i+2)
	{
		for(int j=-4;j<=4;j=j+2)
		{	
			glPushMatrix();
			glTranslatef(i,0,j);
			drawCylinder(0.5,0.3,10,10,groundColor);
			glPopMatrix();
		}
	}
}
void drawGround(int x,int y,color groundColor)
{
	for(int i=0;i<x;i++)
	{
		glPushMatrix();
		glTranslatef((GLfloat)(i*10.0),0,0);
		for(int j=0;j<y;j++)
		{
			glPushMatrix();
			glTranslatef(0,0,(GLfloat)(j*10.0));
			drawGroundPiece(groundColor);
			glPopMatrix();
		}
		glPopMatrix();
	}
}
void drawTree()
{
	color treeLeafColor(0.086,0.66,0.316);
	color treeRootColor(0.55,0.35,0.3);
	color treeBodyColor(0.516,0.352,0.199);
	
	glPushMatrix();
	drawCylinder(3,0.4,30,30,treeRootColor); //draw tree root

		glPushMatrix();
		glTranslatef(0,0.3,0);
		drawCylinder(0.5,9.7,10,10,treeBodyColor); //draw tree body
		glPopMatrix();

		for(GLfloat i=1.0;i<=4.0;i=i+0.5)
		{
			glPushMatrix();
			glTranslatef(0,(GLfloat)(2*i-11.0),0);
			drawCylinder(i,0.3,30,30,treeLeafColor); //draw tree leaf
			glPopMatrix();
		}
	glPopMatrix();
}
void drawPeople()
{
	color bodyColor(0.9,0.8,0.6);
	glPushMatrix();
		glPushMatrix();
		//using this function to draw the chassis, the point and color of the chassis has been defined in start
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
		
		glBegin(GL_QUADS);
		glColor3f(bodyColor.getR(),bodyColor.getG(),bodyColor.getB());
		glVertex3f(human1);    glVertex3f(human2);    glVertex3f(human3);    glVertex3f(human4);
		glEnd();

		glBindTexture(GL_TEXTURE_2D,texture[8]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);glVertex3f(human4);    
			glTexCoord2f(1.0f,0.0f);glVertex3f(human1);    
			glTexCoord2f(1.0f,1.0f);glVertex3f(human5);    
			glTexCoord2f(0.0f,1.0f);glVertex3f(human8);
		glEnd();
		
		glBindTexture(GL_TEXTURE_2D,texture[6]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);glVertex3f(human2);    
			glTexCoord2f(1.0f,0.0f);glVertex3f(human3);    
			glTexCoord2f(1.0f,1.0f);glVertex3f(human7);    
			glTexCoord2f(0.0f,1.0f);glVertex3f(human6);
		glEnd();
		
		glBindTexture(GL_TEXTURE_2D,texture[5]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);glVertex3f(human1);    
			glTexCoord2f(1.0f,0.0f);glVertex3f(human2);    
			glTexCoord2f(1.0f,1.0f);glVertex3f(human6);    
			glTexCoord2f(0.0f,1.0f);glVertex3f(human5);
		glEnd();
		
		glBindTexture(GL_TEXTURE_2D,texture[7]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);glVertex3f(human3);    
			glTexCoord2f(1.0f,0.0f);glVertex3f(human4);    
			glTexCoord2f(1.0f,1.0f);glVertex3f(human8);    
			glTexCoord2f(0.0f,1.0f);glVertex3f(human7);
		glEnd();
		
		glBegin(GL_QUADS);
		glColor3f(bodyColor.getR(),bodyColor.getG(),bodyColor.getB());
		glVertex3f(human5);    glVertex3f(human6);    glVertex3f(human7);    glVertex3f(human8);
		glEnd();
		
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();
		
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
		glBegin(GL_QUADS);
		glColor3f(bodyColor.getR(),bodyColor.getG(),bodyColor.getB());
		glVertex3f(human9);    glVertex3f(human10);    glVertex3f(human11);    glVertex3f(human12);
		glColor3f(bodyColor.getR(),bodyColor.getG(),bodyColor.getB());
		glVertex3f(human9);    glVertex3f(human12);    glVertex3f(human16);    glVertex3f(human13);
		glColor3f(bodyColor.getR(),bodyColor.getG(),bodyColor.getB());
		glVertex3f(human10);    glVertex3f(human11);    glVertex3f(human14);    glVertex3f(human15);
		glColor3f(bodyColor.getR(),bodyColor.getG(),bodyColor.getB());
		glVertex3f(human9);    glVertex3f(human10);    glVertex3f(human14);    glVertex3f(human13);
		glColor3f(bodyColor.getR(),bodyColor.getG(),bodyColor.getB());
		glVertex3f(human11);    glVertex3f(human12);    glVertex3f(human16);    glVertex3f(human15);
		glColor3f(bodyColor.getR(),bodyColor.getG(),bodyColor.getB());
		glVertex3f(human13);    glVertex3f(human14);    glVertex3f(human15);    glVertex3f(human16);
		glEnd();
		glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0,1.9,0);
		drawCylinder(0.15,0.4,10,10,bodyColor);
		glPopMatrix();
	glPopMatrix();
}
void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':yangle++;glutPostRedisplay();break;
	case 'A':yangle+=10;glutPostRedisplay();break;
	case 's':if(xangle<=19)xangle++;glutPostRedisplay();break;
	case 'S':if(xangle<=10)xangle+=10;glutPostRedisplay();break;
	case 'd':yangle--;glutPostRedisplay();break;
	case 'D':yangle-=10;glutPostRedisplay();break;
	case 'w':if(xangle>=-29)xangle--;glutPostRedisplay();break;
	case 'W':if(xangle>=-20)xangle-=10;glutPostRedisplay();break;
	case 'l':light*=-1;zcamera--;glutPostRedisplay();
	case 'r':xangle = -17;	yangle = 90;zangle = 0;xcamera = 0.0f;ycamera = 5.0f;zcamera = 0.0f;glutPostRedisplay();break;
	case 'm':printf("%f %f %f  %f %f %f\n",(float)xangle,(float)yangle,(float)zangle,(float)xcamera,(float)ycamera,(float)zcamera);break;
	case 'c':mode*=-1;glutPostRedisplay();break;
	case 27:exit(0);break;
	default:break;
	}
}
void display(void)
{
	if(mode==-1)glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	else		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );	
	if(light==-1){glDisable( GL_LIGHTING );	glDisable(GL_LIGHT0);}
	else		{glEnable( GL_LIGHTING );	glEnable(GL_LIGHT0);}	
	color groundColor(0.0,1.0,0.0);	
	color bodyColor(0.9,0.8,0.6);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(xangle,1,0,0);
	glRotatef(yangle,0,1,0);
	glRotatef(zangle,0,0,1);
	glTranslatef(xcamera,ycamera,zcamera);	
	glClear(GL_COLOR_BUFFER_BIT); 
	drawGround(6,6,groundColor);
		glPushMatrix();
		glTranslatef(4,0,5);
		drawTree();
		glTranslatef(12,0,-4);
		drawTree();
		glTranslatef(14,0,6);
		drawTree();
		glTranslatef(16,0,-2);
		drawTree();
		glTranslatef(0,0,40);
		drawTree();
		glTranslatef(-16,0,-5);
		drawTree();
		glTranslatef(-12,0,4);
		drawTree();
		glTranslatef(-10,0,0);
		drawTree();
		glPopMatrix();
		
		glTranslatef(10,0,10);		
		glScalef(8.0,-4.0,4.0);
		drawPeople();
	glPopMatrix();
	glFlush();
	//glutSwapBuffers();
}
void main(int argc,char** argv)
{
	glutInit(&argc,argv);
	//Set display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    //set top-left display-window position
    glutInitWindowPosition(100, 100);
    //set display window width and height
    glutInitWindowSize(500, 500);
    //Create display window
    glutCreateWindow("LEGO Park Model");
	//Initialize
    init(); 
	//Send graphics to display window
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	// keyboard input
	glutKeyboardFunc(keyboard);
    //Display everything and wait
    glutMainLoop();
}
