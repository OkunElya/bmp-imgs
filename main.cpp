
#include <fstream>
#include <iostream>
#include <bitset>
#include<vector>
#include <random>
#include <math.h>>
int main()
{

	struct S {
		char d[3];
	};
	int height = 256;
	int width = 256;
	std::uint32_t size =   (height * width * 4);
	std::vector<std::vector<S>> data;
	for (int i = 0; i < height;i++) {
		std::vector<S> buf;
		for (int j = 0; j < width; j++) {
			struct S s;
			s.d[2] = (((height-i)*2)+(50*i))/height;
			s.d[1] = rand();
			s.d[0] = (i+j)/128;	
			buf.push_back(s);
		}
		data.push_back(buf);
	}

	srand(time(NULL));
	for (int c = 0; c < 10; c++) {
		int i = (rand() ) / (65535 / (height));
		int j = (rand() ) / (65535 / (width ));
		
		//draw funy rectangle
		for (int i1 = i; i1 < std::min(height, i + 16); i1++) {
			std::vector<S> buf;
			for (int j1 = j; j1 < std::min(width, j + 16); j1++) {
				struct S s;
				s.d[2] = 128;
				s.d[1] = rand()/6553;
				s.d[0] = 128;
				data[i1][j1] = s;
			}
		}
		
	}

	auto file = std::ofstream("./img.bmp", std::ios_base::binary | std::ios_base::out);
	std::uint32_t buf;
	buf = 0x4D42;
	file.write(reinterpret_cast<char*>(&buf), 2);//id field
	buf = 0x00000046;
	file.write(reinterpret_cast<char*>(&buf), 4);//size of bmp
	buf = 0;
	file.write(reinterpret_cast<char*>(&buf), 4);//unused
	buf = 54;
	file.write(reinterpret_cast<char*>(&buf),4);//offset to data
	buf = 40;
	file.write(reinterpret_cast<char*>(&buf), 4);//size of the header from this point

	file.write(reinterpret_cast<char*>(&width), 4);//width
	file.write(reinterpret_cast<char*>(&height), 4);//height
	
	buf = 0x0001;
	file.write(reinterpret_cast<char*>(&buf), 2);//color panes count
	buf = 0x0018;
	file.write(reinterpret_cast<char*>(&buf), 2);//bps
	buf = 0;
	file.write(reinterpret_cast<char*>(&buf), 4);//use compresion
	file.write(reinterpret_cast<char*>(&size), 4);// bitmap data size
	buf = 0x000001;
	file.write(reinterpret_cast<char*>(&buf), 4);//print res x
	file.write(reinterpret_cast<char*>(&buf), 4);//print res y

	buf = 0;
	file.write(reinterpret_cast<char*>(&buf), 4);//palete color count
	file.write(reinterpret_cast<char*>(&buf), 4);//important colors count

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			file.write(data[i][j].d, 3);
		}
		file.write(reinterpret_cast<char*>(&buf), ((width*3)%4));//padding
	}
	file.close();
}
