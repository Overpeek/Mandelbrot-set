#version 400 core

in vec2 fragPos;

uniform dvec2 unif_offset;
uniform dvec2 unif_complex;
uniform double unif_zoom;
uniform int unif_iterations;

uniform sampler1D unif_tex;

#define MANDELBROT false
#define MULTIPOWER true
#define POWER 10

#define COMPLEX_REAL -0.8
#define COMPLEX_IMAGINARY 0.156

#define M_PI 3.1415926535897932384626433832795

int mandelbrot(double x, double y, int maximum) {
    int iteration = 0;
  
    double zx = x; 
	double zy = y; 
	double xtemp;

    while (zx*zx + zy*zy <= 4.0 && iteration <= maximum) {
		if (MANDELBROT) {
			if (MULTIPOWER) {
				xtemp = pow(float(zx)*float(zx) + float(zy)*float(zy), POWER / 2.0) * cos(POWER * atan(float(zy), float(zx))) + x;
				zy = pow(float(zx)*float(zx) + float(zy)*float(zy), POWER / 2.0) * sin(POWER * atan(float(zy), float(zx))) + y;
				zx=xtemp;
			} else {
				xtemp = zx*zx - zy*zy + x;
				zy = 2*zx*zy + y; 
				zx = xtemp;
			}
		} else {
			if (MULTIPOWER) {
				xtemp = pow(float(zx)*float(zx) + float(zy)*float(zy), POWER / 2.0) * cos(POWER * atan(float(zy), float(zx))) + unif_complex.x;
				zy = pow(float(zx)*float(zx) + float(zy)*float(zy), POWER / 2.0) * sin(POWER * atan(float(zy), float(zx))) - unif_complex.y;
				zx=xtemp;
			} else {
				xtemp = zx*zx - zy*zy + unif_complex.x;
				zy = 2*zx*zy - unif_complex.y; 
				zx = xtemp;
			}
		}
		
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

vec4 getColorLine(int n, float maximum) {
	if (n < maximum && n > 0) {
		float i = sin(n / maximum);
		return texture(unif_tex, i);
	} else return vec4(0.0);
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
	gl_FragColor = getColorLine(value, maximum);
}