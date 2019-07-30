#include <stdlib.h> ///PENTRU SUNET(SI PENTRU O EROARE DACA NU CONFIGUREZI GLUT-UL IN PROJECT->PROPERTIES)
#include <glut.h> ///INLOCUITOR PENTRU GLU SI GL                
#include <math.h> ///PENTRU CALCULE
#include <windows.h> ///PENTRU SUNET
#include <mmsystem.h> ///PENTRU SUNET
#include <glaux.h> ///PENTRU FUNCTIILE DE TEXTURARE

///VARIABILE UMBRA
int da;

////PERSONAJUL KYLE DIN SOUTH PARK

///FUNCTIE PERSONAJ

void doll()
{
    glPushMatrix();
    glTranslatef(-.17,1.1,.75);     
    glRotatef(45,0,0,1);
    glScalef(.9,.7,.7);
	   if(da == 0)
    glColor3f(1.0,1.0,1.0); 
	else glColor3f(0,0,0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();


	glPushMatrix();
    glTranslatef(.17,1.1,.75);     
    glRotatef(-45,0,0,1);
    glScalef(.9,.7,.7); 
	if(da == 0)
    glColor3f(1.0,1.0,1.0); 
	else glColor3f(0,0,0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();

	glPushMatrix();
	if(da == 0)
	glColor3ub(50,40,60);
	else glColor3f(0,0,0);
    glTranslatef(.3,-.5,0);     
    glRotatef(-90.0,1,0,0);
    glScalef(.8,.8,.8);
    gluCylinder(gluNewQuadric(),.5,.5,.5,30,6);
    glPopMatrix();


	glPushMatrix();
	if(da == 0)
	glColor3ub(50,40,60);
	else glColor3f(0,0,0);
    glTranslatef(-.3,-.5,0);     
    glRotatef(-90.0,1,0,0);
    glScalef(.8,.8,.8);
    gluCylinder(gluNewQuadric(),.5,.5,.5,30,6);
    glPopMatrix();

	glPushMatrix();
	if(da == 0)
	glColor3ub(255,90,0);
	else glColor3f(0,0,0);
    glTranslatef(-.82,0,.1);     
    glRotatef(90,0,1,0);
    glRotatef(-50,1,0,0);
    gluCylinder(gluNewQuadric(),.15,.15,.48,30,6);
    glPopMatrix();

	 glPushMatrix();
	 if(da == 0)
	glColor3ub(255,90,0);
	 else glColor3f(0,0,0);
    glTranslatef(.82,0,.1);      
    glRotatef(90,0,1,0);
    glRotatef(-130,1,0,0);
    gluCylinder(gluNewQuadric(),.15,.15,.48,30,6);
    glPopMatrix();

	glPushMatrix();
	if(da == 0)
	glColor3f(0,0.3,0);
	else glColor3f(0,0,0);
    glTranslatef(.82,0,.1);    
    glScalef(.4,.3,.3);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();

	glPushMatrix();
	if(da == 0)
	glColor3f(0,0.3,0);
	else glColor3f(0,0,0);
    glTranslatef(-.82,0,.1);    
    glScalef(.4,.3,.3);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();

	glPushMatrix();
    glTranslatef(0,.78,.74);
    glScalef(.4,.4,.1);
	if(da == 0)
    glColor3f(0.0,0.0,0.0);
	else glColor3f(0,0,0);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();

	glPushMatrix();
	if(da == 0)
    glColor3f(1.0,1.0,1.0);
	else glColor3f(0,0,0);
    glTranslatef(-.08,.72,.76);
    glTranslatef(.055,0,.005 );
    glutSolidCube(.035);
    glTranslatef(.055,0,0 );
    glutSolidCube(.035);
    glPopMatrix();

	glPushMatrix();
    glTranslatef(-.3,1.5,.97);;
    glRotatef(90,0,1,0);
    glRotatef(45,1,0,0);
	if(da == 0)
    glColor3f(0.0,0.0,0.0);
	else glColor3f(0,0,0);
    gluCylinder(gluNewQuadric(),.05,.01,.3,4,6);
    glPopMatrix();

	 glPushMatrix();
    glTranslatef(.3,1.5,.97);
    glRotatef(270,0,1,0);
    glRotatef(45,1,0,0);
	if(da == 0)
	glColor3f(0.0,0.0,0.0);
	else glColor3f(0,0,0);
    gluCylinder(gluNewQuadric(),.05,.01,.3,4,6);
    glPopMatrix();

	glPushMatrix();
	if(da == 0)
	glColor3f(0,0.3,0);
	else glColor3f(0,0,0);
    glTranslatef(0,.5,0);
    glScalef(.59,.59,.59);
    glRotatef(90.0,1,0,0);
    glutSolidTorus(.1,1.0,20,20);
    glPopMatrix();

	glPushMatrix();
    glTranslatef(0,1.2,0);
    glScalef(.9 ,.9,.9 );
	if(da == 0)
    glColor3f(1.0,0.8,0.6);
	else glColor3f(0,0,0);
    gluSphere(gluNewQuadric(),1,100,100);
    glPopMatrix();

	 glPushMatrix();
if(da == 0)
  glColor3f(0,0.3,0);
else glColor3f(0,0,0);
  glTranslatef(-0.8,1.8,0.825);
  glRotatef(90,0,1,0);
  glScalef(0.001,.03,0.08);
  glRotatef(45,0,0,1);
  gluCylinder(gluNewQuadric(),11.5,11.5,20,4,10);
  glPopMatrix();

  glPushMatrix();
  if(da == 0)
  glColor3f(0.0,1.0,0.0);
  else glColor3f(0,0,0);
  glTranslatef(-1.0,2.0,0);
  glRotatef(90,0,1,0);
  glScalef(.1,.05,.1);
  glRotatef(45,0,0,1);
  gluCylinder(gluNewQuadric(),11.5,11.5,20,4,10);
  glPopMatrix();

  glPushMatrix();
  if(da == 0)
  glColor3f(0.0,1.0,0.0);
  else glColor3f(0,0,0);
  glTranslatef(-1,2,0.82);
  glRotatef(180,1,0,0);
  glScalef(0.001,.05,0.082);
  glRotatef(45,0,0,1);
  gluCylinder(gluNewQuadric(),11.5,11.5,20,4,10);
  glPopMatrix();

  glPushMatrix();
  if(da == 0)
  glColor3f(0.0,1.0,0.0);
  else glColor3f(0,0,0);
  glTranslatef(1,2,0.82);
  glRotatef(180,1,0,0);
  glScalef(0.001,.05,0.082);
  glRotatef(45,0,0,1);
  gluCylinder(gluNewQuadric(),11.5,11.5,20,4,10);
  glPopMatrix();

  glPushMatrix();
  if(da == 0)
	glColor3f(0.0,1.0,0.0);
  else glColor3f(0,0,0);
    glTranslatef(-1,1.2,0);
	glRotatef(90.0,0,1,0);
    glScalef(0.2,0.2,0.04);
    gluSphere(gluNewQuadric(),3,20,100);
    glPopMatrix();

	 glPushMatrix();
	 if(da == 0)
	glColor3f(0.0,1.0,0.0);
	 else glColor3f(0,0,0);
    glTranslatef(1,1.2,0);
	glRotatef(90.0,0,1,0);
    glScalef(0.2,0.2,0.04);
    gluSphere(gluNewQuadric(),3,20,100);
    glPopMatrix();

	glPushMatrix();
	if(da == 0)
	glColor3f(0.0,1.0,0.0);
	else glColor3f(0,0,0);
    glTranslatef(0,2.2,0);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.18,100,100);
    glPopMatrix() ;

	glPushMatrix();
    glTranslatef(-.3,-.5,0);
    glScalef(1.5,.3,1.5);
	if(da == 0)
    glColor3f(0.0,0.0,0.0);
	 else glColor3f(0,0,0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();

	glPushMatrix();
    glTranslatef(.3,-.5,0);
    glScalef(1.5,.3,1.5);
	if(da == 0)
    glColor3f(0.0,0.0,0.0);
	else glColor3f(0,0,0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();

	 glPushMatrix();
	 if(da == 0)
	glColor3ub(255,90,0);
	 else glColor3f(0,0,0);
    glTranslatef(0,-.2,0);
    glScalef(1,.7,1);
    glRotatef(90.0,1,0,0);
    gluDisk(gluNewQuadric(),0,.8,30,30);
    glPopMatrix();

	glPushMatrix();
	if(da == 0)
	glColor3ub(255,90,0);
	else glColor3f(0,0,0);
    glTranslatef(0,.5,0);
    glScalef(1,.7,1);
    glRotatef(90.0,1,0,0);
    gluCylinder(gluNewQuadric(),.6,.8,1,100,100);
    glPopMatrix();

	   glPushMatrix();
	   if(da == 0)
	glColor3f(0.0,0.0,0.0);
	   else glColor3f(0,0,0);
    glTranslatef(-.17,1.1,.88);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.1,100,100);
    glPopMatrix();

	    glPushMatrix();
		if(da == 0)
	glColor3f(0.0,0.0,0.0);
		else glColor3f(0,0,0);
    glTranslatef(.17,1.1,.88);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.1,100,100);
    glPopMatrix();

	    glPushMatrix();
		if(da == 0)
	glColor3f(0.0,0.0,0.0);
		else glColor3f(0,0,0);
    glTranslatef(-.1,.4,.85);
    glScalef(1.9,1.9,1.9);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();

	   glPushMatrix();
	   if(da == 0)
	glColor3f(0.0,0.0,0.0);
	   else glColor3f(0,0,0);
    glTranslatef(-.1,.15,.98);
    glScalef(1.9,1.9,1.9);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();

	   glPushMatrix();
	   if(da == 0)
	glColor3f(0.0,0.0,0.0);
	   else glColor3f(0,0,0);
    glTranslatef(-.1,-.1,.92);
    glScalef(1.9,1.9,1.9);
    glColor3f(0.0,0.0,0.0);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}

///ECHIVALENT CU FUNCTIA doll

//void eyeright()
//{
//    glPushMatrix();
//    glTranslatef(.17,1.1,.75);     
//    glRotatef(-45,0,0,1);
//    glScalef(.9,.7,.7);            
//    glColor3f(1.0,1.0,1.0);      
//    gluSphere(gluNewQuadric(),.3,100,100);
//    glPopMatrix();
//}
//
//void eyeleft()
//{
//    glPushMatrix();
//    glTranslatef(-.17,1.1,.75);     
//    glRotatef(45,0,0,1);
//    glScalef(.9,.7,.7);
//    glColor3f(1.0,1.0,1.0);
//    gluSphere(gluNewQuadric(),.3,100,100);
//    glPopMatrix();
//}
//
//void legleft()
//{
//    glPushMatrix();
//	glColor3ub(50,40,60);
//    glTranslatef(.3,-.5,0);     
//    glRotatef(-90.0,1,0,0);
//    glScalef(.8,.8,.8);
//    gluCylinder(gluNewQuadric(),.5,.5,.5,30,6);
//    glPopMatrix();
//}
//
//void legright()
//{
//    glPushMatrix();
//	glColor3ub(50,40,60);
//    glTranslatef(-.3,-.5,0);     
//    glRotatef(-90.0,1,0,0);
//    glScalef(.8,.8,.8);
//    gluCylinder(gluNewQuadric(),.5,.5,.5,30,6);
//    glPopMatrix();
//}
//
//void armleft()
//{
//    glPushMatrix();
//	glColor3ub(255,90,0);
//    glTranslatef(-.82,0,.1);     
//    glRotatef(90,0,1,0);
//    glRotatef(-50,1,0,0);
//    gluCylinder(gluNewQuadric(),.15,.15,.48,30,6);
//    glPopMatrix();
//}
//
//void armright()
//{
//    glPushMatrix();
//	glColor3ub(255,90,0);
//    glTranslatef(.82,0,.1);      
//    glRotatef(90,0,1,0);
//    glRotatef(-130,1,0,0);
//    gluCylinder(gluNewQuadric(),.15,.15,.48,30,6);
//    glPopMatrix();
//}
//
//void handleft()
//{
//    glPushMatrix();
//	glColor3f(0,0.3,0);
//    glTranslatef(.82,0,.1);    
//    glScalef(.4,.3,.3);
//    gluSphere(gluNewQuadric(),.4,100,100);
//    glPopMatrix();
//}
//
//void handright()
//{
//    glPushMatrix();
//	glColor3f(0,0.3,0);
//    glTranslatef(-.82,0,.1);    
//    glScalef(.4,.3,.3);
//    gluSphere(gluNewQuadric(),.4,100,100);
//    glPopMatrix();
//}
//
//void mouth()
//{
//    glPushMatrix();
//    glTranslatef(0,.78,.74);
//    glScalef(.4,.4,.1);
//    glColor3f(0.0,0.0,0.0);
//    gluSphere(gluNewQuadric(),.4,100,100);
//    glPopMatrix();
//}
//
//void teeth()
//{
//    glPushMatrix();
//    glColor3f(1.0,1.0,1.0);
//    glTranslatef(-.08,.72,.76);
//    glTranslatef(.055,0,.005 );
//    glutSolidCube(.035);
//    glTranslatef(.055,0,0 );
//    glutSolidCube(.035);
//    glPopMatrix();
//}
//
//void eyebrowleft()
//{
//    glPushMatrix();
//    glTranslatef(-.3,1.5,.97);;
//    glRotatef(90,0,1,0);
//    glRotatef(45,1,0,0);
//    glColor3f(0.0,0.0,0.0);
//    gluCylinder(gluNewQuadric(),.05,.01,.3,4,6);
//    glPopMatrix();
//}
//
//void eyebrowright()
//{
//    glPushMatrix();
//    glTranslatef(.3,1.5,.97);
//    glRotatef(270,0,1,0);
//    glRotatef(45,1,0,0);
//    gluCylinder(gluNewQuadric(),.05,.01,.3,4,6);
//    glPopMatrix();
//}
//
//void neckring()
//{
//    glPushMatrix();
//	glColor3f(0,0.3,0);
//    glTranslatef(0,.5,0);
//    glScalef(.59,.59,.59);
//    glRotatef(90.0,1,0,0);
//    glutSolidTorus(.1,1.0,20,20);
//    glPopMatrix();
//}
//
//void head()
//{
//    glPushMatrix();
//    glTranslatef(0,1.2,0);
//    glScalef(.9 ,.9,.9 );
//    glColor3f(1.0,0.8,0.6);
//    gluSphere(gluNewQuadric(),1,100,100);
//    glPopMatrix();
//}
//
//void hatadd()
//{
//  glPushMatrix();
//  glColor3f(0,0.3,0);
//  glTranslatef(-0.8,1.8,0.825);
//  glRotatef(90,0,1,0);
//  glScalef(0.001,.03,0.08);
//  glRotatef(45,0,0,1);
//  gluCylinder(gluNewQuadric(),11.5,11.5,20,4,10);
//  glPopMatrix();
//}
//
//void hat()
//{
// 
//  glPushMatrix();
//  glColor3f(0.0,1.0,0.0);
//  glTranslatef(-1.0,2.0,0);
//  glRotatef(90,0,1,0);
//  glScalef(.1,.05,.1);
//  glRotatef(45,0,0,1);
//  gluCylinder(gluNewQuadric(),11.5,11.5,20,4,10);
//  glPopMatrix();
//}
//
//void hatLside()
//{
//  glPushMatrix();
//  glColor3f(0.0,1.0,0.0);
//  glTranslatef(-1,2,0.82);
//  glRotatef(180,1,0,0);
//  glScalef(0.001,.05,0.082);
//  glRotatef(45,0,0,1);
//  gluCylinder(gluNewQuadric(),11.5,11.5,20,4,10);
//  glPopMatrix();
//}
//
//void hatRside()
//{
//  glPushMatrix();
//  glColor3f(0.0,1.0,0.0);
//  glTranslatef(1,2,0.82);
//  glRotatef(180,1,0,0);
//  glScalef(0.001,.05,0.082);
//  glRotatef(45,0,0,1);
//  gluCylinder(gluNewQuadric(),11.5,11.5,20,4,10);
//  glPopMatrix();
//}
//
//void earleft()
//{
//    glPushMatrix();
//	glColor3f(0.0,1.0,0.0);
//    glTranslatef(-1,1.2,0);
//	glRotatef(90.0,0,1,0);
//    glScalef(0.2,0.2,0.04);
//    gluSphere(gluNewQuadric(),3,20,100);
//    glPopMatrix();
//}
//
//void earright()
//{
//    glPushMatrix();
//	glColor3f(0.0,1.0,0.0);
//    glTranslatef(1,1.2,0);
//	glRotatef(90.0,0,1,0);
//    glScalef(0.2,0.2,0.04);
//    gluSphere(gluNewQuadric(),3,20,100);
//    glPopMatrix();
//}
//
//void maintopball()
//{
//    glPushMatrix();
//    glTranslatef(0,2.2,0);
//    glScalef(.9,.9,.9);
//    gluSphere(gluNewQuadric(),.18,100,100);
//    glPopMatrix() ;
//}
//
//void footleft()
//{
//    glPushMatrix();
//    glTranslatef(-.3,-.5,0);
//    glScalef(1.5,.3,1.5);
//    glColor3f(0.0,0.0,0.0);
//    gluSphere(gluNewQuadric(),.3,100,100);
//    glPopMatrix();
//}
//
//void footright()
//{
//    glPushMatrix();
//    glTranslatef(.3,-.5,0);
//    glScalef(1.5,.3,1.5);
//    glColor3f(0.0,0.0,0.0);
//    gluSphere(gluNewQuadric(),.3,100,100);
//    glPopMatrix();
//}
//
//void bellyCoatbottom()
//{
//    glPushMatrix();
//	glColor3ub(255,90,0);
//    glTranslatef(0,-.2,0);
//    glScalef(1,.7,1);
//    glRotatef(90.0,1,0,0);
//    gluDisk(gluNewQuadric(),0,.8,30,30);
//    glPopMatrix();
//}
//
//void BellyCoat()
//{
//    glPushMatrix();
//	glColor3ub(255,90,0);
//    glTranslatef(0,.5,0);
//    glScalef(1,.7,1);
//    glRotatef(90.0,1,0,0);
//    gluCylinder(gluNewQuadric(),.6,.8,1,100,100);
//    glPopMatrix();
//}
//
//void pupilleft()
//{
//    glPushMatrix();
//	glColor3f(0.0,0.0,0.0);
//    glTranslatef(-.17,1.1,.88);
//    glScalef(.9,.9,.9);
//    gluSphere(gluNewQuadric(),.1,100,100);
//    glPopMatrix();
//}
//
//void pupilright()
//{
//    glPushMatrix();
//	glColor3f(0.0,0.0,0.0);
//    glTranslatef(.17,1.1,.88);
//    glScalef(.9,.9,.9);
//    gluSphere(gluNewQuadric(),.1,100,100);
//    glPopMatrix();
//}
//
//void topbutton()
//{
//    glPushMatrix();
//	glColor3f(0.0,0.0,0.0);
//    glTranslatef(-.1,.4,.85);
//    glScalef(1.9,1.9,1.9);
//    gluSphere(gluNewQuadric(),.04,100,100);
//    glPopMatrix();
//}
//
//void middlebutton()
//{
//    glPushMatrix();
//	glColor3f(0.0,0.0,0.0);
//    glTranslatef(-.1,.15,.98);
//    glScalef(1.9,1.9,1.9);
//    gluSphere(gluNewQuadric(),.04,100,100);
//    glPopMatrix();
//}
//
//void bottombutton()
//{
//    glPushMatrix();
//	glColor3f(0.0,0.0,0.0);
//    glTranslatef(-.1,-.1,.92);
//    glScalef(1.9,1.9,1.9);
//    glColor3f(0.0,0.0,0.0);
//    gluSphere(gluNewQuadric(),.04,100,100);
//    glPopMatrix();
//}