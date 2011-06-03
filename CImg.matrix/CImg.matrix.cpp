/*-----------------------------------------------------------------------

  File        : matrix.cpp

  Description : display of matrix image program of the Laboratory of Mechanics in Lille (LML)

  Author      : Sebastien COUDERT
  
  --------------------------------------------------------------------*/

/*Additional documentation for the generation of the reference page (using doxygen)*/
/** \mainpage
 *
 *  index:
 *  \li \ref sectionCommandLine
 *  \li \ref sectionDisplayDocumentation
 *  \li \ref sectionDoxygenSyntax
 *
 *  \section sectionCommandLine command line options
 *  \verbinclude "CImg.display.help.output"
 *
 *  \section sectionDisplayDocumentation documentation outline
 *  This is the reference documentation of <a href="http://www.meol.cnrs.fr/">CImg.display</a>, from the <a href="http://www.univ-lille1.fr/lml/">LML</a>.\n\n
 *  CImg.display is a image displaying software. The program begins in the main function in the <a href="CImg_8display_8cpp.html">CImg.display.cpp</a> source file.\n\n
 *  This documentation has been automatically generated from the CImg.display sources, 
 *  using the tool <a href="http://www.doxygen.org">doxygen</a>. It should be readed as HTML, LaTex and man page.\n
 *  It contains both
 *  \li a detailed description of all classes and functions
 *  \li a <a href="user.html">user guide</a>
 *
 *  that as been documented in the sources.
 *
 *  \par Additional needed libraries:
 *
 *  \li <a href="http://cimg.sourceforge.net">the CImg Library</a> (v1.3.9) using <a href="http://www.imagemagick.org/">ImageMagick</a> for a few image format
 *
 *  \par Optional libraries:
 *
 *  \li i/o <a href="http://www.unidata.ucar.edu/software/netcdf/">NetCDF</a> (network Common Data Form)
 *  \li added to CImg raw, <a href="http://www.rd-vision.com/">Hiris</a>, <a href="http://www.pco.de/">PCO</a> and <a href="http://www.lavision.de">LaVision</a> images support
 *  \li i/o <a href="http://www.libpng.org/">libPNG</a> (Portable Network Graphics) using <a href="http://www.zlib.net/">zLib</a> (non destructive compression)
 *  \li i/o <a href="http://www.libtiff.org/">libTIFF</a> (Tag Image File Format) - need libJPEG for static linking
 *  \li v  vector image <a href="http://libboard.sourceforge.net/">Board</a> (A vector graphics C++ library: Postscript, SVG and Fig files)
 *
 *  \section sectionDoxygenSyntax make documentation using Doxygen syntax
 *  Each function in the source code should be commented using \b doxygen \b syntax in the same file.
 *  The documentation need to be written before the function.
 *  The basic syntax is presented in this part.
 *  \verbinclude "doxygen.example1.txt"
 *
 *  Two kind of comments are needed for \b declaration and \b explanation \b parts of the function:
 *  Standart documentation should the following (\b sample of code documentation):
 *  \verbinclude "doxygen.example2.txt"
 *
 *  In both declaration and explanation part, \b writting and \b highlithing syntax can be the following:\n\n
 *  \li \c \\code to get\n
 *
 *  \li \c \\n    a new line
 *  \li \c \\li   a list (dot list)
 *
 *  \li \c \\b    bold style
 *  \li \c \\c    code style
 *  \li \c \\e    enhanced style (italic)
 *
 *  For making \b shortcut please use:\n
 *  \li \c \\see to make a shortcut to a related function or variable
 *  \li \c \\link to make a shortcut to a file or a function
 *  \note this keyword needs to be closed using \c \\end*
 *
 *  \li \c \\todo to add a thing to do in the list of <a href="todo.html">ToDo</a> for the whole program
 *
 *  In explanation part, \b paragraph style can be the following:\n
 *  \li \c \\code for an example of the function use
 *  \li \c \\note to add a few notes
 *  \li \c \\attention for SOMETHING NOT FULLY DEFINED YET
 *  \li \c \\warning to give a few warning on the function
 *  \note these keywords need to be closed using \c \\end*
 *
 *  \verbinclude "doxygen.example3.txt"
 *
 *  Many other keywords are defined, so please read the documentation of <a href="http://www.doxygen.org/commands.html">doxygen</a>.
 *
**/

