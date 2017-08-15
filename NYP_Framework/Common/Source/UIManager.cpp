#include "UIManager.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "shader.hpp"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "MyMath.h"
#include "SceneManager.h"
using namespace Math;

UIManager::UIManager()
{
	m_programID = SceneManager::instance()->returnProg();
}

UIManager::~UIManager()
{
}

void UIManager::Init()
{
	// Init VBO here
	rotateAngle = 0;
	transX = 100; //For selection
	translateX[0] = 8;
	translateX[1] = 0;
	translateX[2] = 0;
	scaleAll = 1;
	TextSize = 3;
	TextSize_2 = 0;
	TextSize_3 = 0;
	TextSize_4 = 0;
	MenuSelect = 0;
	Translating[0] = 0;
	Translating[1] = 0;
	TitleCheck = false;
	TextChecking = true;
	TextSwitching = false;
	bSomethingHappen = false;

	lightEnable = true;

	//Emable depth test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); //Deletes the backface
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Initialise camera
	camera.Init(Vector3(0, 0, 0), Vector3(0, 0, -10), Vector3(0, 1, 0));
	//Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	for (int i = 0; i < NUM_GEOMETRY; ++i)
		meshList[i] = NULL;

	meshList[GEO_TITLE] = MeshBuilder::GenerateQuad("title", Color(1, 1, 1), 1, 1);
	meshList[GEO_TITLE]->textureID = LoadTGA("Image//UI//Mainmenu//title.tga");

	meshList[GEO_SELECT1] = MeshBuilder::GenerateQuad("title", Color(1, 1, 1), 1, 1);
	meshList[GEO_SELECT1]->textureID = LoadTGA("Image//UI//Mainmenu//start.tga");
	meshList[GEO_SELECT2] = MeshBuilder::GenerateQuad("title", Color(1, 1, 1), 1, 1);
	meshList[GEO_SELECT2]->textureID = LoadTGA("Image//UI//Mainmenu//credit.tga");
	meshList[GEO_SELECT3] = MeshBuilder::GenerateQuad("title", Color(1, 1, 1), 1, 1);
	meshList[GEO_SELECT3]->textureID = LoadTGA("Image//UI//Mainmenu//end.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//skybox//MainMenu.tga");

	meshList[GEO_CINAMATIC] = MeshBuilder::GenerateOBJ("Object", "OBJ//Objects//menu.obj");
	meshList[GEO_CINAMATIC]->textureID = LoadTGA("Image//model//Menutransition.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Text//gothiclight.tga");

	//Load vertex and fragment shaders
	//m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "TextColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 4000.0f);
	projectionStack.LoadMatrix(projection);
}

