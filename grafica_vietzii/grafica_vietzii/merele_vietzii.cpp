////COS CU MERE 

#include <stdlib.h> ///PENTRU TASTA ESC, LEGAT DE EXIT()
#include <glut.h> ///INLOCUITOR PENTRU GLU SI GL                
#include <math.h> ///PENTRU CALCULE
#include <windows.h> ///PENTRU SUNET
#include <mmsystem.h> ///PENTRU SUNET
#include <glaux.h> ///PENTRU FUNCTIILE DE TEXTURARE
#include "Kyle.h" ///PERSONAJUL DIN APLICATIE

#define PI 3.141///FOLOSIT PENTRU FRUNZA SI COTOR

///DEFINESTE VALORILE POZITIEI INITIALE A CAMEREI SI A FERESTREI DE VIZIONARE (MY_RESHAPE)
#define INIT_VIEW_X -4.0    
#define INIT_VIEW_Y 0.0
#define INIT_VIEW_Z -11.5
#define VIEW_LEFT -2.0
#define VIEW_RIGHT 2.0
#define VIEW_BOTTOM -2.0
#define VIEW_TOP 2.0
#define VIEW_NEAR 1.0
#define VIEW_FAR 200.0

///VARIABILE/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///VARIABILE ILUMINARE
GLfloat AmbientLight[]={0.3,0.3,0.3,1.0};                
GLfloat DiffuseLight[] ={1.0,1.0,1.0,1.0};
GLfloat SpecularLight[] ={1.0,1.0,1.0,1.0};
GLfloat SpecRef[] = {0.7,0.7,0.7,1.0};
GLfloat pozSursa[] = {30.0,55.0,-20.0,1.0};
GLint Shine =128;

///VARIABILE PENTRU MISCAREA CAMEREI PRIN MOUSE SI SAGETI (am luat dintr-un proiect de pe web doll.c)
GLint walkX=0,walkY=0,lookX=0,lookY=0;
GLint world=1,oldX=-1,oldY=-1;

///VARIABILE POM
int ok;
int flag=1;
GLfloat angle;

///VARIABILE TEXTURA
GLuint IDtextura;
GLuint ID1,ID2;
const char* sir;

///PROTOTIP TEXTURA
void incarca_textura(const char* s);

///VARIABILE PENTRU PRIMA FEREASTRA
GLint Xsize=1366;
GLint Ysize=768;
int view=0, ct=1;

///VARIABILE MENIU FUNDAL+CEATA
int aflag=1;
int flag2=0;

///VARIABILE SUBMENIU CULORI
GLfloat r=1,g=0,b=0;

///VARIABILE UMBRA
int check;

///VARIABILE SOARE/LUNA
GLfloat s=1,u=0.9,n=0;

///VARIABILA MOD FULLSECREEN
int fullscreen=0;

///VARIABILE DOLL
GLfloat xr=-25;

///VARIABILA SUPRAFATA COS
GLfloat COS[4][4][3] = {
    {{-1.5, -1.5, 0.0}, {-0.5, -2, 0.0}, 
    {0.5, -2, 0.0}, {1.5, -1.5, 0.0}},

    {{-2.5, -0.5, 0.0}, {-2.2, -2.2, 3.0}, 
    {2.2, -2.2, 3.0}, {2.5, -0.5, 0.0}},

    {{-2.5, 0.5, 0.0}, {-2.2, 2.2, 3.0}, 
    {2.2, 2.2, 3.0}, {2.5, 0.5, 0.0}},
 
    {{-1.5, 1.5, 0.0}, {-0.5, 2, 0.0}, 
    {0.5, 2, 0.0}, {1.5, 1.5, 0.0}}
};


