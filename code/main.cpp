#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include "unit/unit.h"

const int SCREEN_WIDTH  = 720;
const int SCREEN_HEIGHT = 438;

int camX=SCREEN_WIDTH/2;
int camY=SCREEN_HEIGHT/2;
int camOldX=0;
int camOldY=0;
int mouseMidOldX=0;
int mouseMidOldY=0;
int mouse_mid_state=0;
int mouse_right_state=0;
int textureSize = 64;

unit unitA;
const int map_x = 128*128;
const int map_y = 128*128;
const int map_z = 128*128;

int getCamX()
{
	return camX - SCREEN_WIDTH/2;
}
int getCamY()
{
	return camY - SCREEN_HEIGHT/2;
}
int cleanup(SDL_Window *win=NULL, SDL_Texture *tex=NULL, SDL_Renderer *ren=NULL)
{
    if(tex)
        SDL_DestroyTexture(tex);
    if(ren)
	    SDL_DestroyRenderer(ren);
    if(win)
        SDL_DestroyWindow(win);
    return 0;
}
int cleanup(SDL_Texture *tex=NULL, SDL_Renderer *ren=NULL, SDL_Window *win=NULL)
{
    if(tex)
        SDL_DestroyTexture(tex);
    if(ren)
	    SDL_DestroyRenderer(ren);
    if(win)
        SDL_DestroyWindow(win);
    return 0;
}
void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h, const SDL_Point *center, double angle)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	//SDL_RenderCopy(ren, tex, NULL, &dst);
	SDL_RenderCopyEx(ren, tex, NULL, &dst, angle, center, SDL_FLIP_NONE);
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, const SDL_Point *center, double angle)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h, center, angle);
}
inline void keyDown(const SDL_Event& ev)
{

}
inline void mouseDown(const SDL_Event& ev)
{
	if(ev.button.button == SDL_BUTTON_MMASK)
	{
		mouseMidOldX=ev.button.x;
		mouseMidOldY=ev.button.y;
		camOldX=camX;
		camOldY=camY;
		mouse_mid_state=1;
	}
}
inline void mouseUp(const SDL_Event& ev)
{
	if(ev.button.button == SDL_BUTTON_MMASK)
	{
		mouse_mid_state=0;

	}
	if(ev.button.button == SDL_BUTTON_RIGHT)
	{
		mouse_right_state=0;
		order thisOrder;
		thisOrder.orderType_=1;
		thisOrder.target_.coord_={getCamX() + (double)ev.button.x, getCamY() + (double)ev.button.y};
		unitA.addOrder(thisOrder);
	}
	
}
int calcTextureCoordByCameraX(int x)
{
	return x%(textureSize)*-1 - textureSize*2;
}
int calcTextureCoordByCameraY(int y)
{
	return y%(textureSize)*-1 - textureSize*2;
}
void camMove(int x, int y)
{
	camX = camOldX - (x - mouseMidOldX);
	camY = camOldY - (y - mouseMidOldY);
}
void mouseMove(const SDL_Event& ev)
{
	if(mouse_mid_state)
		camMove(ev.button.x, ev.button.y);
}

Uint32 callback(Uint32 interval, void *param)
{  
	//SDL_Log("current time: %d ms.\n", SDL_GetTicks());
	
	OrderList& orderList = unitA.orderList();
	if(orderList.size() == 0)
		return interval;
	order& firstOrder = orderList.front();
	
	if(firstOrder.orderType_==1)
	{
		double x1=unitA.x();
		double y1=unitA.y();
		double x2=firstOrder.target_.coord_.x_;
		double y2=firstOrder.target_.coord_.y_;
		double angle = toAngle2(angleBetweenPoints(x1, y1, x2, y2));
		double dist = 2;
		double turnSpeed=unitA.turnSpeed();
		unitA.x(polarProjectionX(x1, dist, angle));
		unitA.y(polarProjectionY(y1, dist, angle));
		double face = unitA.faceAngle();
		if(face > angle)
		{
			if(360 - face + angle < 180 && !(inAngle(face, angle, turnSpeed)))
				unitA.faceAngle(toAngle2(face + unitA.turnSpeed()));
			else if(360 - face + angle >= 180 && !(inAngle(face, angle, turnSpeed)))
				unitA.faceAngle(toAngle2(face - unitA.turnSpeed()));
		}
		else
		{
			
			if(360 - angle + face < 180 && !(inAngle(face, angle, turnSpeed)))
				unitA.faceAngle(toAngle2(face - unitA.turnSpeed()));
			else if(360 - angle + face >= 180 && !(inAngle(face, angle, turnSpeed)))
				unitA.faceAngle(toAngle2(face + unitA.turnSpeed()));
		}
					
		if(DistanceBetweenPoints(x1, y1, x2, y2) < dist)
		{
			orderList.pop_front();
		}
	}
	
	return interval;
}  

