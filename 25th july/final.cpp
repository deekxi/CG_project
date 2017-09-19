#include<string.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <iostream.h>
#include "math.h"
#include<glut.h>

void tex(char *str,int x,int y)
{
	int len=strlen(str);
	glRasterPos2i(x,y);
	
	for(int i=0;i<len;i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
	}	
}
char text[10];
int n=1,i=10;
typedef struct treenode 
{ 
	int data;
	struct treenode* left; 
	struct treenode* right; 
	struct treenode* parent; 
}TREENODE; 

TREENODE* root=NULL; 

char buff1[10];
void add_node(TREENODE** t_root, TREENODE** current) 
{ 
	if(*t_root==NULL) 
	{ 
		*t_root = *current; 
		return; 
	} 
	if((*current)->data < (*t_root)->data) 
	{ 
		if((*t_root)->left==NULL)
		{ 
			(*t_root)->left = (*current); 
		} 
		else 
		{ 
			add_node(&((*t_root)->left),current); 
		} 
	}	
	else	
	{ 
		if((*t_root)->right==NULL) 
		{ 
			(*t_root)->right = *current; 
		}	
		else 
		{ 
			add_node(&((*t_root)->right),current); 
		} 
	} 
}
 
void accept_tree()
{ 
	int n,count=0; 
	cout<<"\nCREATING BST: (enter 0 to finish)\n";
	cout<<"\nEnter node value: and number of nodes less than 8"<<endl;  
	while(1)
	{ 
		fflush(stdin);
		cin>>n;
		count++; 
		if(n==0 || count>7 )
		break;  
		TREENODE* current=new TREENODE; 
		current->data = n; 
		current->right = NULL; 
		current->left = NULL; 
		current->parent = NULL; 
		add_node(&root,&current); 
	} 
}


void inorder(TREENODE* root) 
{ 
	if(root!=NULL) 
	{ 
		inorder(root->left); 
		printf("%d\t",root->data);

		inorder(root->right); 
	} 
} 

void preorder(TREENODE* root) 
{ 
	if(root!=NULL) 
	{ 
		printf("%d\t",root->data); 
		preorder(root->left); 
		preorder(root->right);
	} 
} 
char str[20];
void postorder(TREENODE* root) 
{ 
	if(root!=NULL) 
	{	int i=0;
 		postorder(root->left); 
		postorder(root->right); 
		printf("%d\t",root->data);
		str[i++]=(int)root->data;
	} 
} 

void draw_line(float x1,float y1,float x2, float y2)
{ 
	glBegin(GL_LINES); 
	glVertex2f(x1,y1); 
	glVertex2f(x2,y2); 
	glEnd(); 
} 

void draw_text(char* text,float x, float y)
{ 
	GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24; 
	glRasterPos3f(x-0.5, y, 0); 
	glPushMatrix();
	glColor3f(1,0,0);
	glTranslated(x,y,0);
	glutSolidSphere(1,20,20);
	glPopMatrix();
	glColor3f(0,1,0);
	for (int i=0;text[i]!='\0';i++)
		glutBitmapCharacter(font_style, text[i]);

} 

void drawNode(TREENODE* t_root,float x1,float y1,int level) 
{ 
	if(level>2) 
		return;
	else
	{	
		if(t_root==NULL)
			return; 
	} 
    float segments = 25; 
    float radius = 1.0; 
    float left_angle = 245; 
    float right_angle = 115; 
    float branch_length = 12-level*2.5; 
	float angle_change = 20; 
    char buff[5];
	itoa(t_root->data,buff,10);
	draw_text(buff,x1,y1);
	if(t_root->left) 
	{ 
		float angle = left_angle - level*angle_change; 
		double radian = angle*3.14/180; 
		float m = (double)tan((double)radian); 
		float x2 = x1 + branch_length * sin((double) radian); 
		float y2 = y1 + branch_length * cos((double) radian);
		drawNode(t_root->left,x2,y2,level+1);
		
		if(level<2)
			draw_line(x1,y1,x2,y2); 
	}
 
	if(t_root->right)
	{ 
		float angle = right_angle + level*angle_change; 
		float radian = angle*3.14/180; 
		float m = (double)tan((double)radian); 
		float x2 = x1 + branch_length * sin((double) radian); 
		float y2 = y1 + branch_length * cos((double) radian); 
		drawNode(t_root->right,x2,y2,level+1);

		if (level<2) 
			draw_line(x1,y1,x2,y2);
	}
} 

void display() 
{ 
    glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity(); 
	glTranslatef(0,10,-30); 
	glColor3f(1,1,1); 
	drawNode(root,0,0,0);
	glutSwapBuffers(); 
}

