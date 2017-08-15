#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

#include "Scene.h"
#include "SingletonTemplate.h"
#include <list>
#include "Vector3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Utility.h"
#include <string>

using std::string;



class UIManager : public Singleton<UIManager>,public Scene
{
	friend Singleton<UIManager>;

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,

		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_NUMLIGHTS,
		U_TOTAL,
	};

	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TITLE,
		GEO_SELECT1,
		GEO_SELECT2,
		GEO_SELECT3,
		GEO_FRONT,
		GEO_CINAMATIC,
		GEO_TEXT,
		NUM_GEOMETRY,
	};

private:
	UIManager();
	virtual ~UIManager();

	float transX;
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Mesh* meshList[NUM_GEOMETRY];

	string deltaTime;

	float TextSize;//resizing the image when checking left or right
	float TextSize_2;//resizing text for scene for startgame
	float TextSize_3; //resizing text for scene for exit game
	float TextSize_4; //resizing text for scene for Credit
	bool TextChecking;//if they press Enter already
	bool TextSwitching;//Checking the left and right button
	bool TitleCheck;
	bool bSomethingHappen;
	int MenuSelect;
	float Delaytimer[3];

	float rotateAngle;
	float translateX[3];
	float scaleAll;
	float titlescale;
	float Translating[2];
	MS modelStack, viewStack, projectionStack;

	bool lightEnable;
	void RenderMesh(Mesh *mesh, bool enableLight);

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	
public:


	virtual void Init();
	virtual void UpdateUI(double dt);
	virtual void RenderUI();
	virtual void Exit();
	void CreateUI();

	void RenderMainMenu();
	void RenderPauseMenu();
	void RenderOptionsMenu();
};

#endif
