/*-----------------------------------------------------------------------

  File        : xirtam.cpp

  Description : get number from matrix image program of the Laboratory of Mechanics in Lille (LML)

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
//e.g. add on g++ command line -Dcimg_verbosity=3 to activate debug output (e.g. g++ -Dcimg_verbosity=3)
#if cimg_verbosity>=3
#define PR(value) std::cerr<<#value<<"="<<value<<std::endl<<std::flush;
#else
#define PR(value) ;
#endif
#include <vector>
#include <cstring>

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

//! get value from bit CImg
/**
 * \param [in]  bit   : bit vector
 * \param [out] value : corresponding value
**/
void getAsBit(CImg<bool> &bit,int &value)
{
  value=0;
  cimg_forX(bit,i)
  {
    int k=1<<i;
    if(bit(i)) value|=k;
  }
}

//! draw value in image
/**
 * \param [in] position : calibration position of number matrix
 * \param [in] image : recorded image
 * \param [out] bit : 
**/
template<typename T>
void get_bit_value(CImg<int> &position,T threshold,int mean_size,CImg<T> &image,CImg<bool> &bit)
{
  //trick: change vector dimensions
  bit._width=4;bit._height=4;
  //check sizes
  if((position.width()!=bit.width())||(position.height()!=bit.height())) {PR("error: code error not same XY size.");bit._width=16;bit._height=1;return;}
  //ROI to get mean value around point of interest (Region Of Interest)
  CImg<T> roi(mean_size,mean_size);
  //get matrix
  cimg_forXY(position,x,y)
  {
    int x0=position(x,y,0)-mean_size/2;
    int y0=position(x,y,1)-mean_size/2;
    int x1=x0+mean_size;
    int y1=y0+mean_size;
    roi=image.get_crop(x0,y0,x1,y1);
    bit(x,y)=(roi.mean()>threshold);
  }
  //trick: back to vector dimensions
  bit._width=16;bit._height=1;
}

