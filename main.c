#include <GL/glut.h>
#include <stdio.h>

int ball1_center[3] = {-2,-2,0};
int ball5_center[3]= {2,-2,0};
int rotate_vector[3] = {0,0,0};
float view[3] = {0,0,1};
int rotate_angle = 0;
int rotate_angle2 = 0;
int is_active_left = 0;
int is_active_right = 1;
int flag_down = 1;
int flag_up = 0;


void iluminacao(){
    //define a posição e parâmetros da luz 0
    float position[4] = {5.0f, 5.0f, 5.0f, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    //ativando luz ambiente global
    float global_ambient[4] = {0.7f, 0.7f, 0.7f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    //ativa a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

int init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o rotate_angle de profundidade


    iluminacao();
    return 0;
}



void display(){
    //limpa o buffer
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(view[0], view[1], view[2], //posição da câmera
              0.0, 0.0, 0.0, //para onde a câmera aponta
              0.0, 1.0, 0.0); //vetor viewup
    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-10, 10, -10, 10, -10, 10);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //define material da superfície
    float kd[4] = {0.65f, 0.65f, 0.0f, 1.0f};
    float ks[4] = {0.9f, 0.9f, 0.9f, 1.0f};
    float ns = 65.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    //define que a matrix é a a model view
    GLUquadric* quad = gluNewQuadric();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LINE_SMOOTH);
    glColor3f(0.0, 0.0, 0.0);
    //linhas da esquerda
    glPushMatrix();
        glTranslatef(-1,3,-2);
        glRotatef(68,1,0,0);
        for(int i=0; i<3; i++){
            gluCylinder(quad,0.1,0.1,5,30,30);
            glTranslatef(1,0,0);
        }
    glPopMatrix();
    //linhas da direita
    glPushMatrix();
        glTranslatef(-1,3,2);
        glRotatef(68+45,1,0,0);
        for(int i=0; i<3; i++){
            gluCylinder(quad,0.1,0.1,5,30,30);
            glTranslatef(1,0,0);
        }
    glPopMatrix();
    glPushMatrix();
        //bars
        glTranslatef(-2.5,3,-2);
        glRotatef(90,0,1,0);
        gluCylinder(quad, 0.15,0.15,5,30,30);
        glTranslatef(-4,0,0);
        gluCylinder(quad, 0.15,0.15,5,30,30);
        glRotatef(-90,0,1,0);

        // support 1
        glTranslatef(0.1,0,0);
        glRotatef(-125,1,0,0);
        gluCylinder(quad, 0.15,0.15,3.5,30,30);
        glRotatef(125,1,0,0);
        glTranslatef(0,0,-4);
        gluCylinder(quad, 0.15,0.15,4,30,30);
        glRotatef(-55,1,0,0);
        gluCylinder(quad, 0.15,0.15,3.5,30,30);
        glRotatef(55,1,0,0);

        // //support 2
        glTranslatef(-0.2,0,0);
        glTranslatef(5,0,4);
        glRotatef(-125,1,0,0);
        gluCylinder(quad, 0.15,0.15,3.5,30,30);
        glRotatef(125,1,0,0);
        glTranslatef(0,0,-4);
        gluCylinder(quad, 0.15,0.15,4,30,30);
        glRotatef(-55,1,0,0);
        gluCylinder(quad, 0.15,0.15,3.5,30,30);
        glRotatef(-55,1,0,0);
    glPopMatrix();

    //ball 1
    glPushMatrix();
        glTranslatef(-2,3,-2);
        glRotatef(68,1,0,0);
        glRotatef(rotate_angle*0.9,0,1,0);
        gluCylinder(quad,0.1,0.1,5.7,30,30);   
    glPopMatrix(); 
    glPushMatrix();
        glTranslatef(-2,3,2);
        glRotatef(68+45,1,0,0);
        glRotatef(rotate_angle*0.9,0,1,0);
        gluCylinder(quad,0.1,0.1,5.7,30,30);   
    glPopMatrix(); 
    glPushMatrix();
        glTranslatef(-2.5,3,0);
        glRotatef(rotate_angle,0,0,1);
        glTranslatef(2.5,-3,0);
        glTranslatef(ball1_center[0],ball1_center[1],0);
        glutSolidSphere(0.5, 40, 40);
    glPopMatrix();
    //ball 2
    glPushMatrix();
        glTranslatef(-1,-2,0);
        glutSolidSphere(0.5, 40, 40);
    glPopMatrix();
    //ball 3
    glPushMatrix();
        glTranslatef(0,-2,0);
        glutSolidSphere(0.5, 40, 40);
    glPopMatrix();
    //ball 4
    glPushMatrix();
        glTranslatef(1,-2,0);
        glutSolidSphere(0.5, 40, 40);
    glPopMatrix();
    //ball 5
    glPushMatrix();
        glPushMatrix();
            glTranslatef(2,3,-2);
            glRotatef(68,1,0,0);
            glRotatef(rotate_angle2*0.9,0,1,0);
            gluCylinder(quad,0.1,0.1,5.7,30,30);   
        glPopMatrix(); 
        glPushMatrix();
            glTranslatef(2,3,2);
            glRotatef(68+45,1,0,0);
            glRotatef(rotate_angle2*0.9,0,1,0);
            gluCylinder(quad,0.1,0.1,5.7,30,30);   
        glPopMatrix(); 
        glTranslatef(2.5,3,0);
        glRotatef(rotate_angle2,0,0,1);
        glTranslatef(-2.5,-3,0);
        glTranslatef(ball5_center[0],ball5_center[1],0);
        glutSolidSphere(0.5, 40, 40);
    glPopMatrix();

    //força o desenho das primitivas
    glutSwapBuffers();
}

