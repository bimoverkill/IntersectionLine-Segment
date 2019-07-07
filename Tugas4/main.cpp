#include <iostream>
#include <vector>
#include <sstream>
#include <glut.h>

typedef struct {
	GLfloat x;
	GLfloat y;
} coordinate;

typedef struct {
	coordinate a, b;
} line;

std::stringstream print_data;
std::vector<coordinate> clickpoints;
std::vector<line> line_data;

coordinate calc_intersection(line ab, line cd) {
	float x1ab = ab.a.x;
	float y1ab = ab.a.y;
	float x2ab = ab.b.x;
	float y2ab = ab.b.y;

	float mab = (y2ab - y1ab) / (x2ab - x1ab);
	float cab = y1ab - (mab * x1ab);

	float x1cd = cd.a.x;
	float y1cd = cd.a.y;
	float x2cd = cd.b.x;
	float y2cd = cd.b.y;

	float mcd = (y2cd - y1cd) / (x2cd - x1cd);
	float ccd = y1cd - (mcd * x1cd);
	
	//Intersection
	float x = (ccd - cab) / (mab - mcd);
	float y = (mab * x) + cab;

	return coordinate{ x, y };
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5);

	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	for (int i = 0; i < clickpoints.size(); i++) {
		glVertex2f(clickpoints.at(i).x, clickpoints.at(i).y);
	}
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	for (int i = 0; i < line_data.size(); i++) {
		glVertex2f(line_data.at(i).a.x, line_data.at(i).a.y);
		glVertex2f(line_data.at(i).b.x, line_data.at(i).b.y);
	}
	glEnd();

	glColor3f(0, 1, 1);
	glBegin(GL_LINES);
	for (int i = 0; i < line_data.size(); i++) {
		glVertex2f(line_data.at(i).a.x, line_data.at(i).a.y);
		glVertex2f(line_data.at(i).b.x, line_data.at(i).b.y);
	}
	glEnd();

	for (int i = 0; i < line_data.size(); i++) {
		for (int j = 0; j < line_data.size(); j++) {
			if (j != i) {
				coordinate intersection = calc_intersection(line_data.at(i), line_data.at(j));
				glColor3f(1, 1, 1);
				glBegin(GL_POINTS);
				glVertex2f(intersection.x, intersection.y);
				glEnd();
			}
		}
	}
	glFlush();
}

void myMouse(int button, int state, int x, int y) {
	print_data << "Mouse Coodinate : " << button << " " << state;
	print_data << " | X: " << x << " | Y: " << y << std::endl;
	std::cout << print_data.str();
	print_data = std::stringstream();

		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			coordinate mocoor;
			mocoor.x = x;
			mocoor.y = y;
			clickpoints.push_back(mocoor);

			if (clickpoints.size() >= 2) {
				line_data.push_back(
					line{
						coordinate{clickpoints.at(0).x, clickpoints.at(0).y},
						coordinate{clickpoints.at(1).x, clickpoints.at(1).y}
					}
				);
				clickpoints.clear();
			}
		}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(480, 480);
	glutCreateWindow("Sambungin point satu dengan yg lain, yuk! | 672017288");

	glutMouseFunc(myMouse);
	gluOrtho2D(0, 480, 480, 0);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}