int main(int, char**)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}
	
	SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
		| SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}
	SDL_Texture *image_texture = loadTexture("./res/texture.png", renderer);
	if (image_texture == nullptr)
	{
		cleanup(image_texture, renderer, window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	SDL_Texture *image_unit = loadTexture("./res/unit.png", renderer);
	SDL_Texture *image_status = loadTexture("./res/status.png", renderer);
	SDL_Texture *image_avatar = loadTexture("./res/avatar.png", renderer);
	int iW, iH;
	SDL_QueryTexture(image_texture, NULL, NULL, &iW, &iH);
	int statusW,statusH;
	SDL_QueryTexture(image_status, NULL, NULL, &statusW, &statusH);
	int xAmount=(int)(SCREEN_WIDTH/iW+4);
	int yAmount=(int)(SCREEN_HEIGHT/iH+4);

	SDL_Event e;
	//const unsigned int FPS=1000/30;
	//Uint32 _FPS_Timer;
	//
	bool quit = false;
	SDL_RenderClear(renderer);
	SDL_TimerID timer = SDL_AddTimer(10, callback, NULL);
	//SDL_bool SDL_RemoveTimer(SDL_TimerID id)
	if (timer == 0)
	{
		SDL_Log("add timer fail: %s\n", SDL_GetError());
	}
	unitA.create(0.0, 0.0, 50.0);
/*
	double x2[4]={151.5,229.5,349.5,277.9};
	double y2[4]={310.5,370.5,277.5,223.1};
	double x1[4]={208.2,247.2,287.9,248.1};
	double y1[4]={294.9,326.1,294.2,263.2};
	
	for(int i=0; i<5000; i++)
	{
		coord c=randInRect(x2[0],y2[0],x2[1],y2[1],x2[3],y2[3]);
		if(isInPolygon(4,x1,y1,c.x_,c.y_))
		{
			i--;
			continue;
		}
		unitArray[i].create(c.x_, c.y_);
	}
	*/
	while (!quit)
	{
		//if(SDL_GetTicks()-_FPS_Timer<FPS)
		//{
		//	SDL_Delay(FPS-SDL_GetTicks()+_FPS_Timer);
		//}
    	//_FPS_Timer=SDL_GetTicks();
		//
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = 1;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				keyDown(e);
			}
			else if(e.type == SDL_KEYUP)
			{
				SDL_Keycode key = e.key.keysym.sym;
				if(key == SDLK_ESCAPE)
					quit = 1;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				mouseDown(e);
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				mouseUp(e);
			}
			else if (e.type == SDL_MOUSEMOTION)
			{
				mouseMove(e);
			}
		}//5148
		//SDL_RenderClear(renderer);
		for(int i=0; i<yAmount; i++)
			for(int j=0; j<xAmount; j++)
				renderTexture(image_texture, renderer,
				j*iW+calcTextureCoordByCameraX(camX),
				i*iH+calcTextureCoordByCameraY(camY), NULL, 0);

		renderTexture(image_unit, renderer, -1 * getCamX() + unitA.x()-unitA.r(),
		-1 * getCamY()  + unitA.y()-unitA.r(), NULL, unitA.faceAngle());
		//for(UnitMap::iterator it = unit::unitMap_.begin(); it != unit::unitMap_.end(); it++)
		//{
		//	//it->second.visible(rand()%1);
		//	if(it->second.visible())
		//		renderTexture(image_unit, renderer, -1 * getCamX() - 32+it->second.x(),
		//			-1 * getCamY() - 32 + it->second.y(), NULL, it->second.faceAngle());
		//}
		renderTexture(image_status, renderer, (SCREEN_WIDTH-statusW) / 2,
			SCREEN_HEIGHT-statusH, NULL, 0);
		renderTexture(image_avatar, renderer, (SCREEN_WIDTH-statusW) / 2 + 15,
			SCREEN_HEIGHT-statusH+15, NULL, 0);
		SDL_RenderPresent(renderer);
	}
	IMG_Quit();
	SDL_Quit();

	return 0;
}