void Timer(int value){
    if(is_active_left == 0 && is_active_right == 1 && rotate_angle2 == 0){
        is_active_left = 1;
        is_active_right = 0;
    }
    else if(is_active_left == 1 && is_active_right == 0 && rotate_angle == 0){
        is_active_left = 0;
        is_active_right = 1;
    }
    if(rotate_angle2 == 35){
        flag_down = 1;
        flag_up = 0;
    }
    if(rotate_angle == -35){
        flag_down = 0;
        flag_up = 1;
    }
    if(flag_down == 0 && flag_up == 1 && is_active_left == 1){
        rotate_angle+=1;
    }
    else if(flag_down == 0 && flag_up == 1 && is_active_right == 1){
        rotate_angle2+=1;
    }
    else if( flag_down == 1 && flag_up == 0 && is_active_left == 1){
        rotate_angle -=1;
    }
    else if( flag_down == 1 && flag_up == 0 && is_active_right == 1){
        rotate_angle2 -=1;
    }
    glutPostRedisplay();
    glutTimerFunc(30, Timer, 1);
}

void keyPressed(unsigned char key, int x, int y){
    if(key == 'a'){
        if(view[0]>-2){
            view[0]-=0.08;
        }
    }
    else if(key == 'd'){
        if(view[0] < 2){
            view[0]+=0.08;
        }
    }

    else if(key == 'w'){
        if(view[1] < 2){
            view[1]+=0.08;
        }
    }

    else if(key == 's'){
        if(view[1] > -2){
            view[1]-=0.08;
        }
    }
    else if(key == 'i'){
        if(view[2] == 1){
            view[2] = 0;
        }
    }
    else if(key == 'k'){
        if(view[2] == 0){
            view[2] = 1;
        }
    }


}

int main(int argc, char** argv){
    glutInit(&argc,argv);                           //inicializa o GLUT
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);    //configura o modo de display
    glutInitWindowPosition(200,0);                  //seta a posição inicial da janela
    glutInitWindowSize(800,800);                    //configura a largura e altura da janela de exibição
    glutCreateWindow("Exemplo 4 - Propriedades da Superficie");                 //cria a janela de exibição
    glutTimerFunc(30, Timer, 1);
    init();                                         //executa função de inicialização
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutMainLoop();                                  //mostre tudo e espere
    return 0;

}
