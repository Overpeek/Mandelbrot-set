#version 400 core

in vec2 fragPos;

uniform dvec2 unif_offset;
uniform double unif_zoom;
uniform int unif_iterations;
uniform int rendering_mandelbrot = 1;

uniform sampler1D unif_colorArray;

#define COMPLEX_IMAGINARY -0.835
#define COMPLEX_REAL -0.2321

#define M_PI 3.1415926535897932384626433832795

int mandelbrot(double x, double y, int maximum) {
	int iteration = 0; double zx = x; double zy = y;

	//Mandelbrot
    while (zx*zx + zy*zy <= 4.0 && iteration <= maximum) {
        double ytemp = 2*zx*zy + y; 
		zx = zx*zx - zy*zy + x;
        zy = ytemp;
        if (zx == y && zy == y) return -1;
        iteration += 1;
    }
    if (iteration >= maximum) return -1;
	else return iteration;
}

int juliaSet(double x, double y, int maximum) {
	int iteration = 0; double zx = x; double zy = y;

	//Mandelbrot
    while (zx*zx + zy*zy <= 4.0 && iteration <= maximum) {
        double ytemp = 2*zx*zy + unif_offset.y; 
		zx = zx*zx - zy*zy + unif_offset.x;
        zy = ytemp;
        if (zx == y && zy == y) return -1;
        iteration += 1;
    }
    if (iteration >= maximum) return -1;
	else return iteration;
}

vec4 getColor(int n, float maximum) {
	if (n > 0) {
		float val = 1.0f - (n / maximum);
		//val = pow(val, 4);

		//if (val < 0.3) val = 0.0;

		//return vec4(val, val, val, 1.0);
		return vec4(val, val / 2.0, 0.0, 1.0);
	}
	else return vec4(0.0, 0.0, 0.0, 1.0);
}

vec4 getColorLine(int n, float maximum) {
    int speed = 512;
	if (n > 0) {
		float val = sin(n / maximum);
		//float val = (n % speed) / float(speed);
		return texture(unif_colorArray, val);
	} else return vec4(0.0, 0.0, 0.0, 1.0);
}

void main() {
	int maximum = unif_iterations;
    int counter = 0;
	
	int value = 0;
	double offset = 1.0;
	if (rendering_mandelbrot == 1) {
		double startX = (fragPos.x - offset) * unif_zoom + unif_offset.x;
		double startY = (fragPos.y) * unif_zoom + unif_offset.y;
		
		double dotSize = 0.05;

		double d_x = abs(fragPos.x - 1.0);
		double d_y = abs(fragPos.y);

		if (d_x < dotSize && d_y < dotSize) {
			double distance = sqrt(d_x*d_x + d_y*d_y);
			if (distance >= dotSize * 0.95 && distance <= dotSize * 1.05) {
				gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
				return;
			}
		}

		value = mandelbrot(startX, startY, maximum);
	}
	else {
		double startX = (fragPos.x + offset) * 2.0;
		double startY = (fragPos.y) * 2.0;
		
		value = juliaSet(startX, startY, maximum);
	}
	gl_FragColor = getColorLine(value, maximum);
}