/** \page user user guide
 *
 * \todo add screen capture
 * \todo use section (instead of paragraphs) and add table of contents (such as in mainpage)
 *
 * \par different type of display for image
 *
 * 3 types of display in this software:
 *  \li 2D map (default)
 *  \li 1D graph (\c --1D option)
 *  \li 3D surface (\c --3D option), not implemented, yet !
 *
 * others display command line options using \c -h option
 * \verbinclude "CImg.display.help.output"
 *
 * \par 2D map (default)
 * display image as map
 * \code
 *   ./CImg.display -i image.PNG
 * \endcode
 * GUI keyboard options:
 *  \li \c Ctrl+S: save current view
 *
 * \par 1D graph
 * display image as both map and 1D graph(s) (either X axis or Y axis)
 * \code
 *   ./CImg.display -i image.PNG --1D
 * \endcode
 * GUI keyboard options:
 *  \li \c c: color
 *  \li \c v: value
 *  \li \c l: luminance
 *  \li \c i: intensity
 *  \li \c Ctrl+S: save current view
 * GUI mouse options:
 *  \li \c left button: X axis
 *  \li \c right button: Y axis
 *
 * \par 3D surface
 * \todo documentation of 3D surface
**/

// Include CImg library file and use its main namespace
#include "CImg.h"
using namespace cimg_library;

#include <iostream>
//debug macro
#if cimg_verbosity>=3
#define PR(value) std::cerr<<#value<<"="<<value<<std::endl<<std::flush;
#else
#define PR(value) ;
#endif

//! print value as bit string
/**
 * \param [in] value : value to print as bit using a string
**/
void printAsBit(int value)
{
  for(int i=0;i<16;i++)
  {
    int k=1<<i;
    bool b=(value&k);
    if(i==4||i==12) std::cout<<" ";
    if(i==8) std::cout<<"  ";
    std::cout<<b;
  }
}

//! set value as bit CImg
/**
 * \param [in] value : value to print as bit using a string
**/
void setAsBit(int value,CImg<bool> &bit)
{
  cimg_forX(bit,i)
  {
    int k=1<<i;
    bit(i)=(value&k);
  }
}

//! draw value in image
/**
 * \param [in] value : value to print as bit within the image
 * \param [tmp] bit : size=16 (i.e. 4x4)
 * \param [out] image : 
 * \param [in] tx  : text size for margin only
 * \param [in] psx : 
 * \param [in] psy : 
 * \param [in] ssx : 
 * \param [in] ssy : 
**/
//template<typename T>
void draw_value(int j,CImg<bool> &bit,CImg<unsigned char> &image,int ts,int psx,int psy,int ssx,int ssy)
{
  const unsigned char white[]={255};//,black[]={0};//{255,255,255};
  //set bit vector
  setAsBit(j,bit);
  //trick: change vector dimensions
  bit._width=4;bit._height=4;
  //draw white rectangles (if needed)
  cimg_forXY(bit,x,y) if(bit(x,y))
  {
    int x0=x*(psx+ssx)+ts+2*ssx;
    int y0=y*(psy+ssy)+ts+2*ssy;
    int x1=x0+psx;
    int y1=y0+psy;
    image.draw_rectangle(x0,y0,x1,y1,white);
  }//draw bit
  //trick: back to vector dimensions
  bit._width=16;bit._height=1;
}

//! draw axes and value as text in image
/**
 * \param [in] value : value to print as bit within the image
 * \param [out] image : 
 * \param [in] ts  : text size
 * \param [in] psx : 
 * \param [in] psy : 
 * \param [in] ssx : 
 * \param [in] ssy : 
**/
//template<typename T>
void draw_axesNvalue(int j,CImg<unsigned char> &image,int ts,int psx,int psy,int ssx,int ssy)
{
  const unsigned char white[]={255},black[]={0};//{255,255,255};
  //text
  int x0=ssx;
  int y0=ssy; 
  int x1=4*(psx+ssx)+ts+2*ssx;
  int y1=4*(psy+ssy)+ts+2*ssy;
  //draw value
  image.draw_text(x1,y1,"% 5d",white,black,1,ts,j);
  //draw axes
  image.draw_text(x0,y0,"O",white,black,1,ts);
  image.draw_text(x1,y0,"X",white,black,1,ts);
  image.draw_text(x0,y1,"Y",white,black,1,ts);
}

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/soundcard.h>

