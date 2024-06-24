//----------------------------------------------------------------------------//
// Template for reading portable gray map files (*.pgm)                       //
//                                                                            //
//                                                March 06, 2023           //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//         Prototype declarations                                             //
//----------------------------------------------------------------------------//

void heading (void);      /* Displays program heading */
void openfiles (void);    /* Opens input and output files in binary */
void userdefined (void);  /* Here, the user will implement his routine */
void readhdr (void);      /* Read header from input image file */
void addhdr (void);       /* Add header to output image file */
void closefiles (void);   /* Close all files used in program */

//----------------------------------------------------------------------------//
//         Include declarations                                               //
//----------------------------------------------------------------------------//

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>

//----------------------------------------------------------------------------//
//         Variable declarations                                              //
//----------------------------------------------------------------------------//

int    MRows, NCols;                 /* Number of Rows and columns in image */
FILE   *infptr, *outfptr, *outfptrh; /* Input and output file pointers */
char   infile[40];                   /* Name of input file */
char   outfile[40];                  /* Name of output file */

//----------------------------------------------------------------------------//
//         Main program                                                       //
//----------------------------------------------------------------------------//

main ()
{
     // Display heading
     heading ();
     // Open Input and Output Image Files
     openfiles ();
     // Read header from image file
     readhdr();
     // Add header to output file
     addhdr();
     // Execute userdefined procedure
     userdefined ();
     // Close all image files
     closefiles ();
     
     printf("\n Bye! Bye!\n");
     system("PAUSE");
     return(1);
} // end main ();

//----------------------------------------------------------------------------//
//         Headings                                                           //
//----------------------------------------------------------------------------//

void heading ()
{
     int i;
     for (i=0; i<16; i++)
       printf("                                    +                       \n");
       printf("                      Digital Image Processing in C         \n");
       printf("                         Date: Agosto 28, 2023             \n");
       printf("                            Author: Braian                   \n");
     for (i=0; i<3; i++)
       printf("                                    +                       \n");
       return;
} // end heading ()

//----------------------------------------------------------------------------//
//         Openfiles                                                          //
//----------------------------------------------------------------------------//

void openfiles ()
{
     printf("\n Opening Input and Output image files\n");
     printf(" Enter name of *.ppm INPUT image file (example: lena.ppm) ");
     scanf("%s",&infile);
     
     //Check if input file exists
     if ((infptr = fopen(infile, "rb")) == NULL)
     {
       printf(" Cannot open input image file: %s\n",infile);
       printf(" Exiting program...\n");
       system("PAUSE");
       exit(1);
       }
     
     printf(" Enter name of *.pgm OUTPUT image file (example: lenaout.pgm) ");
     scanf("%s",&outfile);
     
     //Check if output file was created succesfully
     if ((outfptr = fopen(outfile, "wb")) == NULL)
     {
       printf(" Cannot create output image file: %s\n",outfile);
       printf(" Exiting program...\n");
       system("PAUSE");
       exit(1);
       }
       
     // If this point is reached, file are OK
     printf(" File opened and created OK! \n\n");
     
}  //end openfiles ()

//----------------------------------------------------------------------------//
//         Read Header                                                        //
//----------------------------------------------------------------------------//

void readhdr ()
{
     int   i=0, MaxRGB;
     char  c, buffer[128];
     
     //Read header of PPM file
     printf("\n\n File <%s> Header: \n",infile);
     
     do
     {
       c = fgetc(infptr);
       buffer[i] = c;
       i++; 
     } while (c != '\n');
     
     //Check if file is P6 (pPm) format
     if (buffer[1] == '6')
       printf("\n Input file is pgm, OK\n");
     else
     {
       printf("\n Input file is NOT pgm, Exiting program...\n");
       system("PAUSE");
       exit(0);
     }
     
     //File is pgm, read rest of header
     fscanf(infptr,"%d %d %d",&NCols, &MRows, &MaxRGB);
     c = fgetc(infptr);
     printf("%d ",NCols);
     printf("%d   <---- Width x Height) \n",MRows);
     printf("%d   <---- Max. Grayscale level) \n\n",MaxRGB);
}  // end readhdr ()

//----------------------------------------------------------------------------//
//         Add Header                                                         //
//----------------------------------------------------------------------------//

void addhdr ()
{
     fprintf(outfptr, "P5\n%d %d\n%d\n",NCols,MRows,255);
} //addhdr ()

//----------------------------------------------------------------------------//
//         Crear una imagen de GS a partir de una RGB                                            //
//----------------------------------------------------------------------------//

void userdefined ()
{
	unsigned char Red, Green, Blue, Gray;
	
	do{
		// leer los primer 3 bites
		Red = fgetc(infptr);
		Green = fgetc(infptr);
		Blue = fgetc(infptr);
		
		// Promedio
		//Gray = (Red + Green + Blue)/3;
		
		// Tomar solo el canal rojo
		//Gray = Red;
		
		// Tomar solo el canal verde
		//Gray = Green;
		
		// Tomar solo el canal azul
		//Gray = Blue;
		
		// Asignacion de pesos a los canales de color (Los pesos deben sumar 1)
		Gray = ((0.3*Red)+(0.4*Green)+(0.3*Blue));
		
		// Guardar el pixel en la imagen de salida
		fputc(Gray,outfptr);
	}while(!feof(infptr));
	 
}  // end userdefined ()

//----------------------------------------------------------------------------//
//         Close Files                                                        //
//----------------------------------------------------------------------------//

void closefiles ()
{
     fclose(infptr);
     fclose(outfptr);
}  // end closefiles ()
