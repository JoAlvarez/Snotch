#include "font.h"
#include <string>
//#include "image.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <cstdlib>
#include <sstream>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <stdexcept>
#include <vector>
#include <stdarg.h>

Font::Font()
{
	m_iSize = 12;
}

Font::Font(string alias)
{
    m_iSize = 12;
    this->alias = alias;
}

inline int next_p2 (int a )
{
	int rval=1;
	// rval<<=1 Is A Prettier Way Of Writing rval*=2;
	while(rval<a) rval<<=1;
	return rval;
}


void make_dlist (FT_Face face, char ch, GLuint list_base, GLuint * tex_base)
{

	// Load The Glyph For Our Character.
	if(FT_Load_Glyph( face, FT_Get_Char_Index( face, ch ), FT_LOAD_DEFAULT ))
		throw std::runtime_error("FT_Load_Glyph failed");

	// Move The Face's Glyph Into A Glyph Object.
	FT_Glyph glyph;
	if(FT_Get_Glyph( face->glyph, &glyph ))
		throw std::runtime_error("FT_Get_Glyph failed");

	// Convert The Glyph To A Bitmap.
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	// This Reference Will Make Accessing The Bitmap Easier.
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;

	// Use Our Helper Function To Get The Widths Of
	// The Bitmap Data That We Will Need In Order To Create
	// Our Texture.
	int width = next_p2( bitmap.width );
	int height = next_p2( bitmap.rows );

	// Allocate Memory For The Texture Data.
	GLubyte* expanded_data = new GLubyte[ 2 * width * height];

	for(int j=0; j <height;j++) {
		for(int i=0; i < width; i++){
			expanded_data[2*(i+j*width)]= expanded_data[2*(i+j*width)+1] =
				(i>=bitmap.width || j>=bitmap.rows) ?
				0 : bitmap.buffer[i + bitmap.width*j];
		}
	}


	// Now We Just Setup Some Texture Parameters.
	glBindTexture( GL_TEXTURE_2D, tex_base[ch]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	// Here We Actually Create The Texture Itself, Notice
	// That We Are Using GL_LUMINANCE_ALPHA To Indicate That
	// We Are Using 2 Channel Data.
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data );

	// With The Texture Created, We Don't Need The Expanded Data Anymore.
	delete [] expanded_data;

	// Now We Create The Display List
	glNewList(list_base+ch,GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D,tex_base[ch]);

	glPushMatrix();

	// First We Need To Move Over A Little So That
	// The Character Has The Right Amount Of Space
	// Between It And The One Before It.
	glTranslatef(bitmap_glyph->left,0,0);

	// Now We Move Down A Little In The Case That The
	// Bitmap Extends Past The Bottom Of The Line
	// This Is Only True For Characters Like 'g' Or 'y'.
	glTranslatef(0,bitmap_glyph->top-bitmap.rows,0);

	// Now We Need To Account For The Fact That Many Of
	// Our Textures Are Filled With Empty Padding Space.
	// We Figure What Portion Of The Texture Is Used By
	// The Actual Character And Store That Information In
	// The x And y Variables, Then When We Draw The
	// Quad, We Will Only Reference The Parts Of The Texture
	// That Contains The Character Itself.
	float   x=(float)bitmap.width / (float)width,
	y=(float)bitmap.rows / (float)height;

	// Here We Draw The Texturemapped Quads.
	// The Bitmap That We Got From FreeType Was Not
	// Oriented Quite Like We Would Like It To Be,
	// But We Link The Texture To The Quad
	// In Such A Way That The Result Will Be Properly Aligned.
	glBegin(GL_QUADS);
	glTexCoord2d(0,0); glVertex2f(0,bitmap.rows);
	glTexCoord2d(0,y); glVertex2f(0,0);
	glTexCoord2d(x,y); glVertex2f(bitmap.width,0);
	glTexCoord2d(x,0); glVertex2f(bitmap.width,bitmap.rows);
	glEnd();
	glPopMatrix();
	glTranslatef(face->glyph->advance.x >> 6 ,0,0);

	// Increment The Raster Position As If We Were A Bitmap Font.
	// (Only Needed If You Want To Calculate Text Length)
	// glBitmap(0,0,0,0,face->glyph->advance.x >> 6,0,NULL);

	// Finish The Display List
	glEndList();
}

