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

// Normal utility function for exporting the updated image file in the output file
void export_image(binImg *img, FILE *out)
{
    if (!img)
    {
        printf("No Image File...\n");
        exit(0);
    }
    // printing pixel by pixel in the o/p file
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

/*  Morphological Dilation Operation:
        1. One of the basic mathematical morphological operation. 
        2. This operation expands the objects contained in the input image.
        3. Works along the edges of the objects. 
    How it works:
        To compute the dilation of a binary input image by this structuring element, we consider each of the background pixels in the input image in turn. For each background pixel (which we will call the input pixel) we superimpose the structuring element on top of the input image so that the origin of the structuring element coincides with the input pixel position. If at least one pixel in the structuring element coincides with a foreground pixel in the image underneath, then the input pixel is set to the foreground value. If all the corresponding pixels in the image are background, however, the input pixel is left at the background value.*/
binImg *dilation(binImg *img)
{
    /*
        seh - height of the structuring element
        sew - width of the structuring element
    */
    int seh, sew;
    cout << "Height and Width of SE for dilation: ";
    cin >> seh >> sew;

    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            // Structuring Element -> 2D array with the i/p size, are often called kernel.
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



/*  Morphological Erosion Function:
        1. The other basic mathematical morphological operation. 
        2. This operation shrinks the objects contained in the input image.
        3. Works along the edges of the objects. 
    How it works:
        To compute the erosion of a binary input image by this structuring element, we consider each of the foreground pixels in the input image in turn. For each foreground pixel (which we will call the input pixel) we superimpose the structuring element on top of the input image so that the origin of the structuring element coincides with the input pixel coordinates. If for every pixel in the structuring element, the corresponding pixel in the image underneath is a foreground pixel, then the input pixel is left as it is. If any of the corresponding pixels in the image are background, however, the input pixel is also set to background value.*/
binImg *erosion(binImg *img)
{
    int seh, sew;
    printf("Height and Width of SE for erosion: ");
    scanf("%d %d", &seh, &sew);

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
                        if (img->pixel[i + k][j + l] != kernel[k][l])
                        {
                            img->pixel[i + seh / 2][j + sew / 2] = BACKGROUND;
                            break;
                        }
                        else
                            img->pixel[i + seh / 2][j + sew / 2] = FOREGROUND;
                    }
                }
            }
        }
    }
    printf("Erosion Successful with SE %dX%d\n", sew, seh);
    return img;
}

/* Morphological Opening Function: 
        It is a composed morphological operation of erosion followed by dilation. Opening is mainly done with the same sized SE.*/
binImg *opening(binImg *img)
{
    img = erosion(img);
    img = dilation(img);
    return img;
}

/* Morphological Closing Function: 
        It is a composed morphological operation of dilation followed by erosion. Closing is mainly done with the same sized SE.*/
binImg *closing(binImg *img)
{
    img = dilation(img);
    img = erosion(img);
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

    img = opening(img);
    // img = closing(img);
    export_image(img, fout); // Exports image to the o/p file

    fclose(fin);
    fclose(fout);
    return 0;
}