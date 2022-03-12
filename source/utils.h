#ifndef UTILS_H
#define UTILS_H

int printe(const char* type, std::string msg, bool quit = false) {
	std::cerr << "[" << type << "]: " << msg << std::endl;

	if (quit)
		exit(1);

	return 0;
}

int changeColor(int current) {
	if (current == 2)
		return 0;
	return current + 1;
}

#endif // UTILS_H

