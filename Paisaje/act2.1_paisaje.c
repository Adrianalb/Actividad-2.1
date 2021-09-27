#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *image, *outputImage, *outputHist1,*outputHist2, *outputHist3, *outputHist4, *lecturas;
    image = fopen("paisaje1.bmp","rb");          //Imagen original a transformar
    outputHist1 = fopen("Histograma_Red.txt", "wb");
    outputHist2 = fopen("Histograma_Green.txt", "wb");
    outputHist3 = fopen("Histograma_B.txt", "wb");
    outputHist4 = fopen("Histograma_Grises.txt", "wb");
    outputImage = fopen("paisaje1_dd.bmp","wb");
    long ancho;
    long alto;
    unsigned char r, g, b;
    unsigned char* ptr;

    unsigned char xx[54];
    int cuenta = 0;
   for(int i=0; i<54; i++){
    xx[i] = fgetc(image);
    fputc(xx[i], outputImage);
   }
    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("Largo de la imgen: %li\n",alto);
    printf("Ancho de la imgen: %li\n",ancho);

    ptr = (unsigned char*)malloc(alto*ancho*3* sizeof(unsigned char));

    int red[256], blue[256], green[256], gris[256];

    for(int i=0; i<256; i++){
      red[i]=0;
      blue[i]=0;
      green[i]=0;
      gris[i]=0;
    }

    while(!feof(image)){
      b = fgetc(image);
      g = fgetc(image);
      r = fgetc(image);

      unsigned char pixel = 0.21*r+0.72*g+0.07*b;

      red[r]++;
      green[g]++;
      blue[b]++;
      gris[pixel]++;   

      ptr[cuenta] = pixel; //b
      ptr[cuenta+1] = pixel; //g
      ptr[cuenta+2] = pixel; //r

      cuenta++;

    }  
                                          //Grises

    cuenta = ancho;
    for (int i = 0; i < alto*ancho*3; ++i) {
      fputc(ptr[i+(cuenta*3)+2], outputImage);
      fputc(ptr[i+(cuenta*3)+1], outputImage);
      fputc(ptr[i+(cuenta*3)], outputImage);
      cuenta--;
      if (cuenta == 0){
        cuenta = ancho;
      }
    }

   
    for(int i = 0; i<=255; i++){
      fprintf(outputHist1, "%d,%d \n", i, red[i]);
      fprintf(outputHist2, "%d,%d \n", i, blue[i]);
      fprintf(outputHist3, "%d,%d \n", i, green[i]);
      fprintf(outputHist4, "%d,%d \n", i, gris[i]);
    }

    free(ptr);
    fclose(image);
    fclose(outputHist1);
    fclose(outputHist2);
    fclose(outputHist3);
    fclose(outputHist4);
    fclose(outputImage);
    return 0;
}