//!
/**
 *
**/
template<typename T>
void draw_ROI(int x, int y,int roi_size,CImg<T> &cal)
{
  int x0=x-roi_size/2;
  int y0=y-roi_size/2;
  int x1=x0+roi_size;
  int y1=y0+roi_size;
  const T color[]={cal.min(),cal.max(),cal.min()};//green
  cal.draw_rectangle(x0,y0,x1,y1,color);
}
//!
/**
 *
**/
template<typename T>
void get_calibration_positions(CImg<T> &cal,int roi_size,CImg<int> &position)
{
//! \todo [low] slow on big image, migh go faster using zoom and CImgDisplay
  //set position size
  position.assign(2,2,2);//and finaly (4,4,2) after interpolation (see resize)
  //GUI titles
  std::vector<std::string> points;points.push_back("origin");points.push_back("X axis");points.push_back("Y axis");points.push_back("unity");
  std::vector<std::string> coordinates;coordinates.push_back("(0,0)");coordinates.push_back("(3,0)");coordinates.push_back("(0,3)");coordinates.push_back("(3,3)");
  std::string title;
  //current selected position
  CImg<int> pos;
  //get positions on calibration image
  int i=0;
  for(int y=0;y<2;++y)
  for(int x=0;x<2;++x,++i)
  {
    //set title of selection image
    title="select "+points[i]+" point (i.e. "+coordinates[i]+" coordinates)";
    //get point position
    pos=cal.get_select((char*)title.c_str());
//pos.print("pos");
    position(x,y,0)=pos(0);//x
    position(x,y,1)=pos(1);//y
    //draw position
    draw_ROI(pos(0),pos(1),roi_size,cal);
  }
  //set all positions
  position.resize(4,4,2,1,3);//3=linear interpolation
  //draw all positions
  cimg_forXY(position,x,y) draw_ROI(position(x,y,0),position(x,y,1),roi_size,cal);
  //display positions
//  cal.display("calibration selection");
}
//!
/**
 *
**/
template<typename T>
void get_calibration_minmax_values(CImg<T> &cal,int roi_size,CImg<int> &miximum)
{
//! \todo [low] slow on big image, migth go faster using zoom and CImgDisplay
  //set position size
  miximum.assign(2);
  //GUI titles
  std::vector<std::string> points;points.push_back("miminum");points.push_back("maximum");
  std::string title;
  //current selected position
  CImg<int> pos;
  //ROI to get mean value around point of interest (Region Of Interest)
  CImg<T> roi(roi_size,roi_size);
  //get gray level values on calibration image
  for(int i=0;i<2;++i)
  {
    //set title of selection image
    title="select "+points[i]+" point";
    //get point position
    pos=cal.get_select((char*)title.c_str());
//pos.print("pos");
    //get value
    int x0=pos(0)-roi_size/2;
    int y0=pos(1)-roi_size/2;
    int x1=x0+roi_size;
    int y1=y0+roi_size;
    roi=cal.get_crop(x0,y0,x1,y1);
    miximum(i)=roi.mean();
  }
}
//!
/**
 * \param [in] manyString:   many string ex.: "str1,str2,str3" or "str1 str2 str3"
 * \param [out] value: strings in vector ex.: str1 str2 str3
**/
void split_string(const std::string manyString,std::vector<std::string> &value)
{
  ///split the single block "manyString" to vector containing all the string
  char *cstr,*ptr;char *split=(char*)(" ,;");
  cstr=new char [manyString.size()+1];
  strcpy(cstr,manyString.c_str());
  ptr=strtok(cstr,split);
  while (ptr!=NULL)
  {
    value.push_back(ptr);
    ptr=strtok(NULL,split);
  }
  delete[] cstr;
  return;
}
// Main procedure
int main(int argc,char **argv)
{
//! \todo add doxygen comments for main, within the main and PR()
// Define program usage and read command line parameters
  // Display program usage, when invoked from the command line with option '-h'.
  cimg_usage("get number from matrix image (as 2D map) along time.\n"
  "  examples:\n"
  "    CImg.xirtam -c calibration.png -i matrix.png\n"
  "    ls matrix_c1_000.png matrix_c2_000.png matrix_c1_001.png matrix_c2_001.png | CImg.xirtam -c calibration_c1.png,calibration_c2.png -i stdin -n 2\n"
  "    ls matrix_c1_010.png matrix_c2_010.png matrix_c1_011.png matrix_c2_011.png | CImg.xirtam -c calibration.cimg -C file -i stdin -n 2\n"
  "\n  #bash list example for xirtam\n"
  "    list=list.txt; rm $list; for((i=0;i<10;i++)); do zerosi=`printf %03d $i`; for((c=1;c<5;c++)); do f=image_c$c'_'$zerosi.png; ls $f >> $list; done; done; cat $list\n"
  "    cat list.txt | CImg.xirtam -c calibration_c1.png,calibration_c2.png,calibration_c3.png,calibration_c4.png -i stdin -n 4\n"
  "compilation on "
  );
  const std::string matrix_file_name=cimg_option("-i","matrix.png","matrix file name [in] (e.g. -i stdin)");
  const std::string number_file_name=cimg_option("-o","values","number file base name for all images (and cameras) in .cimg format [out]");
  const std::string calibration_type=cimg_option("-C","GUI","calibration type: 'GUI' or 'file' [in]");
  const std::string calibration_file_name=cimg_option("-c","calibration.png","calibration file name(s) (or calibration file name if '-C file' set) [in]");
  const std::string output_calibration_file_name=cimg_option("-O","calibration.cimg","calibration file name if '-C GUI' set [out]");
  const int n=cimg_option("-n",1,"number of camera");
  const int mean_size=cimg_option("--mean-size",9,"size for mean value");
  //help
  const bool help=cimg_option("-h",false,"display this help.");
  //exit on help request '-h' command line option
  if(help) return 0;
//calibration images
  //calibration file names
  std::vector<std::string> calibration_file_names;
  split_string(calibration_file_name,calibration_file_names);
  if(calibration_file_names.size()!=(size_t)n) std::cerr<<"Error: calibration image file name number differs from number of camera (i.e. "<<n<<" cameras regarding to "<<calibration_file_names.size()<<" file names)\n";
  //Image sizes
  CImg<bool> bit(16);//4x4
  CImgList<int> position(n);//(n,4,4,2) x,y
  CImgList<int> miximum(n);//(n,2) min,max
  if(calibration_type=="GUI")
  {//GUI: load calibration image file(s)
    CImg<int> cal;
    cimglist_for(position,c)
    {//camera loop
      //load calibration image
      cal.load((char*)(calibration_file_names[c].c_str()));
      //get position on calibration image
      get_calibration_positions(cal,mean_size,position[c]);
      //get gray level range on calibration image
      get_calibration_minmax_values(cal,mean_size,miximum[c]);
    }//camera loop
    //save calibration parameters for future use (i.e. '-C file')
    CImgList<int> prm(2*n);
    cimglist_for(position,c)
    {
      prm[c]=position[c];
      prm[n+c]=miximum[c];
    }
    prm.save((char*)output_calibration_file_name.c_str());
    std::cout<<"information: calibration parameters from GUI is saved in "<<output_calibration_file_name<<" file.\n";
  }//GUI
  else
  {//file: load calibration position and miximum file
    CImgList<int> prm;
    prm.load((char*)calibration_file_name.c_str());
    cimglist_for(position,c)
    {
      position[c]=prm[c];
      miximum[c]=prm[n+c];
    }
  }//file
//matrix images
  //set file name number (1 if -i, otherwise max)
  int file_name_number;
  if(matrix_file_name!="stdin") file_name_number=1;
  else file_name_number=1<<16;//unsigned signed 16bit (for this signed 32bit)
PR(n);
PR(file_name_number);
  //get values
  CImg<int> img;
  CImg<int> value(file_name_number,n);//(image,camera)
value.print("value assign");
  int ni=0;
  for(int i=0;i<file_name_number;++i,++ni)
  {//image loop
    //camera index
    int c=0;
    //get camera file names
    std::vector<std::string> camera_file_name(n);
    //one image only
    if((n==1)&&(file_name_number==1)) camera_file_name[0]=matrix_file_name;
    else//one or more camera using stdin
    for(c=0;c<n;++c)
    {
      //get stdin file name
      std::string tmp_file_name;
      std::cin>>tmp_file_name;
      //end of stdin
      if(tmp_file_name.empty()) {PR("break camera loop");break;}
      //set file name
      camera_file_name[c]=tmp_file_name;
PR(c);PR(tmp_file_name);
    }//camera loop
    //if end of stdin
    if(c<n&&(file_name_number!=1)) {PR("break image loop");break;}
    //get numbers from images for all cameras
    for(c=0;c<n;++c)
    {//camera loop
      //load image from file
    std::cout<<"\'"<<camera_file_name[c]<<"\' "<<std::flush;
      img.load((char*)camera_file_name[c].c_str());
//img.display("matrix");
      //get bit value from image (using calibration positions)
      get_bit_value(position[c],(miximum[c](1)-miximum[c](0))/2,mean_size,img,bit);
//bit.display("bit");
      //convert bit array to value
      getAsBit(bit,value(i,c));
    printAsBit(value(i,c));std::cout<<" = "<<value(i,c)<<std::endl<<std::flush;
    }//camera loop
  }//image loop
value.print("value");
  //cut value to real number of image
  value.crop(0,0,ni-1,n-1);
value.print("value");
  //save
  std::string tmp=number_file_name+".cimg";
  value.save((char*)tmp.c_str());
  //! \todo add NetCDF save
  //check camera numbers
  //gradient
  CImgList<int> grad;
  grad=value.get_gradient(0,1);//xy forward difference
//grad[1].display("number difference between cameras");
  grad[0].crop(0,grad[0].width()-2);
//grad[0].display("number gradient between images");
  if(n>1)
  {//save camera difference
    tmp=number_file_name+".camera_difference.cimg";
    grad[1].save((char*)tmp.c_str());
  }
  if(ni>1)
  {//save image gradient
    tmp=number_file_name+".image_gradient.cimg";
    grad[0].save((char*)tmp.c_str());
  }
  if( (grad[0].min()==grad[0].max()) && (grad[1].min()==grad[1].max()) ) std::cout<<"information: test passed.\n";
  else std::cout<<"information: test FAILED.\n";
  return 0;
}

