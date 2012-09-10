#ifndef __FONT_H__
#define __FONT_H__

#include <string>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL.h>
#include <cstdlib>

using namespace std;

class Font
{
  private:
        GLuint*	 			m_pTextures;
		GLuint 				m_iListBase;
		string				alias;
		int					m_iSize;
		double				NORMAL_TEX_INTERVAL;
		double				WIDE_TEX_INTERVAL;
		double				LARGE_TEX_INTERVAL;
		double				SMALL_TEX_INTERVAL;
		double				HEIGHT_TEX_INTERVAL;

		void 				print(float x, float y, const char* fmt, ...);

  public:

        Font();
        Font(string alias);

		void				init(string filename, int _size);
		void				clean();

        string              getAlias();
		void				setFontSize(int _iSize);
		void				drawText(string text, double x, double y);
		void				drawText(int numText, double x, double y);
		void                drawText(unsigned int numText, double x, double y);
		void				drawText(double numText, double x,
									   double y);

};
#endif