///VARIABILA SUPRAFATA MAR
GLfloat MAR[4][4][3] = {
    {{-0.8, -1.5, 0}, {-0.8, -1.8, -0}, 
    {0.8, -1.8, 0}, {0.8, -1.5, 0}}, 

    {{-1.8, -0.5, 0}, {-1.9, -1.9, 3.0}, 
    {1.9, -1.9, 3.0}, {1.8, -0.5, 0}}, 

    {{-1.8, 0.5, -0}, {-1.9, 1.9, 3.0}, 
    {1.9, 1.9, 3.0}, {1.8, 0.5, -0}}, 

    {{-1.0, 1.5, -0}, {-1.0, 1.8, -0}, 
    {1.0, 1.8, -0.0}, {1.0, 1.5, -0}}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///FUNCTII MISCARE TASTE PENTRU SOARE (NU FOLOSESC)

//void CALLBACK mutaSursaDreapta(AUX_EVENTREC *event) {
//	if (pozSursa[0]<100)
//		pozSursa[0] += 10;
//}
//void CALLBACK mutaSursaStanga(AUX_EVENTREC *event) {
//	if (pozSursa[0]>-100)
//		pozSursa[0] -= 10;
//}

///FUNCTII UMBRE///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calcCoeficientiPlan(float P[3][3], float coef[4])
{
	float v1[3], v2[3];
	float length;
	static const int x=0;
	static const int y=1;
	static const int z=2;

//calculeaza doi vectori din trei puncte
	v1[x]=P[0][x]-P[1][x];
	v1[y]=P[0][y]-P[1][y];
	v1[z]=P[0][z]-P[1][z];

	v2[x]=P[1][x]-P[2][x];
	v2[y]=P[1][y]-P[2][y];
	v2[z]=P[1][z]-P[2][z];


//se calculeaza produsul vectorial al celor doi vectori
//care reprezinta un al treilea vector perpendicular pe plan
//ale carui componente sunt chiar coeficientii A,B,C din ecuatia planului

	coef[x]=v1[y]*v2[z]-v1[z]*v2[y];
	coef[y]=v1[z]*v2[x]-v1[x]*v2[z];
	coef[z]=v1[x]*v2[y]-v1[y]*v2[x];

//normalizeaza vectorul
	length=(float)sqrt((coef[x]*coef[x])+(coef[y]*coef[y])+(coef[z]*coef[z]));
	coef[x]/=length;
	coef[y]/=length;
	coef[z]/=length;
}


void MatriceUmbra(GLfloat puncte[3][3], GLfloat pozSursa[4],GLfloat mat[4][4])
{
	GLfloat coefPlan[4];
	GLfloat temp;

	//determina coeficientii planului
	calcCoeficientiPlan(puncte,coefPlan);

	//determina si pe D
	coefPlan[3]=-((coefPlan[0]*puncte[2][0])+(coefPlan[1]*puncte[2][1])+(coefPlan[2]*puncte[2][2]));

	//temp=A*xL+B*yL+C*zL+D*w
	temp=coefPlan[0]*pozSursa[0]+coefPlan[1]*pozSursa[1]+coefPlan[2]*pozSursa[2]+coefPlan[3]*pozSursa[3];

	//prima coloana
	mat[0][0]=temp-pozSursa[0]*coefPlan[0];
	mat[1][0]=0.0f-pozSursa[0]*coefPlan[1];
	mat[2][0]=0.0f-pozSursa[0]*coefPlan[2];
	mat[3][0]=0.0f-pozSursa[0]*coefPlan[3];
	//a doua coloana
	mat[0][1]=0.0f-pozSursa[1]*coefPlan[0];
	mat[1][1]=temp-pozSursa[1]*coefPlan[1];
	mat[2][1]=0.0f-pozSursa[1]*coefPlan[2];
	mat[3][1]=0.0f-pozSursa[1]*coefPlan[3];
	//a treia coloana
	mat[0][2]=0.0f-pozSursa[2]*coefPlan[0];
	mat[1][2]=0.0f-pozSursa[2]*coefPlan[1];
	mat[2][2]=temp-pozSursa[2]*coefPlan[2];
	mat[3][2]=0.0f-pozSursa[2]*coefPlan[3];
	//a patra coloana
	mat[0][3]=0.0f-pozSursa[3]*coefPlan[0];
	mat[1][3]=0.0f-pozSursa[3]*coefPlan[1];
	mat[2][3]=0.0f-pozSursa[3]*coefPlan[2];
	mat[3][3]=temp-pozSursa[3]*coefPlan[3];
}


///FUNCTII PENTRU PRIMA FEREASTRA (SI A DOUA)//////////////////////////////////////////////////////////////////////////////////////////////////////////

void myReshape(int w, int h)
{
    GLfloat Ratio;
    glViewport(0,0,w,h);
    Ratio=1.0*w/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0,Ratio,VIEW_NEAR,VIEW_FAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(INIT_VIEW_X,INIT_VIEW_Y,INIT_VIEW_Z);
	glLightfv(GL_LIGHT0, GL_POSITION, pozSursa);
}


void init()
{
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,900.0,0.0,600.0,50.0,-50.0);
	glutPostRedisplay(); 		
}