void Font::init(string fname, int h)
{
	// Allocate Some Memory To Store The Texture Ids.
	m_pTextures = new GLuint[128];

	m_iSize = h;

	// Create And Initilize A FreeType Font Library.
	FT_Library library;
	if (FT_Init_FreeType( &library ))
		throw std::runtime_error("FT_Init_FreeType failed");

	// The Object In Which FreeType Holds Information On A Given
	// Font Is Called A "face".
	FT_Face face;

	// This Is Where We Load In The Font Information From The File.
	// Of All The Places Where The Code Might Die, This Is The Most Likely,
	// As FT_New_Face Will Fail If The Font File Does Not Exist Or Is Somehow Broken.
	if (FT_New_Face( library, fname.c_str(), 0, &face ))
		throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");

	// For Some Twisted Reason, FreeType Measures Font Size
	// In Terms Of 1/64ths Of Pixels.  Thus, To Make A Font
	// h Pixels High, We Need To Request A Size Of h*64.
	// (h << 6 Is Just A Prettier Way Of Writing h*64)
	FT_Set_Char_Size( face, h << 6, h << 6, 96, 96);

	// Here We Ask OpenGL To Allocate Resources For
	// All The Textures And Display Lists Which We
	// Are About To Create.
	m_iListBase=glGenLists(128);
	glGenTextures( 128, m_pTextures );

	// This Is Where We Actually Create Each Of The Fonts Display Lists.
	for(unsigned char i=0;i<128;i++)
		make_dlist(face,i,m_iListBase,m_pTextures);

	// We Don't Need The Face Information Now That The Display
	// Lists Have Been Created, So We Free The Assosiated Resources.
	FT_Done_Face(face);

	// Ditto For The Font Library.
	FT_Done_FreeType(library);


}

void Font::clean()
{
	glDeleteLists(m_iListBase,128);
	glDeleteTextures(128,m_pTextures);
	delete [] m_pTextures;
}

void Font::print(float x, float y, const char* fmt, ...)
{

	/**************************************************************************
	 We Want A Coordinate System Where Distance Is Measured In Window Pixels.
	**************************************************************************/

	GLuint font= m_iListBase;
	// We Make The Height A Little Bigger.  There Will Be Some Space Between Lines.
	float h = m_iSize / .63f;
	char	text[256];							// Holds Our String
	va_list	ap;									// Pointer To List Of Arguments

	if (fmt == NULL)							// If There's No Text
		*text=0;								// Do Nothing
	else
	{
		va_start(ap, fmt);						// Parses The String For Variables
		vsprintf(text, fmt, ap);				// And Converts Symbols To Actual Numbers
		va_end(ap);								// Results Are Stored In Text
	}

	// Here Is Some Code To Split The Text That We Have Been
	// Given Into A Set Of Lines.
	const char *start_line=text;
	vector<string> lines;
	const char *c=text;
	for(;*c;c++)
	{
		if(*c=='\n') {
			string line;
			for(const char *n=start_line;n<c;n++) line.append(1,*n);
			lines.push_back(line);
			start_line=c+1;
		}
	}
	if(start_line) {
		string line;
		for(const char *n = start_line; n < c; ++n)
			line.append(1,*n);
		lines.push_back(line);
	}

	glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT  | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glListBase(font);


	float modelview_matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

	// This Is Where The Text Display Actually Happens.
	// For Each Line Of Text We Reset The Modelview Matrix
	// So That The Line's Text Will Start In The Correct Position.
	// Notice That We Need To Reset The Matrix, Rather Than Just Translating
	// Down By h. This Is Because When Each Character Is
	// Drawn It Modifies The Current Matrix So That The Next Character
	// Will Be Drawn Immediately After It.
	for(int i=0;i<lines.size();i++) {
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(x,y-h*i,0);
		glMultMatrixf(modelview_matrix);

	// The Commented Out Raster Position Stuff Can Be Useful If You Need To
	// Know The Length Of The Text That You Are Creating.
	// If You Decide To Use It Make Sure To Also Uncomment The glBitmap Command
	// In make_dlist().
		// glRasterPos2f(0,0);
		glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());
		// float rpos[4];
		// glGetFloatv(GL_CURRENT_RASTER_POSITION ,rpos);
		// float len=x-rpos[0]; (Assuming No Rotations Have Happend)

		glPopMatrix();
	}

	glPopAttrib();

	//pop_projection_matrix();
}

void Font::setFontSize(int _iSize)
{
	m_iSize = _iSize;
}

string Font::getAlias()
{
    return alias;
}

void Font::drawText(string text, double x, double y)
{
	if(text.size() == 0)
		return;

	while(text.substr(text.size() - 1, 1) == " ")
	{
		text = text.substr(0, text.size() - 1);

		if(text.size() == 0)
			return;
	}

	print(x, y, text.c_str());
}

void Font::drawText(int numText, double x, double y)
{
	string text;
	stringstream ss;
	ss << numText;
	ss >> text;

	print(x, y, text.c_str());
}

void Font::drawText(unsigned int numText, double x, double y)
{
	string text;
	stringstream ss;
	ss << numText;
	ss >> text;

	print(x, y, text.c_str());
}

void Font::drawText(double numText, double x, double y)
{
	string text;
	stringstream ss;
	ss << numText;
	ss >> text;

	print(x, y, text.c_str());
}