void reshape (int w, int h) 
{ 
	glViewport (0, 0, (GLsizei)w, (GLsizei)h); 
	glMatrixMode (GL_PROJECTION); 
	glLoadIdentity (); 
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0); 
	glMatrixMode (GL_MODELVIEW); 
} 



void keyboard(unsigned char key, int x, int y) 
{ 

    if(key=='i' || key=='I')
	{
		printf("inorder\n");
	    inorder(root);
	    printf("\n");
	}
	if(key=='p' || key=='P')
	{
	    printf("preorder\n");
	    preorder(root);
		printf("\n");
	}
	if(key=='r' ||key=='R')
	{
		printf("postorder\n");
		postorder(root);
	}
} 

void menu(int id)
{
	switch(id)
	{
		case 1: printf("Inorder\n");
			    inorder(root);
				glRasterPos3f(500,500,0);
				printf("\n");
				break;

		case 2:	printf("Preorder\n");
				preorder(root);
				printf("\n");
				break;
		
		case 3:	printf("Postorder\n");
				postorder(root);
				printf("\n");
				break;
		default:exit(0);
	}
	glutPostRedisplay();
}


void init()
{
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //Load value 1 to Projection Matrix
	glOrtho(-2,2,-2,2,-2,2);	
	glEnable(GL_DEPTH_TEST);
	glutPostRedisplay();
}

void frontinit()
{
	glClearColor(0.941, 0.902, 0.549,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,1000,0,1000,-100,100);
	glutPostRedisplay();	
}

void titletext(char *str,int x,int y)
{
	int len=strlen(str);
	glRasterPos2i(x,y);
	
	for(int i=0;i<len;i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
	}	
}
void frontkey(unsigned char k,int x,int y)
{
	switch (k) 
	{
		case 'q':
		case 'Q':	exit(0);
					break;
		case 'N':
		case 'n':		accept_tree();
						glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
						glutInitWindowPosition(0,0);
						glutInitWindowSize(1200,800);
						glutCreateWindow("binary tree");
				
						glutReshapeFunc(reshape);//Change display callback according to your project
						glutCreateMenu(menu);	
						glutAddMenuEntry("Inorder",1);
						glutAddMenuEntry("Preorder",2);
						glutAddMenuEntry("Postorder",3);
						glutAttachMenu(GLUT_RIGHT_BUTTON);
						glutDisplayFunc(display);
						glutIdleFunc(display);
						glutKeyboardFunc(keyboard);
				     
						glutPostRedisplay();
						break;
		default:
					printf("Press another key!\n");
					break;
	}
}

void frontdisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.294, 0.000, 0.510);
	titletext("JAWAHARLAL NEHRU NATIONAL COLLEGE OF ENGINEERING, SHIVAMOGGA",50,900);

	glColor3f(0.545, 0.271, 0.075);
	tex("DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING",200,850);

	glColor3f(0.663, 0.663, 0.663);
	tex("A MINI PROJECT ON",385,775);

	glColor3f(0.000, 0.502, 0.502);
	titletext("BINARY TREE SIMULATION",325,700); //Adjust x co-ordinate here

	glColor3f(0.294, 0.000, 0.510);
	tex("SUBMITTED BY:",400,600);
	
	glColor3f(0.502, 0.000, 0.000);
	tex("ASHUTOSH SHENOY P",150,550);

	glColor3f(0.502, 0.000, 0.000);
	tex("4JN14CS018",150,500);

	glColor3f(0.502, 0.000, 0.000);
	tex("DEEKSHITH B.G",700,550);

	glColor3f(0.502, 0.000, 0.000);
	tex("4JN14CS027",700,500);

	glColor3f(0.000, 0.545, 0.545);
	tex("UNDER THE GUIDANCE OF:",350,425);
	
	glColor3f(0.502, 0.502, 0.000);
	tex("Mr. MOHAN H G",75,350);
	tex("Assistant Professor,",75,300);
	tex("Dept. of CSE,JNNCE",75,250);

	tex("Mr. RAVINDRA S",400,350);
	tex("Assistant Professor,",400,300);
	tex("Dept. of CSE,JNNCE",400,250);
	
	tex("Mrs. SREEDEVI S",725,350);
	tex("Assistant Professor,",725,300);
	tex("Dept. of CSE,JNNCE",725,250);
	
	glColor3f(0.184, 0.310, 0.310);
	tex("Press 'N' to Next",400,100);	
	glFlush();
	
}

void main (int argc, char **argv)
{ 
	
	glutInit(&argc,argv);	
	glutInitDisplayMode(GLUT_SINGLE|GLUT_DEPTH|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1200,800);

	glutCreateWindow("Project Name");
	frontinit();
	glutDisplayFunc(frontdisplay);
	glutKeyboardFunc(frontkey);		

	glutMainLoop (); 
}