void display_string1(int x, int y, char *string, int font)
{
    int len,i;
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
    if(font==1)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
	if(font==2)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
	if(font==3)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,string[i]);
	if(font==4)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,string[i]);
	}
}


void display_string2(void)
{
	glClearColor(0.0f,  0.498039f, 1.0f,1);
    glClear(GL_COLOR_BUFFER_BIT);
	display_string1(290,540,"   GRAFICA ASISTATA DE CALCULATOR",1); 
	display_string1(315,500,"          PROIECT: COS CU MERE",1);
	display_string1(410,470,"UTILIZARE",2);
	display_string1(10,430,"MOUSE:",2);
	display_string1(10,400,"Utilizare cursor pentru rotatii X si Y.",3);
	display_string1(10,370,"Utilizare click dreapta pentru a selecta meniul pentru fundal si submeniul pentru culoare mar.",3);
	display_string1(10,330,"TASTATURA:",2);
	display_string1(10,300,"ESC pentru iesire din aplicatie.",3);
	display_string1(10,270,"Sagetile pentru miscarea camerei prin coordonate X si Z.",3);
	display_string1(10,240,"Spacebar-ul pentru intrarea in a doua fereastra.",3);
	display_string1(10,210,"Tastele a si d popt fi folosite pentru mutarea in stanga sau dreapta a personajului Kyle.",3);
	display_string1(320,180,"    APASA ODATA SPACEBAR-UL ALA!!! ",2);
	display_string1(550,160,"Multumesc :)",3);
	display_string1(750,120,"Paul Centea  ",2);
	glutPostRedisplay();
	glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///FUNCTII OBIECTE/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///FUNCTII POM
void makecylinder(float height,float Base)
{
    if(check == 0)glColor3f(0.35f,  0.16f, 0.14f);
    else glColor3f(0,0,0);
    
    glPushMatrix();
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
	gluCylinder(gluNewQuadric(), Base, Base - (0.2 * Base), height, 20, 20);
    glPopMatrix();
}


void maketree(float height,float Base)
{
    glPushMatrix();
    float angle;
    makecylinder(height, Base);
    glTranslatef(0.0f, height,0.0f);
    height -=height*0.2f;
    Base -=Base*0.3f;
    for(int a=0; a<4; a++)
       {
          angle = 20+((rand()%50));
          if(angle >47)
             angle = -(20+((rand()%50)));
				
          if (height > 1)
            {
              glPushMatrix();
              if (flag)
                glRotatef(angle, 1.0f, 0.0f, 1.0f);
              else
                glRotatef(angle, 0.0f, 1.0f, 1.0f);
              flag = !flag;
              maketree(height, Base); //recursiv
              glPopMatrix();
            }
          else
            {
			  glPushMatrix();
			  if(check == 0)glColor3f(0.0f, 1.0f, 0.0f);
              else glColor3f(0,0,0);
              
              glutSolidSphere(0.23f, 10, 10);
			  glPopMatrix();
            }
		    
		 if(ok==1)
            {
			  glPushMatrix();
			  if(check == 0)glColor3f(0.419608,0.556863,0.137255);
              else glColor3f(0,0,0);
			  
              glutSolidSphere(0.2f, 5, 5);
			  glPopMatrix();
		    }
		 else
			  if(ok==0)
				{
				  glPushMatrix();
				  if(check == 0)glColor3f(0.85,0.71,0.10);
                  else glColor3f(0,0,0);
				  
                  glutSolidSphere(0.2f, 5, 5);
				  glPopMatrix();
				}
			  else
				{
				  glPushMatrix();
				  if(check == 0)glColor3f(1.0f, 0.0f, 0.0f);
                  else glColor3f(0,0,0);
                  
                  glutSolidSphere(0.2f, 5, 5);
				  glPopMatrix();
				}
            }
   glPopMatrix();
}  


///FUNCTIE IARBA
void floor()
{  
   glPushAttrib(GL_LIGHTING_BIT);
   glDisable(GL_LIGHTING);
   sir=".\\grass.bmp";
   incarca_textura(sir);
   ID1=IDtextura;
   glEnable(GL_TEXTURE_2D);
   glColor3f(0.419608,0.556863,0.137255);
   glTranslatef(0,-5.45,0);
   glRotatef(90,1,0,0);
   glBindTexture( GL_TEXTURE_2D, ID1);

   glPushMatrix();
    glBegin(GL_QUAD_STRIP);
	    glTexCoord2f(0.0, 0.0);
		glVertex2f(-1200,-1200);
		glTexCoord2f(0.0, 1000.0);
		glVertex3f(-1200, 2000, -1);
		glTexCoord2f(1000.0, 1000.0);
		glVertex2f(1200, -1200);
		glTexCoord2f(1000.0, 0.0);
		glVertex3f(1200, 2000, -1);
	glEnd();
	glPopMatrix();
}


///FUNCTII FRUNZA
void ellipse(float radiusX, float radiusY) 
{
	int i;
	glBegin(GL_TRIANGLE_FAN);
	for(i=0; i<360; i++) 
	{
		float rad = i*(PI/180.0);
		glVertex2f(cos(rad)*radiusX,sin(rad)*radiusY);
	}
  glEnd();
}


void leaf()
{
   glPushMatrix();
   glColor3f(0.184314,0.309804,0.184314);
   glScalef(0.2,0.2,0.2);
   glRotatef(120,0,0,1);
   ellipse(2.0, 4.0);
   glPopMatrix();
}


///FUNCTII COTOR
void cylinder(float x1,float y1,float z1,float x2,float y2,float z2,float r1,float r2)
{
   int i;
   glBegin(GL_QUADS);
   for (i=0;i<100;i++)
     {
        glVertex3f(x1+r1*sin(PI*i/50),y1,z1+r1*cos(PI*i/50));
        glVertex3f(x2+r2*sin(PI*i/50),y2,z2+r2*cos(PI*i/50));
        glVertex3f(x2+r2*sin(PI*(i+1)/50),y2,z2+r2*cos(PI*(i+1)/50));
        glVertex3f(x1+r1*sin(PI*(i+1)/50),y1,z1+r1*cos(PI*(i+1)/50));
     }
   glEnd();
}


void tail(float x,float y,float z,float h,float w)
{
   float i;
   glPushMatrix();
   glColor3f(0.36,0.25,0.2);
   for (i=0;i<100;i++)
        cylinder(x+0.2*(1-cos(PI/2*(float)i/100)),y+0.3-1*i/100,0,x+0.2*(1-cos(PI/2*(float)(i+1)/100)),y+0.3-1*(i+1)/100,0,0.1,0.1);
   glRotatef(190,1,0,0);
   glPopMatrix();
}


///FUNCTIE DUNGA FRUNZA (SE POATE MAI SIMPLU)
void line()
{
   glPushMatrix();
   glColor3f(0,0,0);
   glScalef(0.1,0.1,0.1);
   glRotatef(90,0,1,0);
   glRotatef(30,-1,0,0);
   gluCylinder(gluNewQuadric(),0.1,0.1,14,2,1);
   glPopMatrix();
}


///FUNCTIE MAR
void apple()
{
   ///O JUMATATE DE MAR
   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,0, 1, 12, 4, &MAR[0][0][0]);
   glPushMatrix();
   glRotatef(180.0, 0, 1.0, 0);
   glEvalMesh2(GL_FILL, 0, 20, 0, 20);
   glPopMatrix();

   ///CEALALTA JUMATATE DE MAR
   glPushMatrix();
   glEvalMesh2(GL_FILL, 0, 20, 0, 20);
   glPopMatrix();
}


