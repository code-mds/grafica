
//using namespace std;

class ip_bmp_file {
public:

    static long int WidthHeight(int pix1, int pix2) {
        long int num = 0, n = 8, rem;
        do {   //high byte only
            rem = pix2 % 2;
            num = num + rem * pow(2, n);
            pix2 = pix2 / 2;
            n++;
        } while (n <= 16);
        num = num + pix1;
        return (num);
    }

    static void header_data() {
        unsigned char pixel;
        char filename[255];
        int i, j, x, pixlow, pixhigh, pix3, pix4;

        std::cout << "Picture file name: ";
        std::cin >> filename;
        std::ifstream inpaint(filename, std::ios::binary);
        if (!inpaint) {
            std::cout << "File not opened / found\n";
            exit(1);
        }
        for (x = 1; x <= 54; x++) {
            inpaint >> pixel; //go to start of data after header stuff
            if (x == 19) pixlow = pixel; //low
            if (x == 20) pixhigh = pixel; //high
            if (x == 23) pix3 = pixel; //low
            if (x == 24) pix4 = pixel; //high
        }
        ww = WidthHeight(pixlow, pixhigh);
        wh = WidthHeight(pix3, pix4);
        std::cout << "\nx width = " << ww << "y height = " << wh << std::endl;

        for (i = 0; i < wh; i++) {
            for (j = 0; j < ww; j++) {
                pixel= inpaint.get();
                Image[i][j][2] = pixel;
                pixel = inpaint.get();
                Image[i][j][1] = pixel;
                pixel = inpaint.get();
                Image[i][j][0] = pixel;
                Image[i][j][3] = (GLubyte) 255;
            }
        }
    }
};