//!
/**
 * 
**/
void dsp_open(int &fd,int size,int channels,int rate)
{
//open sound device
  fd=open("/dev/dsp", O_RDWR);
  if(fd<0){std::cerr<<"error /dev/dsp: open of /dev/dsp failed";exit(2);}
//set sampling parameters
  //argument for ioctl calls
  int arg;
  //sample size
  arg=size;
  if(ioctl(fd, SOUND_PCM_WRITE_BITS, &arg)==-1) std::cerr<<"error /dev/dsp: SOUND_PCM_WRITE_BITS ioctl failed";
  if(arg != size) std::cerr<<("error /dev/dsp: unable to set sample size");
  //mono or stereo
  arg=channels;
  if(ioctl(fd, SOUND_PCM_WRITE_CHANNELS, &arg) == -1) std::cerr<<"error /dev/dsp: SOUND_PCM_WRITE_CHANNELS ioctl failed";
  if(arg != channels) std::cerr<<"error /dev/dsp:unable to set number of channels";
  //sampling rate
  arg=rate;
  if(ioctl(fd, SOUND_PCM_WRITE_RATE, &arg)==-1) std::cerr<<"error /dev/dsp:SOUND_PCM_WRITE_WRITE ioctl failed";
}
//!
/**
 * 
**/
void dsp_read(int &fd,CImg<char> &buffer)
{
  size_t size=buffer.size();
  if(read(fd, buffer.data(), size)!=size) {std::cerr<<"error /dev/dsp: read fail (wrong number of bytes).";exit(2);}
}
// Main procedure
int main(int argc,char **argv)
{
//! \todo add doxygen comments for main, within the main and PR()
// Define program usage and read command line parameters
  // Display program usage, when invoked from the command line with option '-h'.
  cimg_usage("display matrix image (as 2D map) along time.");
  const int delay=cimg_option("--delay",25,"delay bettween matrix images in ms");
  const bool display_text=cimg_option("--text",false,"display number as text also (i.e. with in the terminal with --text true)");
  const int display_value=cimg_option("--value",-1,"display value only (i.e. --value 1234 or --value -3)");
  const int isx=cimg_option("-isx",512,"image size along x axis");
  const int isy=cimg_option("-isy",512,"image size along y axis");
  const int psx=cimg_option("-psx",48,"pattern size along x axis");
  const int psy=cimg_option("-psy",48,"pattern size along y axis");
  const int ssx=cimg_option("-ssx",16,"space size along x axis");
  const int ssy=cimg_option("-ssy",16,"space size along y axis");
  const int ts= cimg_option("-ts", 36,"text size");
  const int n=  cimg_option("-n",16,"matrix number to display");
  //help
  const bool help=cimg_option("-h",false,"display this help.");
  //exit on help request '-h' command line option
  if(help) return 0;
/*
int size=8;//bit (8 or 16 bit)
int channels=2;//1 or 2 channels
int rate=8000;//Hz: 8000, 11025, 16000, 22050, 32000, 44100, 48000, 88200, 96000, 192000
int lenght=n;//seconds
CImg<char> record(lenght*rate*size*channels/8);
int fd;
dsp_open(fd,size,channels,rate);
dsp_read(fd,record);
record.display("record");
return 0;
*/
//prepare images
  //Image sizes
  CImg<bool> bit(16);
//special case display a number only
  if(display_value!=-1)
  {
    CImg<unsigned char> img(isx,isy);
    //draw value as white rectangles
//! \todo put \c bit at last parameter in \c draw_value function (i.e. default would be to assign)
    draw_value(display_value,bit,img,ts,psx,psy,ssx,ssy);
    //draw OXY
    draw_axesNvalue(display_value,img,ts,psx,psy,ssx,ssy);
    //display
    img.display("specific number");
    //normal exit
    return 0;
  }//display ONE number ONLY
  CImgList<unsigned char> image(n,isx,isy);
  cimglist_for(image,j)
  {
    //draw value as white rectangles
    draw_value(j,bit,image[j],ts,psx,psy,ssx,ssy);
    //draw OXY
    draw_axesNvalue(j,image[j],ts,psx,psy,ssx,ssy);
//! \todo draw black and add exposure number
  }
//display images in GUI
  CImgDisplay display(image[0],"16 box combinations",0);
  //event loop
  //This loop ends when one of the two display window is closed or when the keys 'ESC' or 'Q' are pressed.
  int i=0;
  while(!display.is_closed() && !display.is_keyESC() && !display.is_keyQ())
  {
    //text in console
    if(display_text)
    {
      std::cout<<"\r"<<i<<"  ";
      printAsBit(i);
      std::cout<<"       "<<std::flush;
    }
    display.display(image[i]);
    //next loop
    i=(++i<n)?i:0;
    // Temporize event loop
    cimg::wait(delay);
  }//event loop
  if(display_text) std::cout<<"\n";
  return 0;
}