///FUNCTIE COS
void basket()
{



   //////COSUL FACUT DIN LINII

   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,0, 1, 12, 4, &COS[0][0][0]);

   glPushMatrix();
   glTranslatef(4.9,0,0.5);
   glColor3f(0,0.0,0.0);
   glRotatef(90.0, 1, 0.0, 0.0);
   glScalef(3,3,3);
   glEvalMesh2(GL_LINE, 0, 20, 0, 20); 
   glPopMatrix();

   if(check == 0)glColor3f(0.9,0.5,0.3);
   else glColor3f(0,0,0);

	//sir = ".\\basket.bmp";
	//incarca_textura(sir);
	//ID2 = IDtextura;

	

   ///COSUL FACUT CU UMPLERE
   glPushMatrix();
   glTranslatef(4.9,0,0.5);
   glRotatef(90.0, 1, 0.0, 0.0);
   glScalef(3,3,3);
   //glEnable(GL_TEXTURE_GEN_S); //generare coordonate de textura
   //glEnable(GL_TEXTURE_GEN_T);
   //glBindTexture(GL_TEXTURE_2D, ID2);
   glEvalMesh2(GL_FILL, 0, 20, 0, 20);
 /*  glDisable(GL_TEXTURE_GEN_S);
   glDisable(GL_TEXTURE_GEN_T);*/
   glPopMatrix();

}


