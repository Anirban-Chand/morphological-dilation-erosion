#include <bits/stdc++.h>
using namespace std;

// My own defines
#define ll long long
#define MAF cout << "Sorry, Memory Allocation Failed. Cannot Process Further.\n";
#define FAF                               \
    cerr << "Couldn\'t open the file.\n"; \
    exit(1);
#define FUP cout << "Files Are Under Processing...\n";

int BACKGROUND = 0;
int FOREGROUND = 1;

// Structure for an input binary image
typedef struct Input_Binary_Image
{
    /* NOTE -->  Height, Width, Maximum Pixel Value and Magic No. of the Image  */
    int height;
    int width;
    char magicNo[2];
    int **pixel;

} binImg;

void get_put_details(binImg *img, FILE *in, FILE *out)
{
    fgets(img->magicNo, 3, in); // reads from input file
    fscanf(in, "\n");           // reads the newline character
    fputs(img->magicNo, out);   // 'P1' is the Magic No for a outary Image
    fputs("\n", out);           // writes the newline character

    fscanf(in, "%d %d", &img->width, &img->height); // reads
    fscanf(in, "\n");                               // reads the newline character
    printf("Image Resolution(W x H): %d x %d\n", img->width, img->height);
    fprintf(out, "%d %d", img->width, img->height); // writes
    fprintf(out, "\n");                             // writes the newline character
}

void export_image(binImg *img, FILE *out)
{
    if (!img)
    {
        printf("No Image File...\n");
        exit(0);
    }
    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            fprintf(out, "%d ", img->pixel[i][j]);
        }
        fprintf(out, "\n");
    }

    printf("Output file is ready...");
}

// Morphological Dilation function
binImg *dilation(binImg *img)
{
    int seh, sew;
    cout << "Height and Width of SE for dilation: ";
    cin >> seh >> sew;

    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            int kernel[seh][sew];
            for (int k = 0; k < seh; k++)
            {
                for (int l = 0; l < sew; l++)
                {
                    kernel[k][l] = 1;
                }
            }
            if (((i + seh) < img->height) && ((j + sew) < img->width))
            {
                for (int k = 0; k < seh; k++)
                {
                    for (int l = 0; l < sew; l++)
                    {
                        if (img->pixel[i + k][j + l] == kernel[k][l])
                        {
                            img->pixel[i + (seh / 2)][j + (sew / 2)] = FOREGROUND;
                            break;
                        }
                        else
                            img->pixel[i + (seh / 2)][j + (sew / 2)] = BACKGROUND;
                    }
                }
            }
        }
    }
    cout << "Dilation Successful with SE " << sew << "X" << seh << endl;
    return img;
}

int main(int argc, char *argv[])
{
    FILE *fin = NULL, *fout = NULL;
    fin = fopen(argv[1], "rb");
    fout = fopen(argv[2], "w");

    if (fin && fout)
    {
        FUP;
    }
    else
    {
        FAF;
    }

    /* Creating an image structure from the input image to access data more conviniently */
    binImg *img = (binImg *)malloc(sizeof(binImg));
    get_put_details(img, fin, fout);
    img->pixel = NULL;
    img->pixel = (int **)malloc(img->height * sizeof(int *));

    if (!img->pixel)
    {
        MAF;
    }

    for (int i = 0; i < img->height; i++)
    {
        img->pixel[i] = (int *)malloc(img->width * sizeof(int));
        for (int j = 0; j < img->width; j++)
        {
            int x;
            fscanf(fin, "%d", &x);
            fscanf(fin, "\n");
            img->pixel[i][j] = x;
            if (feof(fin))
                break;
        }
    }

    img = dilation(img);
    export_image(img, fout); // Exports image to the o/p file

    fclose(fin);
    fclose(fout);
    return 0;
}