void UIManager::UpdateUI(double dt)
{
	Delaytimer[1] += (float)dt;

	if (Delaytimer[1] < 12)
	{
		Translating[0] -= (float)dt;
	}
	if (Delaytimer[1] > 12)
	{
		Translating[1] -= (float)dt;
		Translating[0] = 0;
	}
	if (Delaytimer[1] > 23)
	{
		Translating[1] = 0;
		Delaytimer[1] = 0;
	}

	static size_t selectedNum = 1;
	static float moveAmt = 60.f;
	static float curX = 0.f;
	// Title will appeared after 10 seconds (Check with DelayTimer at the else statement)
	//if (TitleCheck)
	//{
	//	titlescale = 50;
	//	if (TextChecking == true)
	//	{
	//		TextSize = 3;
	//		//Pressing Enter will change to Start and Quit game option
	//		if (Application::IsKeyPressed(VK_RETURN))
	//		{
	//			TextSize = 0;
	//			Delaytimer[0] = 0;
	//			TextChecking = false;
	//			bSomethingHappen = true;
	//		}
	//	}
	//	else if (!TextChecking)
	//	{
	//		if (Application::IsKeyPressed(VK_LEFT) && !bSomethingHappen)
	//		{
	//			if (selectedNum > 1)
	//			{
	//				//std::cout << "Left";
	//				selectedNum--;
	//				curX += moveAmt;
	//				bSomethingHappen = true;
	//			}
	//		}
	//		if (Application::IsKeyPressed(VK_RIGHT) && !bSomethingHappen)
	//		{
	//			if (selectedNum < 3)
	//			{
	//				//std::cout << "Right";
	//				selectedNum++;
	//				curX -= moveAmt;
	//				bSomethingHappen = true;
	//			}
	//		}

	//		switch (selectedNum)
	//		{
	//		case 1: //Start Game
	//			if (Application::IsKeyPressed(VK_RETURN) && !bSomethingHappen)
	//			{
	//				SceneManager::instance()->changeScene(2);
	//				return;
	//			}
	//			break;
	//		case 2: //Credits
	//			if (Application::IsKeyPressed(VK_RETURN) && !bSomethingHappen)
	//			{
	//				SceneManager::instance()->changeScene(8);
	//				return;
	//			}
	//			break;
	//		case 3: //End Game
	//			if (Application::IsKeyPressed(VK_RETURN) && !bSomethingHappen)
	//			{
	//				SceneManager::instance()->EndGame(true);
	//				return;
	//			}
	//			break;
	//		default:
	//			break;
	//		}
	//	}

	//}

	//else //Make menu appear
	//{
	//	Delaytimer[0] += (float)dt;
	//	TextSize = 0;
	//	if (Delaytimer[0] > 3)
	//	{
	//		TitleCheck = true;
	//	}
	//}

	/*static bool more = false;
	static bool less = false;
	if (bSomethingHappen && !more && !less)
	{
		if (transX > curX)
		{
			more = true;
		}
		else if (transX < curX)
		{
			less = true;
		}
		else
		{
			Delaytimer[0] += (float)dt;
			if (Delaytimer[0] > 2)
			{
				Delaytimer[0] = 0;
				transX = 0;
				bSomethingHappen = false;
			}
		}
	}

	if (more)
	{
		if (transX > curX)
		{
			transX -= moveAmt*dt;
		}
		else
		{
			more = bSomethingHappen = false;
		}
	}
	if (less)
	{
		if (transX < curX)
		{
			transX += moveAmt*dt;
		}
		else
		{
			less = bSomethingHappen = false;
		}
	}

	camera.Update(dt);*/
}

void UIManager::RenderUI()
{
	//Initialize
	Mtx44 MVP;

	//Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Setup the view for camera
	/*viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();*/

	//-------------------------------------------------------------------------------------
	//Front
	//modelStack.PushMatrix();
	////to do: transformation code here
	//modelStack.Translate(camera.position.x, camera.position.y, camera.position.z - 498.f);
	//modelStack.Scale(1000.f, 1000.f, 1000.f);
	//RenderMesh(meshList[GEO_FRONT], false);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////to do: transformation code here
	//modelStack.Translate(0, 0, -700);
	//modelStack.Translate(0, 0, -70 * Translating[0]);
	//modelStack.Rotate(90, 0, 0, 1);
	//modelStack.Scale(50, 50, 50);
	//RenderMesh(meshList[GEO_CINAMATIC], false);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////to do: transformation code here
	//modelStack.Translate(0, 0, -700);
	//modelStack.Translate(0, 0, -70 * Translating[1]);
	//modelStack.Scale(50, 50, 50);
	//RenderMesh(meshList[GEO_CINAMATIC], false);
	//modelStack.PopMatrix();

	//RenderTextOnScreen(meshList[GEO_TEXT], deltaTime, Color(0, 1, 0), 3, 0, 0);

	//No transform needed
	RenderMeshOnScreen(meshList[GEO_TITLE], 40, 30, titlescale, titlescale);
	RenderMeshOnScreen(meshList[GEO_SELECT1], transX + 40, 13, 20, 20);
	RenderMeshOnScreen(meshList[GEO_SELECT2], transX + 100, 13, 20, 20);
	RenderMeshOnScreen(meshList[GEO_SELECT3], transX + 160, 13, 20, 20);
	//modelStack.PushMatrix();
	//Text Enter and Start Game
	RenderTextOnScreen(meshList[GEO_TEXT], "ENTER TO START", Color(0, 1, 0), TextSize, 6, 4);
	//RenderTextOnScreen(meshList[GEO_TEXT], deltaTime, Color(0, 1, 0), 5, 0, 0);
	//modelStack.PopMatrix();
	//-------------------------------------------------------------------------------------

}

void UIManager::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(); //this line should only be called once
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void UIManager::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void UIManager::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);


	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i + 1.f * .7f, 1, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	//Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void UIManager::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	//to do: scale and translate accordingly
	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizex, sizey, 1);
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);

}

void UIManager::RenderUI()
{

}

void UIManager::CreateUI()
{

}

void UIManager::Exit()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i] != NULL)
			delete meshList[i];
	}
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);

	//Cleanup color
	glDeleteProgram(m_programID);
}