///FUNCTIE SOARE/LUNA
void sun()
{
	glPushMatrix();
	glTranslatef(pozSursa[0], pozSursa[1], pozSursa[2]);
	glDisable(GL_TEXTURE_2D);
	glPointSize(5.0);
	auxSolidSphere(5);
	glPopMatrix();
}


///FUNCTII NORI
void mini()                                     

{
    ///STANGA

    glPushMatrix();
    glTranslatef(4,5.5,0);
	auxSolidSphere(4);
    glPopMatrix();

    ///DREAPTA

    glPushMatrix();
    glTranslatef(-8,5.5,0);
	auxSolidSphere(3.5);
    glPopMatrix();

    ///STANGA SUS

    glPushMatrix();
    glTranslatef(-3.5,9,0);
	auxSolidSphere(3.5);
    glPopMatrix();

    //DREAPTA SUS

    glPushMatrix();
    glTranslatef(1,9,0);
	auxSolidSphere(3);
    glPopMatrix();

    ///MIJLOC

    glPushMatrix();
    glTranslatef(-1.5,5.5,0);
	auxSolidSphere(4);
    glPopMatrix();

}


void cloud()                                        
{
    glPushMatrix();
	if(check==0)
    glColor3f (1,1,1);
	else
	glColor3f(0,0,0);
    glTranslatef(35,10,0);
    mini();
    glPopMatrix();


    glPushMatrix();
	if(check==0)
    glColor3f (1,1,1);
	else
	glColor3f(0,0,0);
    glTranslatef(28,16,0);
    mini();
    glPopMatrix();

    glPushMatrix();
	if(check==0)
    glColor3f (1,1,1);
	else
	glColor3f(0,0,0);
    glTranslatef(20,10,0);
    mini();
    glPopMatrix();
}


