// SimCity.cpp : Defines the entry point for the console application.
//

#include "main.h"

using namespace std;

System_Information info;
int winWidth, winHeight, state, sim_pos, curr_start;
vector<string> filenames;
button home;
button quit;
button all_events;
button event_info;
button queues;
button servers;
button next_events;
button stats;
button next;
button prev;
button back;
button start;
button cont;
arrow up;
arrow down;
button generate_report;

void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	draw_display(state);

	/* swap back buffer to front buffer */
	glutSwapBuffers();
}

/* 
* Resize the display and ensure that 
* the coordinate system is changed 
*/
void reshape(int w, int h)
{
	winWidth = w, winHeight = h;

	glViewport(0, 0, GLsizei(winWidth), GLsizei(winHeight));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (int)winWidth, 0, (int)winHeight);
	button_setup(); /* make sure the button positions are adjusted */
	glutPostRedisplay(); /* redraw with the new window */
}

void mouse(int button, int state, int x, int y) 
{
	// if the button is pressed down, then see 
	// where the mouse clicked to determine if
	// we should proceed
	y = winHeight - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		select(x, y);
	}

	glutPostRedisplay();
}

void hover(int x, int y)
{
	y = winHeight - y;
	check_mouse_pos(x, y);
	glutPostRedisplay();
}

int main(int argc, char** argv) 
{
	/* Can change this to allow multiple files to be provided */
	if (argc != 2) 
	{
		printf("Please provide one file to the program.\n");
		exit(1);
	}

	/*  add all filenames to the list */
	for (int i = 1; i < argc; i++)
		filenames.push_back((string)argv[i]);

	/* make space for event orders */
	info.event_order = (int *)malloc(sizeof(int) * 3);

	//string filename = (string)argv[1];
	readFile(filenames.at(0), &info);

	simulateDES(&info);

	winHeight = 600;
	winWidth = 800;
	state = INITIAL; /* initialize the state */
	sim_pos = 0;
	curr_start = 0;
	button_setup();
	set_colors();

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	/* these calls must be made before creating the window*/
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("DES Tool");
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(hover);
	glutMainLoop();
	system("pause");

	return 0;
}
