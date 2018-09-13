#version 400 core

in vec2 fragPos;

uniform dvec2 unif_offset;
uniform double unif_zoom;
uniform int unif_iterations;

#define COMPLEX_IMAGINARY -0.835
#define COMPLEX_REAL -0.2321

#define M_PI 3.1415926535897932384626433832795

int mandelbrot(double x, double y, int maximum) {
    int iteration = 0;
  
    double zx = x; 
	double zy = y; 
	double xtemp;

    while (zx*zx + zy*zy <= 4.0 && iteration <= maximum) {
		//JULIA SET
		//xtemp = zx*zx - zy*zy;
        //zy = 2*zx*zy + COMPLEX_IMAGINARY; 
        //zx = xtemp - COMPLEX_REAL;
		//JULIA SET
			
		//MANDELBROT SET
		xtemp = zx*zx - zy*zy;
        zy = 2*zx*zy + y; 
        zx = xtemp + x;
		//MANDELBROT SET
		
        if (zx == y && zy == y) {
            return -1;
        }

		if (zx == 0 || zy == 0) {
            return -1;
        }

		if (zx == -1 || zy == -1) {
            return -1;
        }

        iteration += 1;
    }

    if (iteration >= maximum) {
        return -1;
    } else {
        return iteration;
    }
}

vec3 getColor1(int n, float maximum) {
	if (n < maximum && n > 0) {
		int i = n % 16;
		vec3 color;
		switch (i){
			case 0:
			color = vec3(66, 30, 15);
			break;

			case 1:
			color = vec3(25, 7, 26);
			break;

			case 2:
			color = vec3(9, 1, 47);
			break;

			case 3:
			color = vec3(4, 4, 73);
			break;

			case 4:
			color = vec3(0, 7, 100);
			break;
			
			case 5:
			color = vec3(12, 44, 138);
			break;

			case 6:
			color = vec3(24, 82, 177);
			break;

			case 7:
			color = vec3(57, 125, 209);
			break;

			case 8:
			color = vec3(134, 181, 229);
			break;
			
			case 9:
			color = vec3(211, 236, 248);
			break;

			case 10:
			color = vec3(241, 233, 191);
			break;

			case 11:
			color = vec3(248, 201, 95);
			break;

			case 12:
			color = vec3(255, 170, 0);
			break;

			case 13:
			color = vec3(204, 128, 0);
			break;

			case 14:
			color = vec3(153, 87, 0);
			break;

			case 15:
			color = vec3(106, 52, 3);
			break;

			default:
			break;
		}
		return color / 255;
	} else return vec3(0.0);
}

vec3 getColor2(int n, float maximum) {
	if (n > 0) {
		int i = n % 16;
		float val = (sin((n / 16.0 * M_PI)) + 1.0) / 2.0;
		//float val2 = cos((n / 16.0 * M_PI) + M_PI / 2);
		return vec3(val, 0.0, val);
	} else return vec3(0);
}

vec3 getColor3(int n, float maximum) {
	if (n > 0) {
		int i = n % 16;
		float val = (sin((n / 16.0 * M_PI)) + 1.0) / 2.0;
		float val2 = (cos((n / 16.0 * M_PI)) + 1.0) / 2.0;
		return vec3(0.0, val, val2);
	} else return vec3(0);
}

vec3 getColor4(int n, float maximum) {
	if (n > 0) {
		int i = n % 16;
		float val = (sin((n / 16.0 * M_PI)) + 0.5) / 2.0;
		float val2 = (cos((n / 16.0 * M_PI)) + 0.5) / 2.0;
		return vec3(val, val/2, val2);
	} else return vec3(0);
}

void main() {
	int maximum = unif_iterations;
    int counter = 0;
	double startX = fragPos.x * unif_zoom + unif_offset.x;
	double startY = fragPos.y * unif_zoom + unif_offset.y;
	
	//int value = julia(startX, startY, maximum);
	int value = mandelbrot(startX, startY, maximum);
	gl_FragColor = vec4(getColor2(value, maximum), 1.0);
}