void clouds()                                   
{
    glPushMatrix();
    glTranslatef(-15.0,30.0,0.0);
    glScalef(0.7,0.7,0.0);
    cloud();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20.0,25.0,0.0);
    glScalef(0.7,0.7,0.0);
    cloud();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-60.0,25.0,0.0);
    glScalef(0.7,0.7,0.0);
    cloud();
    glPopMatrix();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///DISPLAY////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Display()
{
   ///VARIABILE POM PENTRU PUNEREA CRENGILOR INTR-O POZITIE CONSTANTA
   const double t = glutGet(GLUT_ELAPSED_TIME) / 100.0; 
   const double a = t*90.0;
   srand(GLUT_ELAPSED_TIME); //MISCAREA CIUDATA A POMILOR

   ///PARTEA CU UMBRELE IN DISPLAY
   GLfloat matUmbra[4][4];
   GLfloat puncte[3][3]={ { -100.0f, -5.0f, 50.0f },{ 100.0f, -5.0f, -20.0f },{ 50.0f, -5.0f, -20.0f }};

	
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   ///FORMAREA UMBREI
   MatriceUmbra(puncte,pozSursa,matUmbra);

   ///CONDITIA PENTRU AFISARE TEXT PRIMA FEREASTRA
 if(view==0)
   {
   init();
   display_string2();
   }
 else ///CEALALTA FEREASTRA
  {
   if(ct==1)
	   myReshape(Xsize,Ysize);	 

///CONDITIE PENTRU SETAREA CETII SI MODIFICAREA FUNDALULUI
 if(flag2==1)
   {
  GLfloat fogcolour[4]={1.0,1.0,1.0,1.0};

  glFogfv(GL_FOG_COLOR,fogcolour);              
  glFogf(GL_FOG_DENSITY,0.1);                   
  glFogi(GL_FOG_MODE,GL_EXP);                   
  glFogf(GL_FOG_START,3.0);                  
  glFogf(GL_FOG_END,100.0);                    
  glHint(GL_FOG_HINT, GL_FASTEST);             
  glEnable(GL_FOG);
  }

  if(flag2==0)
  {
	  glDisable(GL_FOG);
  }

  ///CONDITIA PENTRU MISCAREA MOUSE-ULUI
  glPushMatrix();

   if(world==1)
	 {
      	glTranslatef(walkX,-1,walkY);
	    glRotatef(lookY,0,1,0);
        glRotatef(lookX,1,0,0);
	 }

   glPushMatrix();

   glTranslatef(-10,-16,-75); ///AM SETAT VIEWPORT-UL ASTFEL CA SA POT DEPLASA CAMERA SI SA POT VEDEA OBIECTELE DE LA DISTANTELE DEFINITE (NEAR, FAR)
                          ///DE ACEEA FOLOSESC VALORI FOARTE MICI PENTRU TRANSLATII, DIMENSIONARII


//////OBIECTELE///////////////////////////////////////////////////////////////////////////////////////////////////

//////KYLE
   glPushMatrix();
   glLightfv(GL_LIGHT0,GL_POSITION,pozSursa);
   glTranslatef(xr,-1.0,10);
   glScalef(7,7,7);
   da=0;
   doll();
   glPopMatrix();

   ///ACELASI LUCRU
 //   eyeright();
 //   eyeleft();
 //   eyebrowleft();
 //   eyebrowright();
	//earleft();
	//earright();
	//hat();
	//hatLside();
	//hatRside();
 //   legright();
 //   legleft();
 //   armleft();
 //   armright();
 //   BellyCoat();
 //   bellyCoatbottom();
 //   neckring();
 //   handleft();
 //   handright();
	//hatadd();
 //   mouth();
 //   teeth();
 //   head();
 //   footleft();
 //   footright();
 //   topbutton();
 //   middlebutton();
 //   bottombutton();
 //   pupilleft();
 //   pupilright();


//////COS
   glPushMatrix();
   glLightfv(GL_LIGHT0,GL_POSITION,pozSursa);
   check=0;
   basket();
   glPopMatrix();



//////ALTE MERE

//////MERE SPATE
   glPushMatrix();
   glColor3f(1,0.0,0);
   glTranslatef(1.8,-1.7,-1.73);
   apple();
   glPopMatrix();

   glPushMatrix();
   glColor3f(0.419608,0.556863,0.137255);
   glTranslatef(5.0,-2,-2.6);
   apple();
   glPopMatrix();
   
   glPushMatrix();
   glColor3f(0.85,0.71,0.10);
   glTranslatef(8.0,-1.7,-1.73);
   apple();
   glPopMatrix();


//////MERE FATA
   glPushMatrix();
   glColor3f(0.419608,0.556863,0.137255);
   glTranslatef(1.8,-1.9,2.4);
   apple();
   glPopMatrix();

   glPushMatrix();
   glColor3f(0.85,0.71,0.10);
   glTranslatef(5.0,-2.2,2.7);
   apple();
   glPopMatrix();
   
   glPushMatrix();
   glColor3f(1,0.0,0);
   glTranslatef(8.0,-1.9,2.4);
   apple();
   glPopMatrix();


//////MAR GALBEN
   glPushMatrix();
   glColor3f(0.85,0.71,0.10);
   glTranslatef(1.0,0,0.5);
   apple();
   glPopMatrix();

   ///FRUNZA
   glPushMatrix();
   glTranslatef(1.5,2.5,0.5);
   leaf();
   glPopMatrix();

   ///LINIE FRUNZA
   glPushMatrix();
   glTranslatef(0.9,2.2,0.51);
   line();
   glPopMatrix();

   ///COTOR
   glPushMatrix();
   glTranslatef(0.8,3.5,0.5);
   tail(0,-1.1,0,0.3,0.52);
   glPopMatrix();



//////MAR ROSU
   glPushMatrix();
   glColor3f(r,g,b);
   glTranslatef(5.0,-0.2,0.0);
   apple();
   glPopMatrix();

   ///FRUNZA
   glPushMatrix();
   glTranslatef(5.5,2.3,0.5);
   leaf();
   glPopMatrix();

   ///LINIE
   glPushMatrix();
   glTranslatef(4.9,2.0,0.51);
   line();
   glPopMatrix();

   ///COTOR
   glPushMatrix();
   glTranslatef(4.8,3.3,0.5);
   tail(0,-1.1,0,0.3,0.52);
   glPopMatrix();


//////MAR VERDE
   glPushMatrix();
   glColor3f( 0.419608,0.556863,0.137255);
   glTranslatef(9.0,0,0.5);
   apple();
   glPopMatrix();

   ///FRUNZA
   glPushMatrix();
   glTranslatef(9.5,2.5,0.5);
   leaf();
   glPopMatrix();

   ///LINIE FRUNZA
   glPushMatrix();
   glTranslatef(8.9,2.2,0.51);
   line();
   glPopMatrix();

   ///COTOR
   glPushMatrix();
   glTranslatef(8.8,3.5,0.5);
   tail(0,-1.1,0,0.3,0.52);
   glPopMatrix();
   

//////POM ROSU
   glPushMatrix();
   glTranslatef(12.9,-5.2,-33.5);
   glScalef(5,5,5);
   glRotatef(angle,0,1,0);
   glRotatef(angle,0,0,1);
   check=0;
   ok=-1;
   maketree(2.8147f,0.2f);
   glPopMatrix();


//////POM GALBEN
   glPushMatrix();
   glTranslatef(-32.9,-5.2,-28.5);
   glScalef(6,6,6);
   glRotatef(angle,0,1,0);
   glRotatef(angle,0,0,1);
   check=0;
   ok=0;
   maketree(2.8147f,0.2f);
   glPopMatrix();


//////POM VERDE
   glPushMatrix();
   glTranslatef(64.9,-5.2,-28.5);
   glScalef(6,6,6);
   glRotatef(angle-45,0,1,0);
   glRotatef(angle,0,0,1);
   check=0;
   ok=1;
   maketree(2.8147f,0.2f);
   glPopMatrix();

//////SOARE/LUNA
   glPushMatrix();
   glColor3f(s, u, n);
   sun();
   glPopMatrix();

//////NORI
    glPushMatrix();
    glTranslatef(-25,25.0,-40.0);
    glScalef(0.8,1,0);
	check=0;
    clouds();
    glPopMatrix();

	glPushMatrix();
    glTranslatef(85,25.0,-40.0);
    glScalef(0.8,1,0);
	check=0;
    clouds();
    glPopMatrix();


//////UMBRE
   glPushMatrix();
   glPushAttrib(GL_LIGHTING_BIT);
   glDisable(GL_LIGHTING);

	glPushMatrix();
		glMultMatrixf((GLfloat*)matUmbra);
		check = 1;
		da=1;

		///COS
		basket();

		///POM ROSU
		glPushMatrix();
		glTranslatef(12.9,-5.2,-33.5);
		glScalef(3,3,3);
		maketree(2.8147f,0.2f);
		glPopMatrix();

		///POM GALBEN
		glPushMatrix();
        glTranslatef(-32.9,-5.2,-28.5);
        glScalef(3,3,3);
		maketree(2.8147f,0.2f);
		glPopMatrix();

		///POM VERDE
		glPushMatrix();
        glTranslatef(64.9,-5.2,-28.5);
        glScalef(3,3,3);
		maketree(2.8147f,0.2f);
		glPopMatrix();

		///PERSONAJUL KYLE
		glPushMatrix();
		glTranslatef(xr,-1.0,10);
		glScalef(5,5,5);
		doll();
		glPopMatrix();


	glPopMatrix();

	glPopAttrib();
	glPopMatrix();

glEnable(GL_LIGHTING);



//////IARBA 
   glPushMatrix();
   floor();
   glPopMatrix();

   ///DOAR IARBA NU ARE ILUMINARE
   glEnable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);

   glPopMatrix();

   glPopMatrix();
                                 
   glutSwapBuffers();                             
}

} 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///TEXTURI
void incarca_textura(const char* s)
{   
	AUX_RGBImageRec *pImagineTextura = auxDIBImageLoad(s);

    if(pImagineTextura != NULL )
	{
        glGenTextures( 1, &IDtextura );

		glBindTexture(GL_TEXTURE_2D, IDtextura);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, pImagineTextura->sizeX, pImagineTextura->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, pImagineTextura->data);
	}

	if(pImagineTextura)
	{
		if(pImagineTextura->data )
			free(pImagineTextura->data );

		free(pImagineTextura);
	}

}


///INITIALIZARI
void SetupRend()
{
   ///ILUMINAREA
   glEnable(GL_DEPTH_TEST);         
   glEnable(GL_LIGHTING);             
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);                   
   glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
   glMaterialfv(GL_FRONT,GL_SPECULAR,SpecRef);
   glMateriali(GL_FRONT,GL_SHININESS,Shine);
   glLightfv(GL_LIGHT0,GL_AMBIENT,AmbientLight);
   glLightfv(GL_LIGHT0,GL_DIFFUSE,DiffuseLight);
   glLightfv(GL_LIGHT0,GL_SPECULAR,SpecularLight);


   ///MAPAREA
   glEnable(GL_MAP2_VERTEX_3); 
   glEnable(GL_AUTO_NORMAL);
   glEnable(GL_NORMALIZE); 
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	
}


///SAGETILE DE LA TASTATURA
void walk(int key,int x,int y)                                     
{
    if(key==GLUT_KEY_UP)    walkY+=1;
    if(key==GLUT_KEY_DOWN)  walkY-=1;
    if(key==GLUT_KEY_RIGHT) walkX-=1;
    if(key==GLUT_KEY_LEFT)  walkX+=1;  
}


 ///SCHIMBARE FUNDAL + TASTA ESC + MUTARE STANGA(a) SI DREAPTA(d) A PERSONAJULUI
void keyboard ( unsigned char key, int x, int y ) 
{
	GLfloat colors[][3] = { {0.0f, 0.0f, 0.0f }, { 0.0f,  0.498039f, 1.0f}  };
    static int back;


    switch ( key ) {
    case 27:
       exit ( 0 ); 
       break;
    case 32:view=1;
             Display();
               break;
	case 'a':xr=xr-10;
		      doll();
			  glutPostRedisplay();
		     break;
	case 'd':xr=xr+10;
		     doll();
			 glutPostRedisplay();
		     break;
 
    ///schimbare fundal din taste
    //default: 
	   //back ^= 1;
    //   glClearColor(colors[back][0], colors[back][1], colors[back][2], 1.0f);
    //   glutPostRedisplay();

                    }
}


///FLUIDITATEA MOUSE-ULUI
void gaze(int x,int y)
{
    if((oldX<0) || (oldY<0))
	{
      oldX=x;
	  oldY=y;
	}
    lookX+=y-oldY;
	lookY+=x-oldX;
	oldX=x;
	oldY=y;
}


///MENIU FUNDAL+CEATA
void myMenu(int id)
{
       if(id==1)
	{
    glClearColor(0.0,  0.498039, 1.0,0);
	glDisable(GL_FOG);
	PlaySound("getoutside.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	s=1;u=0.9;n=0;
	glutPostRedisplay();
	}

	   if(id==2)
	{
	flag2=2;
	glClearColor( 0.184314,  0.184314,  0.309804,0);
	GLfloat fogcolour[4]={0.0,0.0,0.0,1.0};
    glFogfv(GL_FOG_COLOR,fogcolour);              
    glFogf(GL_FOG_DENSITY,0.02);                   
    glFogi(GL_FOG_MODE,GL_EXP);                  
    glHint(GL_FOG_HINT, GL_FASTEST);             
    glEnable(GL_FOG);
	PlaySound("fearofthedark.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	s=1;u=1;n=1;
    glutPostRedisplay();
    }
}


///SUBMENIU CULORI
void colorMenu(int id)
{
	if(id==4)
	{
		r=1;
		g=b=0;
	    glutPostRedisplay();

	}
	if(id ==5)
	{
		r=0.85;
		g=0.71;
		b=0.10;
		glutPostRedisplay();
	}
	if(id==6)
	{
		r=0.419608;
	    g=0.556863;
		b=0.137255;
		glutPostRedisplay();
	}
		if(id==7)
	{
		r=0;
	    g=0;
		b=0;
		glutPostRedisplay();
	}
	
}


///MAIN-UL
void main(int argc, char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	//glutInitWindowSize(800,600);
	glutInitWindowSize(Xsize,Ysize);
    glutCreateWindow("Apples");
	if (fullscreen) glutFullScreen();
	PlaySound("getoutside.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	int submenu=glutCreateMenu(colorMenu);
	glutAddMenuEntry("Rosu", 4);
	glutAddMenuEntry("Galben", 5);
	glutAddMenuEntry("Verde",6);
	glutAddMenuEntry("MARUL METALISTILOR",7);
	glutCreateMenu(myMenu);
	glutAddMenuEntry("Ziua",1);
	glutAddMenuEntry("Noaptea",2);
	glutAddSubMenu("Culori mar",submenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutReshapeFunc(myReshape);
	glutKeyboardFunc(keyboard);
    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutSpecialFunc(walk);
    glutPassiveMotionFunc(gaze);
    SetupRend();
    glEnable(GL_NORMALIZE);
    glutMainLoop();
}
